#pragma once
#include <random>

inline std::random_device rand_dev;
inline std::mt19937 gen(rand_dev());