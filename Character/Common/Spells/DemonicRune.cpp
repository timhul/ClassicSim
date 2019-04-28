#include "DemonicRune.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "Random.h"
#include "StatisticsResource.h"

DemonicRune::DemonicRune(Character* pchar) :
    Spell("Demonic Rune", "Assets/misc/Inv_misc_rune_04.png", pchar, RestrictedByGcd::No, 120, ResourceType::Mana, 0),
    random(new Random(min, max))
{}

DemonicRune::~DemonicRune() {
    delete random;
}

void DemonicRune::spell_effect() {
    const unsigned before_gain = pchar->get_resource_level(ResourceType::Mana);
    const unsigned mana_gain = random->get_roll();

    pchar->gain_mana(mana_gain);

    const unsigned delta = pchar->get_resource_level(ResourceType::Mana) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

SpellStatus DemonicRune::is_ready_spell_specific() const {
    const unsigned delta = pchar->get_max_resource_level(ResourceType::Mana) - pchar->get_resource_level(ResourceType::Mana);
    return delta < max ? SpellStatus::OvercapResource : SpellStatus::Available;
}

void DemonicRune::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
