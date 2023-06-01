#include <stdio.h>
#include <stdlib.h>

enum
{
    A = 1103515245u,
    C = 12345u,
    M = 2147483648u
};

struct RandomOperations
{
    void (*destroy)();
    unsigned int (*next)();
};

typedef struct RandomGenerator
{
    struct RandomOperations *ops;
    unsigned int x;
} RandomGenerator;

void destroy_f(RandomGenerator *rr) {
    free(rr->ops);
    free(rr);
}

unsigned int next_f(RandomGenerator *rr) {
    rr->x = (rr->x * A + C) % M;
    return rr->x;
}

RandomGenerator *random_create(int seed){
    RandomGenerator *rg;
    rg = calloc (1, sizeof(struct RandomGenerator));
    rg->ops = calloc (1, sizeof(struct RandomOperations));
    rg->ops->next = next_f;
    rg->ops->destroy = destroy_f;
    rg->x = seed;
    return rg;
}
