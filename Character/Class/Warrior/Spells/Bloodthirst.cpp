
#include "Bloodthirst.h"

int Bloodthirst::spell_effect(const int resource_level) const {
    // TODO: Roll special hit attack table and deal damage based on outcome.
    // TODO: Apply Flurry buff if critical.
    assert(resource_level >= resource_cost);


    return resource_cost;
}
