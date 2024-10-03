#pragma once

// implementation of math function with a focus on performance
#include <stdexcept>
#include <limits>
#include <cmath>
#include "math.hpp"
#include "../hyperp.hpp"


namespace tlap {

// power
T_ARITHMETIC	pow(T x, int n) {
    if (n == 0) return 1;
    if (x == 0) {
        if (n > 0) return 0;
        else throw std::invalid_argument("0^0 is undefined");
    }
    if (n == 1) return x;
    if (n == 2) return x * x;
    if (n < 0) {
        x = 1 / x;
        n = -n;
    }
    T result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= x;
        }
        x *= x;
        n /= 2;
    }
    return result;
}

//70 chaussures-chaussettes decathlon + 90 chf nouvelles chaussures + 50 euros maillots de bain et tongues intersport + 110 chf manger

T_ARITHMETIC	 pow(T x, T n) {
    if (n == 0) return 1;
    if (x == 0) {
        if (n > 0) return 0;
        else
			throw std::invalid_argument("0^0 is undefined");
    }
    if (x < 0 && std::floor(n) != n)
        throw std::invalid_argument("Negative base with non-integer exponent is undefined in real numbers.");
    if (n == 1) return x;
    if (n == 2) return x * x;
    if (n == 0.5) return tlap::sqrt(x);
    if (n == -0.5) return 1 / tlap::sqrt(x);
    if (n == -1) return 1 / x;
    return tlap::exp(n * tlap::ln(x));
}


// exp and log
T_FLOAT			exp(T x) {
	if (x < 0)
		return 1 / tlap::exp(-x);
	else if (x == 0)
		return 1;
	else if (x == 1)
		return E;
	else if (x > EXP_LIMIT)
		return std::numeric_limits<T>::infinity();
	else if (x < -EXP_LIMIT)
		return 0;
	
	T result = 1;
	T term = 1;

	for (int n = 1; n < EXP_TERMS; ++n) {
		term *= x / n;
		if (tlap::abs(term) < EPSILON)
			break;
		result += term;
	}
	return result;
}

T_FLOAT			ln(T x) {
	if (x <= 0)
		return std::numeric_limits<T>::quiet_NaN();
	else if (x == 1)
		return 0;

	int exponent = 0;

	while (x > 2) {
		x /= 2;
		++exponent;
	}
	while (x < 0.5) {
		x *= 2;
		--exponent;
	}

	T result = 0;
	T term = (x - 1) / (x + 1);
	T termSquared = term * term;

	for (int n = 1; n <= LN_TERMS; n += 2) {
		result += term / n;
		term *= termSquared;
	}
	return (result * 2 + exponent * LN2);
}

T_FLOAT			log10(T x) {
	if (x <= 0)
		return std::numeric_limits<T>::quiet_NaN();
	return tlap::ln(x) / LN10;
}

T_FLOAT			log2(T x) {
	if (x <= 0)
		return std::numeric_limits<T>::quiet_NaN();
	return tlap::ln(x) / LN2;
}

T_FLOAT			log(T x, int base) {
	if (x <= 0 || base <= 0 || base == 1)
		return std::numeric_limits<T>::quiet_NaN();
	return tlap::ln(x) / tlap::ln(static_cast<T>(base));
}

T_FLOAT			log(T x, T base) {
	if (x <= 0 || base <= 0 || base == 1)
		return std::numeric_limits<T>::quiet_NaN();
	return tlap::ln(x) / tlap::ln(base);
}

// root
T_FLOAT			sqrt(T x) {
	if (x < 0)
		return std::numeric_limits<T>::quiet_NaN();
	else if (x == 0 || x == 1)
		return x;

	T result = x / 2.0;

	while (tlap::abs(result * result - x) > EPSILON)
		result = (result + x / result) / 2.0;
	return result;
}

T_FLOAT			cbrt(T x) {
	if (x == 0 || x == 1)
		return x;

	T result = x / 3.0;

	while (tlap::abs(result * result * result - x) > EPSILON)
		result = (2 * result + x / (result * result)) / 3.0;
	return result;
}

T_FLOAT			root(T x, int n) {
	if (n == 0)
		throw std::invalid_argument("The root of degree 0 is undefined.");
	if (x < 0 && n % 2 == 0)
		return std::numeric_limits<T>::quiet_NaN();
	if (x == 0)
		return 0;

	T result = x / n;
	T epsilon = static_cast<T>(1e-10);

	while (tlap::abs(tlap::pow(result, n) - x) > epsilon)
		result = (1.0 / n) * ((n - 1) * result + x / tlap::pow(result, n - 1));
	return result;
}

T_FLOAT			root(T x, T n) {
	if (n == 0)
		throw std::invalid_argument("The root of degree 0 is undefined.");
	if (x < 0 && tlap::floor(n) != n && static_cast<int>(n) % 2 == 0)
		return std::numeric_limits<T>::quiet_NaN();
	if (x == 0)
		return 0;

	T result = x / n;
	T epsilon = static_cast<T>(1e-10);

	while (tlap::abs(tlap::pow(result, n) - x) > epsilon)
		result = ((n - 1.0) * result + x / tlap::pow(result, n - 1)) / n;
	return result;
}

