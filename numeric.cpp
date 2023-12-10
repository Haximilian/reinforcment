#include <iostream>
#include <Eigen/Dense>

#include "environment.hpp"

#define ITERATIONS 16

int main(int argc, char** argv)
{
    configuration_t configuration = {
        5,
        1,
        Eigen::Vector2f(0, -9.81),
        Eigen::Vector2f(0, 0)
    };

    state_t* state = initial_state(configuration);
    print_state(state);

    for (int i = 0; i < ITERATIONS; i++) {
        std::cout << "----------------" << std::endl;

        update_state(&configuration, state);
        print_state(state);
    }

    return 0;
}