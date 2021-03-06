/*
 * Copyright (c) 2016, The University of Oxford
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

#ifndef OSKAR_DFT_C2R_3D_CUDA_H_
#define OSKAR_DFT_C2R_3D_CUDA_H_

/**
 * @file oskar_dft_c2r_3d_cuda.h
 */

#include <oskar_global.h>
#include <utility/oskar_vector_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * CUDA wrapper to perform a 3D complex-to-real single-precision DFT.
 *
 * @details
 * Computes a real output from a set of complex input data, using CUDA to
 * evaluate a 3D Direct Fourier Transform (DFT).
 *
 * Note that all pointers are device pointers, and must not be dereferenced
 * in host code.
 *
 * This function must be supplied with the input x-, y- and z-positions, and
 * the output x-, y- and z-positions.
 * The output positions are direction cosines.
 *
 * The wavelength used to compute the supplied wavenumber must be in the
 * same units as the input positions.
 *
 * The fastest-varying dimension in the output array is along x. The output is
 * assumed to be completely real, so the conjugate copy of the input data
 * should not be supplied.
 *
 * @param[in] num_in       Number of input points.
 * @param[in] wavenumber   Wavenumber (2 pi / wavelength).
 * @param[in] x_in         Array of input x positions.
 * @param[in] y_in         Array of input y positions.
 * @param[in] z_in         Array of input z positions.
 * @param[in] data_in      Array of complex input data.
 * @param[in] weight_in    Array of input data weights.
 * @param[in] num_out      Number of output points.
 * @param[in] x_out        Array of output 1/x positions.
 * @param[in] y_out        Array of output 1/y positions.
 * @param[in] z_out        Array of output 1/z positions.
 * @param[out] output      Array of computed output points.
 */
OSKAR_EXPORT
void oskar_dft_c2r_3d_cuda_f(int num_in, float wavenumber, const float* x_in,
        const float* y_in, const float* z_in, const float2* data_in,
        const float* weight_in, int num_out, const float* x_out,
        const float* y_out, const float* z_out, float* output);

/**
 * @brief
 * CUDA wrapper to perform a 3D complex-to-real double-precision DFT.
 *
 * @details
 * Computes a real output from a set of complex input data, using CUDA to
 * evaluate a 3D Direct Fourier Transform (DFT).
 *
 * Note that all pointers are device pointers, and must not be dereferenced
 * in host code.
 *
 * This function must be supplied with the input x-, y- and z-positions, and
 * the output x-, y- and z-positions.
 * The output positions are direction cosines.
 *
 * The wavelength used to compute the supplied wavenumber must be in the
 * same units as the input positions.
 *
 * The fastest-varying dimension in the output array is along x. The output is
 * assumed to be completely real, so the conjugate copy of the input data
 * should not be supplied.
 *
 * @param[in] num_in       Number of input points.
 * @param[in] wavenumber   Wavenumber (2 pi / wavelength).
 * @param[in] x_in         Array of input x positions.
 * @param[in] y_in         Array of input y positions.
 * @param[in] z_in         Array of input z positions.
 * @param[in] data_in      Array of complex input data.
 * @param[in] weight_in    Array of input data weights.
 * @param[in] num_out      Number of output points.
 * @param[in] x_out        Array of output 1/x positions.
 * @param[in] y_out        Array of output 1/y positions.
 * @param[in] z_out        Array of output 1/z positions.
 * @param[out] output      Array of computed output points.
 */
OSKAR_EXPORT
void oskar_dft_c2r_3d_cuda_d(int num_in, double wavenumber, const double* x_in,
        const double* y_in, const double* z_in, const double2* data_in,
        const double* weight_in, int num_out, const double* x_out,
        const double* y_out, const double* z_out, double* output);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_DFT_C2R_3D_CUDA_H_ */
