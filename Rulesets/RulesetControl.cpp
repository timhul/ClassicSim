
#include "ActiveBuffs.h"
#include "Character.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Execute.h"
#include "GeneralBuffs.h"
#include "EssenceOfTheRed.h"
#include "SimSettings.h"
#include "RulesetControl.h"

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
        break;
    }
}

void RulesetControl::use_vaelastrasz_ruleset(Character* pchar, SimSettings* sim_settings) {
    Buff* buff = pchar->get_active_buffs()->get_general_buffs()->get_general_buff_by_name("Essence of the Red");

    assert(buff != nullptr);

    if (!buff->is_enabled())
        buff->enable_buff();

    buff->apply_buff();

    auto* warr = dynamic_cast<Warrior*>(pchar);
    if (warr != nullptr)
        dynamic_cast<WarriorSpells*>(warr->get_spells())->get_execute()->set_execute_treshold(0.67);

    sim_settings->set_execute_threshold(0.67);
}

void RulesetControl::remove_vaelastrasz_ruleset(Character* pchar, SimSettings* sim_settings) {
    Buff* buff = pchar->get_active_buffs()->get_general_buffs()->get_general_buff_by_name("Essence of the Red");

    assert(buff != nullptr);

    buff->reset();

    if (buff->is_enabled())
        buff->disable_buff();

    auto* warr = dynamic_cast<Warrior*>(pchar);
    if (warr != nullptr)
        dynamic_cast<WarriorSpells*>(warr->get_spells())->get_execute()->reset_execute_treshold();

    sim_settings->clear_execute_threshold();
}