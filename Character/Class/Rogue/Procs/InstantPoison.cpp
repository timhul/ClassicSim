#include "InstantPoison.h"

#include "CharacterStats.h"
#include "EnchantName.h"
#include "ItemNamespace.h"
#include "InstantPoisonBuff.h"
#include "MagicSchools.h"
#include "ProcInfo.h"
#include "Random.h"
#include "Rogue.h"
#include "StatisticsResource.h"

InstantPoison::InstantPoison(Character* pchar, const QString& weapon_side, const int weapon) :
    Proc("Instant Poison " + weapon_side, "Assets/ability/Ability_poisons.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>(),
         pchar),
    Enchant(EnchantName::InstantPoison, "Instant Poison", "Instant Poison"),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Vile Poisons", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Improved Poisons", 5, DisabledAtZero::No)
                   }),
    dmg_roll(new Random(112, 149)),
    rogue(dynamic_cast<Rogue*>(pchar)),
    base_proc_range(2000)
{
    this->instant_poison_buff = new InstantPoisonBuff(pchar, this, weapon_side);
    this->instant_poison_buff->enable_buff();

    proc_range = base_proc_range;

    vile_poisons_modifiers = {1.0, 1.04, 1.08, 1.12, 1.16, 1.20};
    improved_poisons_proc_range_increases = {0, 200, 400, 600, 800, 1000};

    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);

    switch (weapon) {
    case EnchantSlot::MAINHAND:
        proc_sources.append({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing});
        break;
    case EnchantSlot::OFFHAND:
        proc_sources.append({ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing});
        break;
    }
}

InstantPoison::~InstantPoison() {
    instant_poison_buff->cancel_buff();
    instant_poison_buff->disable_buff();
    delete instant_poison_buff;
}

void InstantPoison::proc_effect() {
    instant_poison_buff->use_charge();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Nature, pchar->get_stats()->get_spell_crit_chance());
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Nature);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    unsigned damage_dealt = dmg_roll->get_roll();
    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * pchar->get_spell_crit_dmg_mod() * resist_mod * vile_poisons)), resource_cost, 0);
    }
    else {
        pchar->spell_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt * resist_mod * vile_poisons)), resource_cost, 0);
    }
}

void InstantPoison::increase_talent_rank_effect(const int curr, const QString& talent_name) {
    if (talent_name == "Improved Poisons")
        proc_range = base_proc_range + improved_poisons_proc_range_increases[curr];
    else if (talent_name == "Vile Poisons")
        vile_poisons = vile_poisons_modifiers[curr];
}

void InstantPoison::decrease_talent_rank_effect(const int curr, const QString& talent_name) {
    if (talent_name == "Improved Poisons")
        proc_range = base_proc_range + improved_poisons_proc_range_increases[curr];
    else if (talent_name == "Vile Poisons")
        vile_poisons = vile_poisons_modifiers[curr];
}

void InstantPoison::prepare_set_of_combat_iterations() {
    instant_poison_buff->apply_buff();
}
