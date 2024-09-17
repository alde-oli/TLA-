// Author: alde-oli, date: 15/09/2024
// Description: Vector class with a focus on performance
// File version: 0.1

#pragma once

#include <type_traits>
#include <vector>
#include <list>

typedef unsigned int size_t;

#define TEMPLATE_U template <typename U>
#define TEMPLATE_UV template <typename U, typename V>
#define ARITHMETIC_U static_assert(std::is_arithmetic<U>::value, "U must be an arithmetic type!")


namespace tlap {

template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
class Vector {
	static_assert(std::is_arithmetic<T>::value, "Vector can only be instantiated with arithmetic types.");

	private:
		T		*_data;
		T		*_newData = nullptr;
		size_t	_size;

	public:
		// constructors and destructor
		Vector();
		Vector(size_t size);
		TEMPLATE_U Vector(size_t size, const U &value);
		TEMPLATE_U Vector(std::initializer_list<U> list);
		TEMPLATE_U Vector(const Vector<U> &other);
		TEMPLATE_U Vector(const std::vector<U> &other);
		TEMPLATE_U Vector(Vector<U> &&other) noexcept;
		~Vector();
	
		// assignment operators
		TEMPLATE_U Vector<T>	&operator=(const Vector<U> &other);
		TEMPLATE_U Vector<T>	&operator=(Vector<U> &&other) noexcept; // move assignment
	
		// comparison operators
		TEMPLATE_U bool			operator==(const Vector<U> &other) const;
		TEMPLATE_U bool			operator!=(const Vector<U> &other) const;
	
		// arithmetic operators
		TEMPLATE_U Vector<T>	operator+(const Vector<U> &other) const;
		TEMPLATE_U Vector<T>	operator-(const Vector<U> &other) const;
		TEMPLATE_U Vector<T>	operator*(const Vector<U> &other) const; // dot product
		TEMPLATE_U Vector<T>	operator*(const U &scalar) const;
		TEMPLATE_U Vector<T>	operator/(const U &scalar) const;
		// compound assignment operators
		TEMPLATE_U Vector<T>	&operator+=(const Vector<T> &other);
		TEMPLATE_U Vector<T>	&operator-=(const Vector<T> &other);
		TEMPLATE_U Vector<T>	&operator*=(const Vector<T> &other);
		TEMPLATE_U Vector<T>	&operator*=(const T &scalar);
		TEMPLATE_U Vector<T>	&operator/=(const T &scalar);
	
		// stream operator
		friend std::ostream		&operator<<(std::ostream &os, const Vector<T> &vector);

		// index access operators
		const T					&operator[](size_t index) const;
		T						&operator[](size_t index);

		// various operations and methods
		TEMPLATE_U Vector<T>	&add(const Vector<T> &other);
		TEMPLATE_U Vector<T>	&sub(const Vector<T> &other);

		TEMPLATE_U Vector<T>	&scaleUp(const T &scalar);
		TEMPLATE_U Vector<T>	&scaleDown(const T &scalar);

		TEMPLATE_UV Vector<T>	&linComb(const Vector<U> &other, const V &factor1, const V &factor2);
		// linear combination with a list of vectors and factors, and the first vector factor
		TEMPLATE_UV Vector<T>	&linComb(const std::list<Vector<U>> &others, const std::list<V> &factors, const V &factor1);
		//
		size_t					shape() const;
		Vector<T>				&reshape(size_t size);
		void					print() const;
};

} // namespace tlap

#include "../src/Vector.tpp" // implementations