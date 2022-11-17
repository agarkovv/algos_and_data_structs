#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>

#include "random.h"
#include "random.h"  // check include guards

const auto kInfinity = std::numeric_limits<double>::infinity();

TEST_CASE("NormalProbability", "[Random]") {
  {
    auto first_gen = std::mt19937_64(0);
    auto second_gen = std::mt19937_64(11);
    REQUIRE(NormalProbability(-kInfinity, kInfinity, 10u, first_gen) == Approx(1.0));
    REQUIRE(NormalProbability(-kInfinity, kInfinity, 1000u, second_gen) == Approx(1.0));
  }

  {
    auto first_gen = std::mt19937_64(0);
    auto second_gen = std::mt19937_64(11);
    REQUIRE(NormalProbability(1, 1, 10u, first_gen) == Approx(0.0));
    REQUIRE(NormalProbability(1, 1, 1000u, second_gen) == Approx(0.0));
    REQUIRE(NormalProbability(5, -2, 10u, first_gen) == Approx(0.0));
    REQUIRE(NormalProbability(5, -2, 1000u, second_gen) == Approx(0.0));
  }

  {
    auto first_gen = std::mt19937_64(11);
    auto second_gen = std::mt19937_64(11);
    REQUIRE(NormalProbability(1, 3, 1000u, first_gen) == NormalProbability(1, 3, 1000u, second_gen));
    REQUIRE(NormalProbability(1, 3, 1000u, first_gen) != NormalProbability(1, 3, 10000u, second_gen));
    REQUIRE(NormalProbability(1, 3, 1000u, first_gen) != NormalProbability(1, 3, 1000u, first_gen));
  }

  auto generator = std::mt19937_64(11);
  REQUIRE(NormalProbability(-1, 3, 100u, generator) == Approx(0.84).epsilon(0.1));
  std::cerr << "NormalProbability 1/4" << std::endl;
  REQUIRE(NormalProbability(-1, 3, 10'000u, generator) == Approx(0.84).epsilon(0.01));
  std::cerr << "NormalProbability 2/4" << std::endl;
  REQUIRE(NormalProbability(-1, 3, 1'000'000u, generator) == Approx(0.84).epsilon(0.001));
  std::cerr << "NormalProbability 3/4" << std::endl;
  REQUIRE(NormalProbability(-1, 3, 100'000'000u, generator) == Approx(0.84).epsilon(0.0001));
  std::cerr << "NormalProbability 4/4" << std::endl;
}

TEST_CASE("MonteCarloPi", "[Random]") {
  {
    auto first_gen = std::mt19937_64(11);
    auto second_gen = std::mt19937_64(11);
    REQUIRE(MonteCarloPi(1000u, first_gen) == MonteCarloPi(1000u, second_gen));
    REQUIRE(MonteCarloPi(1000u, first_gen) != MonteCarloPi(10000u, second_gen));
    REQUIRE(MonteCarloPi(1000u, first_gen) != MonteCarloPi(1000u, first_gen));
  }

  auto generator = std::mt19937_64(11);
  REQUIRE(MonteCarloPi(100u, generator) == Approx(3.14159265).epsilon(0.5));
  std::cerr << "MonteCarloPi 1/4" << std::endl;
  REQUIRE(MonteCarloPi(10'000u, generator) == Approx(3.14159265).epsilon(0.05));
  std::cerr << "MonteCarloPi 2/4" << std::endl;
  REQUIRE(MonteCarloPi(1'000'000u, generator) == Approx(3.14159265).epsilon(0.005));
  std::cerr << "MonteCarloPi 3/4" << std::endl;
  REQUIRE(MonteCarloPi(100'000'000u, generator) == Approx(3.14159265).epsilon(0.0005));
  std::cerr << "MonteCarloPi 4/4" << std::endl;
}
