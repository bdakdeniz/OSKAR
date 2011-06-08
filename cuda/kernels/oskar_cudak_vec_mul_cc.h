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

#ifndef OSKAR_CUDAK_VEC_MUL_CC_H_
#define OSKAR_CUDAK_VEC_MUL_CC_H_

/**
 * @file oskar_cudak_vec_mul_cc.h
 */

#ifdef __CDT_PARSER__
    #define __global__
    #define __device__
    #define __shared__
    #define __constant__
#endif

/**
 * @brief
 * CUDA kernel to multiply two complex vectors together, element-wise
 * (single precision).
 *
 * @details
 * This CUDA kernel multiplies the elements of two complex vectors together
 * using the graphics card.
 *
 * @param[in] n Number of elements in all vectors.
 * @param[in] a First input vector.
 * @param[in] b Second input vector.
 * @param[out] c Output vector.
 */
__global__
void oskar_cudakf_vec_mul_cc(int n, const float2* a, const float2* b, float2* c);

/**
 * @brief
 * CUDA kernel to multiply two complex vectors together, element-wise
 * (double precision).
 *
 * @details
 * This CUDA kernel multiplies the elements of two complex vectors together
 * using the graphics card.
 *
 * @param[in] n Number of elements in all vectors.
 * @param[in] a First input vector.
 * @param[in] b Second input vector.
 * @param[out] c Output vector.
 */
__global__
void oskar_cudakd_vec_mul_cc(int n, const double2* a, const double2* b,
        double2* c);

#endif // OSKAR_CUDAK_VEC_MUL_CC_H_
