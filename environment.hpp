#include "Eigen/Eigen"

#define DELTA_T 0.16

typedef struct
{
    float radius;
    float weight;
    Eigen::Vector2f gravity;
    Eigen::Vector2f attachment;
} configuration_t;

typedef struct
{
    Eigen::Vector2f position;
    Eigen::Vector2f velocity;
} state_t;

state_t *initial_state(configuration_t &);

void print_state(state_t *);

void update_state(configuration_t *, state_t *);

Eigen::Vector2f translate(int, int, float, Eigen::Vector2f &);