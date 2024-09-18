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
		TEMPLATE_U Vector(size_t size, const U &value); // fill constructor
		TEMPLATE_U Vector(std::initializer_list<U> list); // initializer list constructor
		TEMPLATE_U Vector(const Vector<U> &other); // copy constructor
		TEMPLATE_U Vector(Vector<U> &&other) noexcept; // move constructor
		TEMPLATE_U Vector(const std::vector<U> &other); // std::vector copy constructor
		TEMPLATE_U Vector(std::vector<U> &&other); // std::vector move constructor
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
		TEMPLATE_U Vector<T>	&operator+=(const Vector<U> &other);
		TEMPLATE_U Vector<T>	&operator-=(const Vector<U> &other);
		TEMPLATE_U Vector<T>	&operator*=(const Vector<U> &other);
		TEMPLATE_U Vector<T>	&operator*=(const U &scalar);
		TEMPLATE_U Vector<T>	&operator/=(const U &scalar);
	
		// stream operator
		friend std::ostream		&operator<<(std::ostream &os, const Vector<T> &vector);

		// index access operators
		const T					&operator[](size_t index) const; // read-access
		T						&operator[](size_t index); // write-access

		// various operations and methods
		TEMPLATE_U Vector<T>	&add(const Vector<U> &other);
		TEMPLATE_U Vector<T>	&sub(const Vector<U> &other);

		TEMPLATE_U Vector<T>	&scaleUp(const T &scalar); // multiply by scalar
		TEMPLATE_U Vector<T>	&scaleDown(const T &scalar); // divide by scalar

		TEMPLATE_U Vector<T>	&linComb(const Vector<T> &other, const U &factor1, const U &factor2); // linear combination with 1 vector
		TEMPLATE_U Vector<T>	&linComb(const std::list<Vector<T>> &others, const std::list<U> &factors, const U &factor1); // linear combination with multiple vectors

		T						lerp(const Vector<T> &other, const T &factor) const; // linear interpolation
		T						dot(const Vector<T> &other) const; // dot product
	
		Vector<T>				&cross(const Vector<T> &other); // cross product
		float					norm1() const; // Manhattan norm (sum of abs values)
		float					norm() const; // Euclidean norm (len of vector)
		float					normInf() const; // Infinity norm (max abs value)

		Vector<T>				&normalize(); // resize to unit vector
		Vector<T>				&resize(const T &len); // resize vector to len
		Vector<T>				&clamp(const T &min, const T &max); // clamp values between min and max

		Vector<T>				&apply(T (*func)(T)); // apply function to each element
		Vector<T>				&apply(T (*func)(const T &)); // apply function to each element

		Vector<T>				&reflect(const Vector<T> &normal); // reflect vector on normal
		Vector<T>				&refract(const Vector<T> &normal, const T &eta); // refract vector on normal with eta
		Vector<T>				&project(const Vector<T> &other, const Vector<T> &axis); // project vector on other vector along axis
	
		Vector<T>				&rotate(const T &angle); // rotate vector by angle
		Vector<T>				&rotate(const Vector<T> &axis, const T &angle, const Vector<T> &center); // rotate vector around axis by angle around center
		float					cos(const Vector<T> &other) const; // cosine of angle between vectors
		float					angle(const Vector<T> &other) const; // angle between vectors

		float					dist(const Vector<T> &other) const; // distance between vectors

		Vector<T>				&transform(const tlap::Matrix<T> &matrix); // transform vector by matrix

		float					len() const; // length of vector
		size_t					shape() const; // dimension of vector
		Vector<T>				&reshape(size_t size); // resize vector
		void					print() const; // print vector "Vector{X}D: [x1, x2, ..., xn]"
};

} // namespace tlap

#include "Vector.tpp" // implementations