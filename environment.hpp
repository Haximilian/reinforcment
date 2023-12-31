#include "Eigen/Eigen"

#define DELTA_T 0.032
#define SPRINT_CONSTANT 0.16

typedef struct
{
    float radius;
    float weight;
    Eigen::Vector2d gravity;
    Eigen::Vector2d attachment;
} configuration_t;

typedef struct
{
    Eigen::Vector2d position;
    Eigen::Vector2d velocity;
} state_t;

state_t *initial_state(configuration_t &);

void print_state(state_t *);

void update_state(configuration_t *, state_t *);

Eigen::Vector2d translate(int, int, float, Eigen::Vector2d &);