#include "JomGabbar.h"

#include "Character.h"
#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "Engine.h"
#include "PeriodicRefreshBuff.h"

JomGabbar::JomGabbar(Character* pchar):
    Buff(pchar, "Jom Gabbar", "Assets/items/Inv_misc_enggizmos_19.png", 20, 0),
    curr_stacks(0),
    max_stacks(10)
{}

void JomGabbar::buff_effect_when_applied() {
    auto* event = new PeriodicRefreshBuff(pchar, this, pchar->get_engine()->get_current_priority() + 2.0);
    pchar->get_engine()->add_event(event);

    ++curr_stacks;
    pchar->get_stats()->increase_melee_ap(65);
    pchar->get_stats()->increase_ranged_ap(65);
}

void JomGabbar::buff_effect_when_removed() {
    unsigned reduction = curr_stacks * 65;

    pchar->get_stats()->decrease_melee_ap(reduction);
    pchar->get_stats()->decrease_ranged_ap(reduction);

    reset_effect();
}

void JomGabbar::buff_effect_when_refreshed() {
    if (curr_stacks == max_stacks)
        return;

    buff_effect_when_applied();
}

void JomGabbar::reset_effect() {
    curr_stacks = 0;
}
