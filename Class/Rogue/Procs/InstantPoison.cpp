#include "InstantPoison.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "EnchantName.h"
#include "InstantPoisonBuff.h"
#include "ItemNamespace.h"
#include "MagicSchools.h"
#include "ProcInfo.h"
#include "Random.h"
#include "Rogue.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

InstantPoison::InstantPoison(Rogue* rogue, EnchantInfo* enchant_info, const QString& weapon_side, const int weapon) :
    Proc("Instant Poison " + weapon_side, "Assets/ability/Ability_poisons.png", 0.2, 0, QVector<Proc*>(), QVector<ProcInfo::Source>(), rogue),
    Enchant(EnchantName::Name::InstantPoison, enchant_info),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Vile Poisons", 5, DisabledAtZero::No),
                                                 new TalentRequirerInfo("Improved Poisons", 5, DisabledAtZero::No)}),
    SetBonusRequirer({"Bloodfang Armor"}),
    dmg_roll(new Random(112, 149)),
    rogue(rogue),
    vile_poisons(1.0) {
    this->enabled = false;
    this->instant_poison_buff = new InstantPoisonBuff(rogue, this, weapon_side);

    vile_poisons_modifiers = {1.0, 1.04, 1.08, 1.12, 1.16, 1.20};
    improved_poisons_increase = 200;

    switch (weapon) {
    case EnchantSlot::MAINHAND:
        proc_sources.append({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing});
        break;
    case EnchantSlot::OFFHAND:
        proc_sources.append({ProcInfo::Source::OffhandSwing});
        break;
    default:
        check(false, "InstantPoison constructor reached end of switch");
    }
}

InstantPoison::~InstantPoison() {
    disable();
    delete instant_poison_buff;
}

void InstantPoison::perform_start_of_combat() {
    instant_poison_buff->apply_buff();
}

void InstantPoison::enable_spell_effect() {
    instant_poison_buff->enable_buff();
    rogue->get_spells()->add_spell_group({this});
    rogue->get_spells()->add_start_of_combat_spell(this);
}

void InstantPoison::disable_spell_effect() {
    rogue->get_spells()->remove_spell(this);
    rogue->get_spells()->remove_start_of_combat_spell(this);

    if (instant_poison_buff->is_enabled()) {
        instant_poison_buff->cancel_buff();
        instant_poison_buff->disable_buff();
    }
}

void InstantPoison::proc_effect() {
    instant_poison_buff->use_charge();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Nature, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Nature);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    unsigned damage_dealt = dmg_roll->get_roll();
    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Nature);
        add_spell_crit_dmg(static_cast<int>(round(damage_dealt * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod * vile_poisons)),
                           resource_cost, 0, resist_roll);
    } else {
        pchar->spell_hit_effect(MagicSchool::Nature);
        add_spell_hit_dmg(static_cast<int>(round(damage_dealt * resist_mod * vile_poisons)), resource_cost, 0, resist_roll);
    }
}

void InstantPoison::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Poisons")
        proc_range += improved_poisons_increase;
    else if (talent_name == "Vile Poisons")
        vile_poisons = vile_poisons_modifiers[curr];
}

void InstantPoison::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Poisons")
        proc_range -= improved_poisons_increase;
    else if (talent_name == "Vile Poisons")
        vile_poisons = vile_poisons_modifiers[curr];
}

void InstantPoison::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Bloodfang Armor") {
        switch (set_bonus) {
        case 3:
            proc_range += 500;
            break;
        default:
            check(false, "InstantPoison::activate_set_bonus_effect reached end of switch");
        }
    }
}

void InstantPoison::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Bloodfang Armor") {
        switch (set_bonus) {
        case 3:
            proc_range -= 500;
            break;
        default:
            check(false, "InstantPoison::deactivate_set_bonus_effect reached end of switch");
        }
    }
}

void InstantPoison::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_spell = pchar->get_statistics()->get_spell_statistics(Spell::name, icon, spell_rank);
}
