
#include "MainhandAttack.h"

int MainhandAttack::spell_effect(const int) const {
    // TODO: Roll white hit table and damage in order to determine resource generation.
    // TODO: Check if Windfury is up, roll extra attacks.

    // TODO: Find weapon skill for mainhand.
    AttackResult* result = roll->get_melee_hit_result(300);

    if (result->is_miss())
        return 0;
    // TODO: Apply Overpower
    if (result->is_dodge())
        return 0;
    if (result->is_parry())
        return 0;
    // TODO: Apply Flurry
    if (result->is_critical())
        return 30;
    if (result->is_glancing())
        return 10;

    return 15;
}
