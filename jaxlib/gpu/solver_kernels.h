/* Copyright 2019 The JAX Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef JAXLIB_CUSOLVER_KERNELS_H_
#define JAXLIB_CUSOLVER_KERNELS_H_

#include <cstddef>

#include "jaxlib/gpu/vendor.h"
#include "xla/service/custom_call_status.h"

namespace jax {

namespace JAX_GPU_NAMESPACE {

// Set of types known to Cusolver.
enum class SolverType {
  F32,
  F64,
  C64,
  C128,
};

#ifdef JAX_GPU_CUDA

// csrlsvpr: Linear system solve via Sparse QR

struct CsrlsvqrDescriptor {
  SolverType type;
  int n, nnz, reorder;
  double tol;
};

void Csrlsvqr(gpuStream_t stream, void** buffers, const char* opaque,
              size_t opaque_len, XlaCustomCallStatus* status);

#endif  // JAX_GPU_CUDA

// sytrd/hetrd: Reduction of a symmetric (Hermitian) matrix to tridiagonal form.
struct SytrdDescriptor {
  SolverType type;
  gpusolverFillMode_t uplo;
  int batch, n, lda, lwork;
};

void Sytrd(gpuStream_t stream, void** buffers, const char* opaque,
           size_t opaque_len, XlaCustomCallStatus* status);


}  // namespace JAX_GPU_NAMESPACE
}  // namespace jax

#endif  // JAXLIB_CUSOLVER_KERNELS_H_
