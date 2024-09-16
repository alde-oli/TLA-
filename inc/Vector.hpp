// Author: alde-oli, date: 15/09/2024
// Description: Vector class with a focus on performance
// File version: 0.1

#pragma once
#include <concepts>

template <typename T, size_t N>
requires std::is_arithmetic_v<T>
class Vector {
	private:
		T data[N];

	public:
		Vector();
		Vector(const Vector<T, N>& other);
		Vector(Vector<T, N>&& other) noexcept;
		~Vector();

		Vector<T, N>		&operator=(const Vector<T, N>& other);
		Vector<T, N>		&operator=(Vector<T, N>&& other) noexcept;
		friend std::ostream	&operator<<(std::ostream& os, const Vector<T, N>& vector);

		const T				&operator[](size_t index) const;
		T					&operator[](size_t index);

		void				add(const Vector<T, N>& other);

		void				print() const;
};

// Inclusion du fichier .tpp avec les implémentations
#include "../src/Vector.tpp"