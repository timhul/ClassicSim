#include "ManaPotion.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "Random.h"
#include "StatisticsResource.h"

ManaPotion::ManaPotion(Character* pchar) :
    Spell("Mana Potion", "Assets/misc/Inv_potion_76.png", pchar, RestrictedByGcd::No, 120, ResourceType::Mana, 0),
    random(new Random(min, max))
{}

ManaPotion::~ManaPotion() {
    delete random;
}

void ManaPotion::spell_effect() {
    const unsigned before_gain = pchar->get_resource_level(ResourceType::Mana);
    const unsigned mana_gain = random->get_roll();

    pchar->gain_mana(mana_gain);

    const unsigned delta = pchar->get_resource_level(ResourceType::Mana) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

bool ManaPotion::is_ready_spell_specific() const {
    const unsigned delta = pchar->get_max_resource_level(ResourceType::Mana) - pchar->get_resource_level(ResourceType::Mana);
    return delta >= max;
}

void ManaPotion::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
