#include "ManaPotion.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Random.h"
#include "StatisticsResource.h"

ManaPotion::ManaPotion(Character* pchar) :
    Spell("Mana Potion", "Assets/misc/Inv_potion_76.png", pchar, new CooldownControl(pchar, 120.0), RestrictedByGcd::No, ResourceType::Mana, 0),
    random(new Random(min, max))
{}

ManaPotion::~ManaPotion() {
    delete random;
    delete cooldown;
}

void ManaPotion::spell_effect() {
    const unsigned before_gain = pchar->get_resource_level(ResourceType::Mana);
    const unsigned mana_gain = random->get_roll();

    pchar->gain_mana(mana_gain);

    const unsigned delta = pchar->get_resource_level(ResourceType::Mana) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

SpellStatus ManaPotion::is_ready_spell_specific() const {
    const unsigned delta = pchar->get_max_resource_level(ResourceType::Mana) - pchar->get_resource_level(ResourceType::Mana);
    return delta < max ? SpellStatus::OvercapResource : SpellStatus::Available;
}

void ManaPotion::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
