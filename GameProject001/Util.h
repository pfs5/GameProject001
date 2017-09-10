#pragma once

#include <string>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace Util {
	const bool DEBUG_MODE = true;
	const float F_COMPARE_PREC = 1e-5;

	inline void printMessage(const std::string& _s) {
		if (DEBUG_MODE)
			std::cerr << "> " <<_s << std::endl;
	}

	inline void printMessage(const int& _i) {
		if (DEBUG_MODE) {
			std::cerr << "> " << std::to_string(_i) << std::endl;
		}
	}

	inline void printMessage(const float& _f) {
		if (DEBUG_MODE) {
			std::cerr << "> " << std::to_string(_f) << std::endl;
		}
	}

	inline void printVector(const sf::Vector2f& _v) {
		if (DEBUG_MODE) {
			std::cerr << "> " << "vector " << _v.x << " " << _v.y << std::endl;
		}
	}

	inline void printVector(const sf::Vector2i& _v) {
		if (DEBUG_MODE) {
			std::cerr << "> " << "vector " << _v.x << " " << _v.y << std::endl;
		}
	}

	inline int charToInt(const char& _c) {
		return _c - '0';
	}

	/**
		Random int in [low, high] interval
	**/
	inline int randomi(const int& _low, const int& _high) {
		return (rand() % (_high - _low + 1)) + _low;
		return 0;
	}

	/**
		Equality function for floats
	**/
	inline bool fcompare(const float& _a, const float& _b) {
		return fabsf(_a - _b) < F_COMPARE_PREC;
	}

	inline sf::Vector2f normalize(const sf::Vector2f& _v) {
		sf::Vector2f normalized = _v;
		normalized /= sqrtf(powf(_v.x, 2) + powf(_v.y, 2));
		return normalized;
	}

	inline float magnitude(const sf::Vector2f& _v) {
		return sqrtf(powf(_v.x, 2) + powf(_v.y, 2));
	}
}