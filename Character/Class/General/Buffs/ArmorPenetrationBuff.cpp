
#include "ArmorPenetrationBuff.h"
#include "Character.h"
#include "Target.h"
#include <cassert>
#include <QDebug>

ArmorPenetrationBuff::ArmorPenetrationBuff(Character* pchar, const QString& name, const int reduction, const int max_stacks, const int duration):
    Buff(pchar, name, duration, 0)
{
    this->current_stacks = 0;
    this->max_stacks = max_stacks;
    this->reduction_per_stack = reduction;
}

void ArmorPenetrationBuff::buff_effect_when_applied() {
    ++current_stacks;
    assert(current_stacks <= max_stacks);

    pchar->get_target()->decrease_armor(reduction_per_stack);
}

void ArmorPenetrationBuff::buff_effect_when_removed() {
    pchar->get_target()->increase_armor(reduction_per_stack * current_stacks);
    current_stacks = 0;
}

void ArmorPenetrationBuff::buff_effect_when_refreshed() {
    if (current_stacks == max_stacks)
        return;

    buff_effect_when_applied();
}
