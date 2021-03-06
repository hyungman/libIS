// ======================================================================== //
// Copyright 2018 Intel Corporation                                         //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include <cmath>
#include <stdexcept>
#include <ostream>

// Utility type for implementing the test simulation and renderer

template<typename T>
struct vec3 {
	T x, y, z;

	vec3(T x = 0) : x(x), y(x), z(x) {}
	vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	template<typename B>
	vec3(const vec3<B> &v) : x(v.x), y(v.y), z(v.z) {}
	vec3<T>& operator+=(const vec3<T> &a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}
	vec3<T>& operator-=(const vec3<T> &a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}
	vec3<T>& operator*=(const vec3<T> &a) {
		x *= a.x;
		y *= a.y;
		z *= a.z;
		return *this;
	}
	vec3<T>& operator/=(const vec3<T> &a) {
		x /= a.x;
		y /= a.y;
		z /= a.z;
		return *this;
	}

	const T& operator[](size_t i) const {
		switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
		throw std::runtime_error("Invalid index");
	}
	T& operator[](size_t i) {
		switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
		throw std::runtime_error("Invalid index");
	}
};

template<typename T>
vec3<T> operator*(const vec3<T> &a, const vec3<T> &b) {
	return vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}
template<typename T>
vec3<T> operator/(const vec3<T> &a, const vec3<T> &b) {
	return vec3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}
template<typename T>
vec3<T> operator+(const vec3<T> &a, const vec3<T> &b) {
	return vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}
template<typename T>
vec3<T> operator-(const vec3<T> &a, const vec3<T> &b) {
	return vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}
template<typename T>
vec3<T> operator%(const vec3<T> &a, const vec3<T> &b) {
	return vec3<T>(a.x % b.x, a.y % b.y, a.z % b.z);
}

template<typename T>
vec3<T> operator*(const vec3<T> &a, const T b) {
	return vec3<T>(a.x * b, a.y * b, a.z * b);
}
template<typename T>
vec3<T> operator*(const T b, const vec3<T> &a) {
	return vec3<T>(a.x * b, a.y * b, a.z * b);
}
template<typename T>
vec3<T> operator/(const vec3<T> &a, const T b) {
	return vec3<T>(a.x / b, a.y / b, a.z / b);
}
template<typename T>
std::ostream& operator<<(std::ostream &os, const vec3<T> &v) {
	os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

inline bool compute_divisor(int x, int &divisor) {
	int upper_bound = std::sqrt(x);
	for (int i = 2; i <= upper_bound; ++i) {
		if (x % i == 0) {
			divisor = i;
			return true;
		}
	}
	return false;
}

inline vec3<int> compute_grid(int num) {
	vec3<int> grid(1);
	int axis = 0;
	int divisor = 0;
	while (compute_divisor(num, divisor)) {
		grid[axis] *= divisor;
		num /= divisor;
		axis = (axis + 1) % 3;
	}
	if (num != 1) {
		grid[axis] *= num;
	}
	return grid;
}


