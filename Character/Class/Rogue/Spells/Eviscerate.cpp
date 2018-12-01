#include "CharacterStats.h"
#include "Equipment.h"
#include "Eviscerate.h"
#include "Random.h"
#include "Rogue.h"
#include "Weapon.h"

Eviscerate::Eviscerate(Character* pchar) :
    Spell("Eviscerate", "Assets/ability/Ability_rogue_eviscerate.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 35),
    TalentRequirer(3, DisabledAtZero::No),
    rogue(dynamic_cast<Rogue*>(pchar)),
    evisc_range(new Random(904, 1012)),
    total_dmg_modifier(1.0)
{
    this->damage_ranges_per_combo_point = {
        QPair<unsigned, unsigned>(224, 332),
        QPair<unsigned, unsigned>(394, 502),
        QPair<unsigned, unsigned>(564, 672),
        QPair<unsigned, unsigned>(734, 842),
        QPair<unsigned, unsigned>(904, 1012),
    };

    this->imp_evisc_modifiers = {1.0, 1.05, 1.10, 1.15};
    this->imp_evisc_modifier = imp_evisc_modifiers[curr_talent_rank];
}

Eviscerate::~Eviscerate() {
    delete evisc_range;
}

bool Eviscerate::is_ready_spell_specific() const {
    return rogue->get_combo_points() > 0;
}

void Eviscerate::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    set_evisc_range();
    double ap_modifier = rogue->get_stats()->get_melee_ap() * (rogue->get_combo_points() * 0.03);
    double damage_dealt = damage_after_modifiers((evisc_range->get_roll() + ap_modifier) * total_dmg_modifier);

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * rogue->get_ability_crit_dmg_mod());
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == AttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->spend_combo_points();
}

void Eviscerate::set_evisc_range() {
    int index = static_cast<int>(rogue->get_combo_points()) - 1;
    assert(index >= 0 && index <= damage_ranges_per_combo_point.size() -1);

    unsigned min = damage_ranges_per_combo_point[index].first;
    unsigned max = damage_ranges_per_combo_point[index].second;

    evisc_range->set_new_range(min, max);
}

void Eviscerate::update_dmg_modifier() {
    this->total_dmg_modifier = 1 * imp_evisc_modifier;
}

void Eviscerate::increase_talent_rank_effect(const QString& talent_name) {
    if (talent_name == "Improved Eviscerate")
        imp_evisc_modifier = imp_evisc_modifiers[curr_talent_rank];

    update_dmg_modifier();
}

void Eviscerate::decrease_talent_rank_effect(const QString& talent_name) {
    if (talent_name == "Improved Eviscerate")
        imp_evisc_modifier = imp_evisc_modifiers[curr_talent_rank];

    update_dmg_modifier();
}
