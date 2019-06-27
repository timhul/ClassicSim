#include "AngerManagement.h"

#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "Resource.h"
#include "ResourceGain.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"
#include "Warrior.h"
#include "WarriorSpells.h"

AngerManagement::AngerManagement(Character* pchar) :
    Spell("Anger Management", "Assets/spell/Spell_holy_blessingofstamina.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Anger Management", 1, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    statistics_resource(nullptr)
{
    this->enabled = false;
}

AngerManagement::~AngerManagement() {
    delete cooldown;
}

void AngerManagement::increase_talent_rank_effect(const QString&, const int) {
    dynamic_cast<WarriorSpells*>(warr->get_spells())->add_start_of_combat_spell(this);
}

void AngerManagement::decrease_talent_rank_effect(const QString&, const int) {
    dynamic_cast<WarriorSpells*>(warr->get_spells())->remove_start_of_combat_spell(this);
}

void AngerManagement::spell_effect() {
    check(false, "Not implemented");
}

void AngerManagement::perform_start_of_combat() {
    auto* new_event = new ResourceGain(this, engine->get_current_priority() + 1.5);
    this->engine->add_event(new_event);
}

void AngerManagement::perform_periodic() {
    unsigned rage_before_am_tick = warr->get_resource_level(resource_type);
    warr->gain_rage(1);

    if (rage_before_am_tick < warr->get_resource_level(resource_type))
        statistics_resource->add_resource_gain(ResourceType::Rage, 1);

    auto* new_event = new ResourceGain(this, engine->get_current_priority() + 3.0);
    this->engine->add_event(new_event);
}

void AngerManagement::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
