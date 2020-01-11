#include "ThistleTea.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Rogue.h"
#include "StatisticsResource.h"

ThistleTea::ThistleTea(Rogue *rogue) :
    Spell("Thistle Tea", "Assets/misc/Inv_drink_milk_05.png", rogue, new CooldownControl(rogue, 300.0), RestrictedByGcd::No, ResourceType::Energy, 0)
{}

ThistleTea::~ThistleTea() {
    delete cooldown;
}

void ThistleTea::spell_effect() {
    const unsigned before_gain = pchar->get_resource_level(ResourceType::Energy);

    pchar->gain_energy(100);

    const unsigned delta = pchar->get_resource_level(ResourceType::Energy) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Energy, delta);
}

void ThistleTea::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
