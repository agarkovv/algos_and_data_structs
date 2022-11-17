#ifndef OOP_ASSIGNMENTS_RANDOM_H
#define OOP_ASSIGNMENTS_RANDOM_H

#include <random>

[[nodiscard]] double NormalProbability(double low, double high, size_t n_samples, std::mt19937_64& generator);
[[nodiscard]] double MonteCarloPi(size_t n_samples, std::mt19937_64& generator);

#endif  // OOP_ASSIGNMENTS_RANDOM_H
