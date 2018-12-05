#include "CharacterStats.h"
#include "Equipment.h"
#include "Random.h"
#include "Rogue.h"
#include "RelentlessStrikes.h"
#include "Ruthlessness.h"
#include "SliceAndDice.h"
#include "SliceAndDiceBuff.h"
#include "Weapon.h"

SliceAndDice::SliceAndDice(Character* pchar) :
    Spell("Slice and Dice", "Assets/ability/Ability_rogue_slicedice.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 25),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Slice And Dice", 3, DisabledAtZero::No)}),
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

    if (rogue->get_relentless_strikes()->is_enabled()) {
        rogue->get_relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
        rogue->get_relentless_strikes()->perform();
    }

    rogue->spend_combo_points();

    if (rogue->get_ruthlessness()->is_enabled())
        rogue->get_ruthlessness()->perform();
}

void SliceAndDice::increase_talent_rank_effect(const int curr, const QString&) {
    buff->change_duration_modifier(curr);
}

void SliceAndDice::decrease_talent_rank_effect(const int curr, const QString&) {
    buff->change_duration_modifier(curr);
}
