#include "RulesetControl.h"

#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "EnabledBuffs.h"
#include "EssenceOfTheRed.h"
#include "Execute.h"
#include "GeneralBuffs.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Warrior.h"
#include "WarriorSpells.h"

RulesetControl::RulesetControl() :
    active_ruleset(Ruleset::Standard)
{}

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
        pchar->get_stats()->decrease_melee_crit(10000);
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
        pchar->get_stats()->increase_melee_crit(10000);
        pchar->get_combat_roll()->drop_tables();
        break;
    }
}

void RulesetControl::use_vaelastrasz_ruleset(Character* pchar, SimSettings* sim_settings) {
    Buff* buff = pchar->get_enabled_buffs()->get_general_buffs()->get_general_buff_by_name("Essence of the Red");

    check((buff != nullptr), "buff nullptr");
    buff->enable_buff();
    pchar->get_enabled_buffs()->add_start_of_combat_buff(buff);

    auto* warr = dynamic_cast<Warrior*>(pchar);
    if (warr != nullptr)
        dynamic_cast<WarriorSpells*>(warr->get_spells())->get_execute()->set_execute_threshold(2.0 / 3.0);

    sim_settings->set_execute_threshold(2.0 / 3.0);
}

void RulesetControl::remove_vaelastrasz_ruleset(Character* pchar, SimSettings* sim_settings) {
    Buff* buff = pchar->get_enabled_buffs()->get_general_buffs()->get_general_buff_by_name("Essence of the Red");

    check((buff != nullptr), "buff nullptr");

    pchar->get_enabled_buffs()->remove_start_of_combat_buff(buff);
    buff->disable_buff();

    auto* warr = dynamic_cast<Warrior*>(pchar);
    if (warr != nullptr)
        dynamic_cast<WarriorSpells*>(warr->get_spells())->get_execute()->reset_execute_threshold();

    sim_settings->reset_execute_threshold();
}
