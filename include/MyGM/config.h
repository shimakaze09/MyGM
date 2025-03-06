//
// Created by Admin on 6/03/2025.
//

#pragma once

#ifndef MY_FORCEINLINE
#if (_MSC_VER >= 1200)
#define MY_FORCEINLINE __forceinline
#else
#define MY_FORCEINLINE __inline
#endif
#endif  // !MY_FORCEINLINE

#ifdef MY_USE_XSIMD
#include "_deps/xsimd/xsimd.hpp"
// link:
// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html

#define MakeShuffleMask(x, y, z, w) (x | (y << 2) | (z << 4) | (w << 6))

// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
#define VecSwizzleMask(vec, mask) \
  _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vec), mask))
#define VecSwizzle(vec, x, y, z, w) \
  VecSwizzleMask(vec, MakeShuffleMask(x, y, z, w))
#define VecSwizzle1(vec, x) VecSwizzleMask(vec, MakeShuffleMask(x, x, x, x))
// special swizzle
#define VecSwizzle_0022(vec) _mm_moveldup_ps(vec)
#define VecSwizzle_1133(vec) _mm_movehdup_ps(vec)

// return (vec1[x], vec1[y], vec2[z], vec2[w])
#define VecShuffle(vec1, vec2, x, y, z, w) \
  _mm_shuffle_ps(vec1, vec2, MakeShuffleMask(x, y, z, w))
// special shuffle
#define VecShuffle_0101(vec1, vec2) _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2) _mm_movehl_ps(vec2, vec1)

#ifdef MY_USE_SSE_4_1
/*
<mmintrin.h>  MMX
<xmmintrin.h> SSE
<emmintrin.h> SSE2
<pmmintrin.h> SSE3
<tmmintrin.h> SSSE3
<smmintrin.h> SSE4.1
<nmmintrin.h> SSE4.2
<ammintrin.h> SSE4A
<wmmintrin.h> AES
<immintrin.h> AVX, AVX2, FMA
*/
#include <smmintrin.h>
#endif  // MY_USE_SSE_4_1

#endif  // MY_USE_XSIMD
