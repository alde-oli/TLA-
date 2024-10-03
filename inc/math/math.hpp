// Author: alde-oli, date: 15/09/2024
// Description: Math functions with a focus on performance
// File version: 0.1
#pragma once

#include "../hyperp.hpp"
#include <concepts>

#define T_FLOAT			template <std::floating_point T> auto
#define T_ARITHMETIC	template <typename T> auto
#define T_INT			template <std::integral T> auto

namespace	tlap {
	// power
	T_ARITHMETIC	pow(T x, int n);
	T_ARITHMETIC	pow(T x, T n);

	// exp and log
	T_FLOAT			exp(T x);
	T_FLOAT			ln(T x);
	T_FLOAT			log10(T x);
	T_FLOAT			log2(T x);
	T_FLOAT			log(T x, int base);
	T_FLOAT			log(T x, T base);

	// root
	T_FLOAT			sqrt(T x);
	T_FLOAT			cbrt(T x);
	T_FLOAT			root(T x, int n);
	T_FLOAT			root(T x, T n);

	// trigonometry
	T_FLOAT			sin(T x);
	T_FLOAT			cos(T x);
	T_FLOAT			tan(T x);
	T_FLOAT			asin(T x);
	T_FLOAT			acos(T x);
	T_FLOAT			atan(T x);
	T_FLOAT			atan2(T y, T x);

	// hyperbolic
	T_FLOAT			sinh(T x);
	T_FLOAT			cosh(T x);
	T_FLOAT			tanh(T x);

	// rounding
	T_FLOAT			floor(T x);
	T_FLOAT			ceil(T x);
	T_FLOAT			round(T x);

	// other
	T_ARITHMETIC		abs(T x);
	T_ARITHMETIC		mod(T x, T y);
	T_INT				factorial(T x);
	T_ARITHMETIC		rougheq(T x, T y, T e);
	T_ARITHMETIC		lerp(T a, T b, T t);
	T_ARITHMETIC		clamp(T x, T min, T max);
}

#include "math.tpp"
