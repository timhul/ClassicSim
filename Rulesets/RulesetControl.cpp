#include "RulesetControl.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "SimSettings.h"
#include "Spell.h"
#include "SpellRankGroup.h"
#include "Utils/Check.h"

RulesetControl::RulesetControl() : active_ruleset(Ruleset::Standard) {}

Ruleset RulesetControl::get_active_ruleset() const {
    return this->active_ruleset;
}

void RulesetControl::use_ruleset(Ruleset ruleset, Character* pchar, SimSettings* sim_settings) {
    switch (active_ruleset) {
    case Ruleset::Standard:
        break;
    case Ruleset::Vaelastrasz:
        remove_vaelastrasz_ruleset(pchar, sim_settings);
        break;
    case Ruleset::Loatheb:
        pchar->get_stats()->decrease_melee_aura_crit(10000);
        pchar->get_combat_roll()->drop_tables();
        break;
    }

    this->active_ruleset = ruleset;

    switch (active_ruleset) {
    case Ruleset::Standard:
        break;
    case Ruleset::Vaelastrasz:
        use_vaelastrasz_ruleset(pchar, sim_settings);
        break;
    case Ruleset::Loatheb:
        pchar->get_stats()->increase_melee_aura_crit(10000);
        pchar->get_combat_roll()->drop_tables();
        break;
    }
}

void RulesetControl::use_vaelastrasz_ruleset(Character* pchar, SimSettings* sim_settings) {
    Spell* spell = pchar->get_spells()->get_spell_rank_group_by_name("Essence of the Red")->get_max_available_spell_rank();
    check((spell != nullptr), QString("Essence of the Red not found for %1").arg(pchar->class_name).toStdString());
    spell->enable();

    sim_settings->set_execute_threshold(2.0 / 3.0);
}

void RulesetControl::remove_vaelastrasz_ruleset(Character* pchar, SimSettings* sim_settings) {
    Spell* spell = pchar->get_spells()->get_spell_rank_group_by_name("Essence of the Red")->get_max_available_spell_rank();
    check((spell != nullptr), QString("Essence of the Red not found for %1").arg(pchar->class_name).toStdString());
    spell->disable();

    sim_settings->set_execute_threshold(0.2);
}