// trigonometry
T_FLOAT			sin(T x) {
	x = tlap::mod(x, 2.0 * PI);

	T term = x;
	T result = x;
	T x_squared = x * x;
	int n = 1;

	while (tlap::abs(term) > EPSILON) {
		n += 2;
		term *= -x_squared / (n * (n - 1));
		result += term;
	}
	return result;
}

T_FLOAT			cos(T x) {
	x = tlap::mod(x, 2 * PI);

	T term = 1;
	T result = 1;
	T x_squared = x * x;
	int n = 2;

	while (tlap::abs(term) > EPSILON) {
		term *= -x_squared / (n * (n - 1));
		result += term;
		n += 2;
	}
	return result;
}

T_FLOAT			tan(T x) {
	x = tlap::mod(x, 2 * PI);

	T cosine_value = cos(x);

	if (tlap::abs(cosine_value) < EPSILON)
		throw std::overflow_error("Tangent undefined (cos(x) is too close to 0).");
	return tlap::sin(x) / cosine_value;
}

T_FLOAT			asin(T x) {
	if (x < -1 || x > 1)
		throw std::invalid_argument("asin() is undefined for |x| > 1.");

	T result = x;
	T term = x;
	T x_squared = x * x;
	int n = 1;

	while (tlap::abs(term) > EPSILON && n < MAX_RECURSION) {
		term *= x_squared * (2 * n - 1) / (2 * n);
		result += term / (2 * n + 1);
		n++;
	}
	return result;
}

T_FLOAT			acos(T x) {
	if (x < -1 || x > 1)
		throw std::invalid_argument("acos() is undefined for |x| > 1.");

	return PI / 2 - tlap::asin(x);
}

T_FLOAT			atan(T x) {
	if (tlap::abs(x) > 1) {
		if (x > 1)
			return PI / 2 - tlap::atan(1 / x);
		else
			return -PI / 2 - tlap::atan(1 / x);
	}

	T result = x;
	T term = x;
	T x_squared = x * x;
	int n = 1;

	while (tlap::abs(term) > EPSILON && n < MAX_RECURSION) {
		term *= -x_squared;
		result += term / (2 * n + 1);
		n++;
	}
	return result;
}

T_FLOAT			atan2(T y, T x) {
	if (x == 0) {
		if (y == 0)
			throw std::invalid_argument("atan2(0, 0) is undefined.");
		return (y > 0 ? PI / 2 : -PI / 2);
	}
	else if (y == 0)
		return (x > 0 ? 0 : PI);

	T result = tlap::atan(y / x);
	if (x < 0)
		result += (y >= 0 ? PI : -PI);
	return result;
}

// hyperbolic
T_FLOAT			sinh(T x) {
	return (tlap::exp(x) - tlap::exp(-x)) / 2;
}

T_FLOAT			cosh(T x) {
	return (tlap::exp(x) + tlap::exp(-x)) / 2;
}

T_FLOAT			tanh(T x) {
	T exp_x = tlap::exp(x);
	T exp_minus_x = tlap::exp(-x);
	if (exp_x == std::numeric_limits<T>::infinity())
		return 1;
	else if (exp_minus_x == std::numeric_limits<T>::infinity())
		return -1;
	if (exp_x + exp_minus_x == 0)
		throw std::overflow_error("Tanh undefined (exp(x) + exp(-x) is too close to 0).");
	return (exp_x - exp_minus_x) / (exp_x + exp_minus_x);
}

// rounding
T_FLOAT			floor(T x) {
	T int_part = static_cast<T>(static_cast<long long>(x));
	if (x < int_part)
		return int_part - 1.0;
	return int_part;
}

T_FLOAT			ceil(T x) {
	T int_part = static_cast<T>(static_cast<long long>(x));
	if (x > int_part)
		return int_part + 1.0;
	return int_part;
}

T_FLOAT			round(T x) {
	T int_part = static_cast<T>(static_cast<long long>(x));
	T fractional = x - int_part;
	
	if (fractional >= 0.5)
		return int_part + 1.0;
	else if (fractional <= -0.5)
		return int_part - 1.0;
	return int_part;
}

// other
T_ARITHMETIC	abs(T x) {
	return (x < 0 ? -x : x);
}

T_ARITHMETIC	mod(T x, T y) {
	if (y == 0)
		throw std::invalid_argument("Division by zero");
	return x - y * tlap::floor(x / y);
}

T_INT			factorial(T n) {
	if (n < 0)
		throw std::invalid_argument("Factorial is not defined for negative numbers.");
	else if (n == 0 || n == 1)
		return 1;
	else if (n <= FACTORIAL_SWITCH) {
		T result = 1;
		for (T i = 2; i <= n; ++i)
			result *= i;
		return result;
	}
	return static_cast<T>(tlap::sqrt(2 * PI * n) * tlap::pow(n / E, n));
}

T_ARITHMETIC	rougheq(T x, T y, T e) {
	return (tlap::abs(x - y) < e);
}

T_ARITHMETIC	lerp(T a, T b, T t) {
	if (t < 0 || t > 1)
		throw std::invalid_argument("t must be between 0 and 1");
	return a + t * (b - a);
}

T_ARITHMETIC	clamp(T x, T min, T max) {
	if (x < min)
		return min;
	else if (x > max)
		return max;
	return x;
}

} // namespace tlap
