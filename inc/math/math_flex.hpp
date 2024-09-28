#pragma once

#include "math.hpp"
#include <type_traits>
#include <iostream>

// Can choose between float, double, and long double depending on precision vs performance needs
#define FLOATING_CONVERT	double
#define INT_CONVERT			int
#define AUTO_T				template <typename T> auto
#define IF_INT(T)			std::enable_if_t<std::is_integral_v<T>, FLOATING_CONVERT>
#define IF_FLOAT(T)			std::enable_if_t<std::is_floating_point_v<T>, T>
#define TO_FLOATING(x)		static_cast<FLOATING_CONVERT>(x)
#define TO_INT(x)			static_cast<INT_CONVERT>(x)

namespace tlap {
// power
AUTO_T	pow(T x, int n) -> IF_INT(T) {
	return tlap::pow(TO_FLOATING(x), n);
}

AUTO_T	pow(T x, T n) -> IF_INT(T) {
	return tlap::pow(TO_FLOATING(x), TO_FLOATING(n));
}


// exp and log
AUTO_T	exp(T x) -> IF_INT(T) {
	return tlap::exp(TO_FLOATING(x));
}

AUTO_T	ln(T x) -> IF_INT(T) {
	return tlap::ln(TO_FLOATING(x));
}

AUTO_T	log10(T x) -> IF_INT(T) {
	return tlap::log10(TO_FLOATING(x));
}

AUTO_T	log2(T x) -> IF_INT(T) {
	return tlap::log2(TO_FLOATING(x));
}

AUTO_T	log(T x, int base) -> IF_INT(T) {
	return tlap::log(TO_FLOATING(x), base);
}

AUTO_T	log(T x, T base) -> IF_INT(T) {
	return tlap::log(TO_FLOATING(x), TO_FLOATING(base));
}


// root
AUTO_T	sqrt(T x) -> IF_INT(T) {
	return tlap::sqrt(TO_FLOATING(x));
}

AUTO_T	cbrt(T x) -> IF_INT(T) {
	return tlap::cbrt(TO_FLOATING(x));
}

AUTO_T	root(T x, int n) -> IF_INT(T) {
	return tlap::root(TO_FLOATING(x), n);
}

AUTO_T	root(T x, T n) -> IF_INT(T) {
	return tlap::root(TO_FLOATING(x), TO_FLOATING(n));
}


// trigonometry
AUTO_T	sin(T x) -> IF_INT(T) {
	return tlap::sin(TO_FLOATING(x));
}

AUTO_T	cos(T x) -> IF_INT(T) {
	return tlap::cos(TO_FLOATING(x));
}

AUTO_T	tan(T x) -> IF_INT(T) {
	return tlap::tan(TO_FLOATING(x));
}

AUTO_T	asin(T x) -> IF_INT(T) {
	return tlap::asin(TO_FLOATING(x));
}

AUTO_T	acos(T x) -> IF_INT(T) {
	return tlap::acos(TO_FLOATING(x));
}

AUTO_T	atan(T x) -> IF_INT(T) {
	return tlap::atan(TO_FLOATING(x));
}

AUTO_T	atan2(T y, T x) -> IF_INT(T) {
	return tlap::atan2(TO_FLOATING(y), TO_FLOATING(x));
}


// hyperbolic
AUTO_T	sinh(T x) -> IF_INT(T) {
	return tlap::sinh(TO_FLOATING(x));
}

AUTO_T	cosh(T x) -> IF_INT(T) {
	return tlap::cosh(TO_FLOATING(x));
}

AUTO_T	tanh(T x) -> IF_INT(T) {
	return tlap::tanh(TO_FLOATING(x));
}


// rounding
AUTO_T	floor(T x) -> IF_INT(T) {
	return tlap::floor(TO_FLOATING(x));
}

AUTO_T	ceil(T x) -> IF_INT(T) {
	return tlap::ceil(TO_FLOATING(x));
}

AUTO_T	round(T x) -> IF_INT(T) {
	return tlap::round(TO_FLOATING(x));
}


// other
AUTO_T	factorial(T x) -> IF_FLOAT(T) {
	return tlap::factorial(TO_INT(x));
}
}