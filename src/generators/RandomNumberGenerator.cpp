// implemented header
#include "RandomNumberGenerator.hpp"

// project includes

// std includes
#include <chrono>


int64_t RandomNumberGenerator::seed = std::chrono::system_clock::now().time_since_epoch().count();

std::minstd_rand RandomNumberGenerator::rng = std::minstd_rand(RandomNumberGenerator::seed);

std::uniform_int_distribution<uint64_t> RandomNumberGenerator::distribution = std::uniform_int_distribution<uint64_t>(0U, UINT64_MAX);

uint64_t RandomNumberGenerator::GetRandom()
{
    return distribution(rng);
}
