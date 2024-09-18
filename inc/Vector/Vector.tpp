#include "Vector.hpp"
#include <immintrin.h>

template <typename T>
void simd_fill_tab(T *tab, size_t n, T v) {
    if (n >= SIMD_THRESHOLD) {
#ifdef __AVX__ // AVX for 256-bit SIMD operations, adjust for different types
        size_t i = 0;
        if constexpr (std::is_same<T, float>::value) {
            __m256 simd_val = _mm256_set1_ps(v); // AVX 256-bit for float
            size_t simd_count = n / 8; // Each __m256 holds 8 floats
            for (; i < simd_count * 8; i += 8)
				_mm256_storeu_ps(&tab[i], simd_val);
        } else if constexpr (std::is_same<T, double>::value) {
            __m256d simd_val = _mm256_set1_pd(v); // AVX 256-bit for double
            size_t simd_count = n / 4; // Each __m256d holds 4 doubles
            for (; i < simd_count * 4; i += 4)
				_mm256_storeu_pd(&tab[i], simd_val);
        } else if constexpr (std::is_same<T, int>::value) {
            __m256i simd_val = _mm256_set1_epi32(v); // AVX 256-bit for int
            size_t simd_count = n / 8; // Each __m256i holds 8 ints
            for (; i < simd_count * 8; i += 8)
				_mm256_storeu_si256((__m256i*)&tab[i], simd_val);
        } else
            for (; i < n; ++i)
				tab[i] = v;
        for (; i < n; ++i)
			tab[i] = v;

#else
        for (size_t i = 0; i < n; ++i)
			tab[i] = v;
#endif
    } else
        for (size_t i = 0; i < n; ++i)
			tab[i] = v;
}

namespace tlap {

Vector::Vector()
	: _data(nullptr), _size(0) {
}

Vector::Vector(size_t size)
	: _data(new T[size]), _size(size) {
	simd_fill_tab(_data, size, T(0));
}

}