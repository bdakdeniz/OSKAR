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

#ifndef OSKAR_MATH_CUDAK_DFTW_O2C_2D_H_
#define OSKAR_MATH_CUDAK_DFTW_O2C_2D_H_

/**
 * @file oskar_math_cudak_dftw_o2c_2d.h
 */

#include "oskar_global.h"

/**
 * @brief
 * CUDA kernel to perform a 2D real-to-complex single-precision DFT using
 * supplied weights, where all input signals are implicitly of amplitude 1.0.
 *
 * @details
 * This CUDA kernel performs a 2D real-to-complex DFT, where all the input
 * signals are implicitly assumed to be of amplitude 1.0.
 *
 * Each thread evaluates a single output point, looping over all the input
 * points while performing a complex multiply-accumulate with the supplied
 * input DFT weights.
 *
 * The input positions must be pre-multiplied by a factor k (= 2pi / lambda).
 *
 * The computed points are returned in the \p output array, which must be
 * pre-sized to length n_out. The values in the \p output array are
 * the complex values for each output position.
 *
 * @param[in] n_in         Number of input points.
 * @param[in] x_in         Array of input x positions.
 * @param[in] y_in         Array of input y positions.
 * @param[in] weights_in   Array of complex DFT weights.
 * @param[in] n_out        Number of output points.
 * @param[in] x_out        Array of output 1/x positions.
 * @param[in] y_out        Array of output 1/y positions.
 * @param[in] max_in_chunk Maximum input points per chunk.
 * @param[out] output      Array of computed output points (see note, above).
 */
__global__
void oskar_cudak_dftw_o2c_2d_f(const int n_in, const float* x_in,
        const float* y_in, const float2* weights_in, const int n_out,
        const float* x_out, const float* y_out, const int max_in_chunk,
        float2* output);

/**
 * @brief
 * CUDA kernel to perform a 2D real-to-complex double-precision DFT using
 * supplied weights, where all input signals are implicitly of amplitude 1.0.
 *
 * @details
 * This CUDA kernel performs a 2D real-to-complex DFT, where all the input
 * signals are implicitly assumed to be of amplitude 1.0.
 *
 * Each thread evaluates a single output point, looping over all the input
 * points while performing a complex multiply-accumulate with the supplied
 * input DFT weights.
 *
 * The input positions must be pre-multiplied by a factor k (= 2pi / lambda).
 *
 * The computed points are returned in the \p output array, which must be
 * pre-sized to length n_out. The values in the \p output array are
 * the complex values for each output position.
 *
 * @param[in] n_in         Number of input points.
 * @param[in] x_in         Array of input x positions.
 * @param[in] y_in         Array of input y positions.
 * @param[in] weights_in   Array of complex DFT weights.
 * @param[in] n_out        Number of output points.
 * @param[in] x_out        Array of output 1/x positions.
 * @param[in] y_out        Array of output 1/y positions.
 * @param[in] max_in_chunk Maximum input points per chunk.
 * @param[out] output      Array of computed output points (see note, above).
 */
__global__
void oskar_cudak_dftw_o2c_2d_d(const int n_in, const double* x_in,
        const double* y_in, const double2* weights_in, const int n_out,
        const double* x_out, const double* y_out, const int max_in_chunk,
        double2* output);

#endif // OSKAR_MATH_CUDAK_DFTW_O2C_2D_H_
