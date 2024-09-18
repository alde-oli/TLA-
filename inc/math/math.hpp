// Author: alde-oli, date: 15/09/2024
// Description: Math functions with a focus on performance
// File version: 0.1
#include "../hyperp.hpp"
#include <type_traits>

template<typename T>
using EnableIfFloatingPoint = typename std::enable_if<std::is_floating_point<T>::value, T>::type;
template<typename T>
using EnableIfIntegral = typename std::enable_if<std::is_integral<T>::value, T>::type;

namespace tlap {
	// power
	template <typename T>
	T							pow(T x, int n);
	template <typename T>
	EnableIfFloatingPoint<T>	pow(T x, T n);

	// exp and log
	template <typename T>
	EnableIfFloatingPoint<T>	exp(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	ln(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	log10(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	log2(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	log(T x, int base);
	template <typename T>
	EnableIfFloatingPoint<T>	log(T x, T base);
	

	// root
	template <typename T>
	EnableIfFloatingPoint<T>	sqrt(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	cbrt(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	root(T x, int n);
	template <typename T>
	EnableIfFloatingPoint<T>	root(T x, T n);

	// trigonometry
	template <typename T>
	EnableIfFloatingPoint<T>	sin(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	cos(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	tan(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	asin(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	acos(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	atan(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	atan2(T y, T x);

	// hyperbolic
	template <typename T>
	EnableIfFloatingPoint<T>	sinh(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	cosh(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	tanh(T x);

	// rounding
	template <typename T>
	EnableIfFloatingPoint<T>	floor(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	ceil(T x);
	template <typename T>
	EnableIfFloatingPoint<T>	round(T x);

	// other
	template <typename T>
	T							abs(T x);
	template <typename T>
	T							mod(T x, T y);
	template <typename T>
	EnableIfIntegral<T>			factorial(T x);
	template <typename T>
	T							rougheq(T x, T y, T e);
	template <typename T>
	T							lerp(T a, T b, T t);
	template <typename T>
	T							clamp(T x, T min, T max);
}

#include "math.tpp"