#include <math.h>
#include <iostream>

#include "environment.hpp"

state_t *initial_state(configuration_t &configuration)
{
    state_t *initial_state = (state_t *)malloc(sizeof(state_t));

    // todo: generate randomly
    float initial_angle = M_PI_4;

    initial_state->position = Eigen::Vector2f(
        cos(initial_angle) * configuration.radius,
        sin(initial_angle) * configuration.radius);
    initial_state->velocity = Eigen::Vector2f(0, 0);

    return initial_state;
}

void print_state(state_t *state)
{
    std::cout << "state->position: " << std::endl;
    std::cout << state->position << std::endl;
    std::cout << "state->velocity: " << std::endl;
    std::cout << state->velocity << std::endl;
    std::cout << "dot: " << std::endl;
    std::cout << state->velocity.dot(state->position) << std::endl;
}

void update_state(configuration_t *configuration, state_t *state)
{
    // a(t) -> object a position
    // C -> constraint
    // C(a, 0) = a(t) * a(t) - d**2
    // C(a, 0) = 0
    // dC / dt = 0
    // dC / dt = 2 * a'(t) * a(t)
    // therefore, velocity ⊥ position

    float numerator = (-1) * configuration->gravity.dot(state->position) - configuration->weight * state->velocity.dot(state->velocity);
    float denominator = state->position.dot(state->position);
    float lambda = numerator / denominator;
    Eigen::Vector2f constraint_force = lambda * state->position;
    Eigen::Vector2f acceleration = configuration->gravity + constraint_force;

    state->velocity = state->velocity + DELTA_T * acceleration;
    state->position = state->position + DELTA_T * state->velocity;

    // static float time = 0;
    // time += DELTA_T;
    // state->position = Eigen::Vector2f(configuration->radius * sin(time), configuration->radius * cos(time));
}

Eigen::Vector2f translate(int width, int height, float magnification, Eigen::Vector2f &in)
{
    // (0, 0) -> top right
    float x = (width / 2) + in(0) * magnification;
    float y = (height / 2) + in(1) * magnification;

    return Eigen::Vector2f(x, y);
}