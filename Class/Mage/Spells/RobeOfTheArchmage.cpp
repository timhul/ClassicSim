#include "RobeOfTheArchmage.h"

#include "Character.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Random.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

RobeOfTheArchmage::RobeOfTheArchmage(Character* pchar) :
    Spell("Robe of the Archmage",
          "Assets/items/Inv_chest_cloth_38.png",
          pchar,
          new CooldownControl(pchar, 300.0),
          RestrictedByGcd::No,
          ResourceType::Mana,
          0),
    ItemModificationRequirer({14152}),
    random(new Random(min, max)) {
    enabled = false;
}

RobeOfTheArchmage::~RobeOfTheArchmage() {
    delete random;
    delete cooldown;
}

void RobeOfTheArchmage::spell_effect() {
    const unsigned before_gain = pchar->get_resource_level(ResourceType::Mana);
    const unsigned mana_gain = random->get_roll();

    pchar->gain_mana(mana_gain);

    const unsigned delta = pchar->get_resource_level(ResourceType::Mana) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

SpellStatus RobeOfTheArchmage::is_ready_spell_specific() const {
    const unsigned delta = pchar->get_max_resource_level(ResourceType::Mana) - pchar->get_resource_level(ResourceType::Mana);
    return delta < max ? SpellStatus::OvercapResource : SpellStatus::Available;
}

void RobeOfTheArchmage::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}

void RobeOfTheArchmage::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 14152:
        enable();
        break;
    default:
        check(false, "RobeOfTheArchmage::activate_item_effect reached end of switch");
    }
}

void RobeOfTheArchmage::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 14152:
        disable();
        break;
    default:
        check(false, "RobeOfTheArchmage::deactivate_item_effect reached end of switch");
    }
}
