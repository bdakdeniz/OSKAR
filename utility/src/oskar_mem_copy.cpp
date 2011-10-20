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

#include <cuda_runtime_api.h>
#include <cstring>
#include "utility/oskar_mem_copy.h"
#include "utility/oskar_mem_element_size.h"

extern "C"
int oskar_mem_copy(oskar_Mem* dst, const oskar_Mem* src)
{
    // Check that all pointers are not NULL.
    if (src == NULL || dst == NULL)
        return OSKAR_ERR_INVALID_ARGUMENT;
    if (src->data == NULL || dst->data == NULL)
        return OSKAR_ERR_MEMORY_NOT_ALLOCATED;

    // Get the meta-data.
    int n_elements_src = src->n_elements();
    int n_elements_dst = dst->n_elements();
    int type_src = src->type();
    int type_dst = dst->type();
    int location_src = src->location();
    int location_dst = dst->location();

    // Check the data dimensions.
    if (n_elements_src != n_elements_dst)
        return OSKAR_ERR_DIMENSION_MISMATCH;

    // Check the data types.
    if (type_src != type_dst)
        return OSKAR_ERR_TYPE_MISMATCH;

    // Get the number of bytes to copy.
    int bytes = oskar_mem_element_size(type_src) * n_elements_src;

    // Host to host.
    if (location_src == OSKAR_LOCATION_CPU
            && location_dst == OSKAR_LOCATION_CPU)
    {
        memcpy(dst->data, src->data, bytes);
        return 0;
    }

    // Host to device.
    else if (location_src == OSKAR_LOCATION_CPU
            && location_dst == OSKAR_LOCATION_GPU)
    {
        cudaMemcpy(dst->data, src->data, bytes, cudaMemcpyHostToDevice);
        return cudaPeekAtLastError();
    }

    // Device to host.
    else if (location_src == OSKAR_LOCATION_GPU
            && location_dst == OSKAR_LOCATION_CPU)
    {
        cudaMemcpy(dst->data, src->data, bytes, cudaMemcpyDeviceToHost);
        return cudaPeekAtLastError();
    }

    // Device to device.
    else if (location_src == OSKAR_LOCATION_GPU
            && location_dst == OSKAR_LOCATION_GPU)
    {
        cudaMemcpy(dst->data, src->data, bytes, cudaMemcpyDeviceToDevice);
        return cudaPeekAtLastError();
    }

    return OSKAR_ERR_BAD_LOCATION;
}
