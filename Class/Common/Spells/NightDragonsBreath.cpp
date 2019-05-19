#include "NightDragonsBreath.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Random.h"
#include "StatisticsResource.h"

NightDragonsBreath::NightDragonsBreath(Character* pchar) :
    Spell("Night Dragon's Breath", "Assets/misc/Inv_misc_food_45.png", pchar, new CooldownControl(pchar, 120.0), RestrictedByGcd::No, ResourceType::Mana, 0),
    random(new Random(min, max))
{}

NightDragonsBreath::~NightDragonsBreath() {
    delete random;
    delete cooldown;
}

void NightDragonsBreath::spell_effect() {
    const unsigned before_gain = pchar->get_resource_level(ResourceType::Mana);
    const unsigned mana_gain = random->get_roll();

    pchar->gain_mana(mana_gain);

    const unsigned delta = pchar->get_resource_level(ResourceType::Mana) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

SpellStatus NightDragonsBreath::is_ready_spell_specific() const {
    const unsigned delta = pchar->get_max_resource_level(ResourceType::Mana) - pchar->get_resource_level(ResourceType::Mana);
    return delta < max ? SpellStatus::OvercapResource : SpellStatus::Available;
}

void NightDragonsBreath::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
