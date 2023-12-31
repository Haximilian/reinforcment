#include <math.h>
#include <iostream>

#include "environment.hpp"

state_t *initial_state(configuration_t &configuration)
{
    state_t *initial_state = (state_t *)malloc(sizeof(state_t));

    // todo: generate randomly
    float initial_angle = M_PI_4;

    initial_state->position = Eigen::Vector2d(
        cos(initial_angle) * configuration.radius,
        sin(initial_angle) * configuration.radius);
    initial_state->velocity = Eigen::Vector2d(0, 0);

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
    Eigen::Vector2d constraint_force = lambda * state->position;

    // correction / sprint force
    Eigen::Vector2d origin(0, 0);
    float origin_displacement = sqrt((state->position - origin).dot(state->position - origin));
    float spring_displacement = origin_displacement - configuration->radius;
    Eigen::Vector2d spring_unit_vector = (state->position - origin) / origin_displacement;
    Eigen::Vector2d spring_force = SPRINT_CONSTANT * spring_displacement * (-1) * spring_unit_vector;

    Eigen::Vector2d acceleration = configuration->gravity + constraint_force + spring_force / configuration->weight;

    state->velocity = state->velocity + DELTA_T * acceleration;
    state->position = state->position + DELTA_T * state->velocity;
}

Eigen::Vector2d translate(int width, int height, float magnification, Eigen::Vector2d &in)
{
    // (0, 0) -> top right
    float x = (width / 2) + in(0) * magnification;
    float y = (height / 2) + in(1) * magnification * (-1);

    return Eigen::Vector2d(x, y);
}