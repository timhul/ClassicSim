
#include "AngerManagement.h"
#include "ClassStatistics.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Resource.h"
#include "ResourceGain.h"
#include "StatisticsResource.h"

AngerManagement::AngerManagement(Character* pchar) :
    Spell("Anger Management", "Assets/warrior/arms/tier3/anger_management.png", pchar, RestrictedByGcd::No, 0.0, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Anger Management", 1, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    statistics_resource(nullptr)
{}

void AngerManagement::increase_talent_rank_effect(const int, const QString&) {
    dynamic_cast<WarriorSpells*>(warr->get_spells())->add_pre_combat_spell(this);
}

void AngerManagement::decrease_talent_rank_effect(const int, const QString&) {
    dynamic_cast<WarriorSpells*>(warr->get_spells())->remove_pre_combat_spell(this);
}

void AngerManagement::spell_effect() {
    auto* new_event = new ResourceGain(pchar, this, engine->get_current_priority() + 1.5);
    this->engine->add_event(new_event);
}

void AngerManagement::perform_periodic() {
    unsigned rage_before_am_tick = warr->get_resource_level(resource_type);
    warr->gain_rage(1);

    if (rage_before_am_tick < warr->get_resource_level(resource_type))
        statistics_resource->add_resource_gain(ResourceType::Rage, 1);

    auto* new_event = new ResourceGain(pchar, this, engine->get_current_priority() + 3.0);
    this->engine->add_event(new_event);
}

void AngerManagement::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
