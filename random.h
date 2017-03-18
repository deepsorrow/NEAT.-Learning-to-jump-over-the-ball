#pragma once
#include <random>
#include <algorithm>

class Random {
public:

	template <typename T>
	static auto Number(T min, T max) {
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(engine);
	}

	template <typename T>
	static inline auto DidChanceOccure(T chance) {
		auto randnum = Number(static_cast<T>(0.0), static_cast<T>(1.0));
		return randnum < chance;
	}

	static inline auto FlipACoin() {
		return Number(0, 1) == 0;
	}

private:
	 static std::random_device randomDevice;
	 static std::mt19937 engine;
};

template <>
inline auto Random::Number(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(engine);
}

template <>
inline auto Random::Number(double min, double max)
{
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(engine);
}