#include "CharacterStats.h"
#include "Equipment.h"
#include "Random.h"
#include "Rogue.h"
#include "SliceAndDice.h"
#include "SliceAndDiceBuff.h"
#include "Weapon.h"

SliceAndDice::SliceAndDice(Character* pchar) :
    Spell("Slice and Dice", "Assets/ability/Ability_rogue_slicedice.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 25),
    rogue(dynamic_cast<Rogue*>(pchar)),
    buff(new SliceAndDiceBuff(rogue))
{
    buff->enable_buff();
}

SliceAndDice::~SliceAndDice() {
    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
}

bool SliceAndDice::is_ready_spell_specific() const {
    return rogue->get_combo_points() > 0;
}

void SliceAndDice::spell_effect() {
    rogue->exit_stealth();

    add_gcd_event();

    buff->update_duration(rogue->get_combo_points());
    buff->apply_buff();

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->spend_combo_points();
}
