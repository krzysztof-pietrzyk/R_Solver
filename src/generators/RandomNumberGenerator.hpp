#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

#include <random>
#include <chrono>
#include <limits.h>
#include <cstdint>

class RandomNumberGenerator
{
    public:

    static uint64_t GetRandom();

    RandomNumberGenerator() = delete;
    ~RandomNumberGenerator() = delete;

    private:

    static int64_t seed;
    static std::minstd_rand rng;
	static std::uniform_int_distribution<uint64_t> distribution;
};

#endif
