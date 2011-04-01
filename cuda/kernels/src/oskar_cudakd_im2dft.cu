/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "cuda/kernels/oskar_cudakd_im2dft.h"

// Shared memory pointer used by the kernel.
extern __shared__ double4 c[];

#ifndef M_2PI
#define M_2PI 6.283185307179586476925
#endif

__global__
void oskar_cudakd_im2dft(int nv, const double* u, const double* v,
        const double2* vis, const int np, const double* pl, const double* pm,
        const int maxVisPerBlock, double* image)
{
    // Get the pixel ID that this thread is working on.
    const int p = blockDim.x * blockIdx.x + threadIdx.x;

    // Get the pixel position.
    // (NB. Cannot exit on index condition, as all threads are needed later).
    double cpx = 0.0, l = 0.0, m = 0.0;
    if (p < np) {
        l = pl[p];
        m = pm[p];
    }

    // Cache a block of visibilities and u,v-coordinates into shared memory.
    for (int vs = 0; vs < nv; vs += maxVisPerBlock) {
        int visInBlock = nv - vs;
        if (visInBlock > maxVisPerBlock)
            visInBlock = maxVisPerBlock;

        // There are blockDim.x threads available - need to copy
        // visInBlock pieces of data from global memory.
        for (int t = threadIdx.x; t < visInBlock; t += blockDim.x) {
            const int g = vs + t; // Global visibility index.
            c[t].x = u[g];
            c[t].y = v[g];
            c[t].z = vis[g].x;
            c[t].w = vis[g].y;
        }

        // Pre-multiply.
        for (int t = threadIdx.x; t < visInBlock; t += blockDim.x) {
            c[t].x *= M_2PI;
            c[t].y *= M_2PI;
        }

        // Must synchronise before computing the signal for these visibilities.
        __syncthreads();

        // Loop over visibilities in block.
        for (int v = 0; v < visInBlock; ++v) {
            // Calculate the complex DFT weight.
            double4 cc = c[v];
            double2 weight;
            double a = cc.x * l + cc.y * m; // u*l + v*m
            sincos(a, &weight.y, &weight.x);

            // Perform complex multiply-accumulate.
            // Image is real, so should only need to evaluate the real part.
            cpx += cc.z * weight.x - cc.w * weight.y; // RE*RE - IM*IM
        }

        // Must synchronise again before loading in a new block of visibilities.
        __syncthreads();
    }

    // Copy result into global memory.
    if (p < np)
        if (hypot(l, m) > 1.0)
            image[p] = 0.0;
        else
            image[p] = cpx / (double)nv;
}
