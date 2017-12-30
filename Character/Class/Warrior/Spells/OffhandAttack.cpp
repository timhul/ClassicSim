
#include "OffhandAttack.h"

int OffhandAttack::spell_effect(const int) const {
    // TODO: Roll white hit table and damage in order to determine resource generation.
    // TODO: Check if Windfury is up, roll extra attacks.
    // TODO: Take offhand dual-wield penalty into account.
    // TODO: Take dual-wield specialization into account.

    // TODO: Find weapon skill for offhand.
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
        return 20;
    if (result->is_glancing())
        return 6;

    return 10;
}
