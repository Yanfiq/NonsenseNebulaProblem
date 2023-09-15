#include "RNG.h"

namespace RNG {
    int generateRandomInteger(int num_1, int num_2) {

        int min = (num_1 < num_2) ? num_1 : num_2;
        int max = (min == num_1) ? num_2 : num_1;

        // Define the random number generator engine
        std::random_device rd;
        std::default_random_engine rng(rd());

        // Define the uniform integer distribution using the specified range
        std::uniform_int_distribution<int> dist(min, max);

        // Generate and return a random integer number within the specified range
        return dist(rng);
    }

    float generateRandomFloat(float num_1, float num_2) {

        float min = (num_1 < num_2) ? num_1 : num_2;
        float max = (min == num_1) ? num_2 : num_1;

        // Seed the random number generator with the current time
        static std::mt19937 rng(static_cast<unsigned>(std::time(0)));

        // Define the distribution for floating-point numbers
        std::uniform_real_distribution<float> dist(min, max);

        // Generate and return a random float number within the specified range
        return dist(rng);
    }
}