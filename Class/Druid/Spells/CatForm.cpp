#include "CatForm.h"

#include <cmath>

#include "Buff.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "StatisticsResource.h"

CatForm::CatForm(Druid* druid, Buff* cat_form) :
    Spell("Cat Form", "Assets/ability/Ability_druid_catform.png", druid, new CooldownControl(druid, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 100),
    TalentRequirer({
        new TalentRequirerInfo("Natural Shapeshifter", 3, DisabledAtZero::No),
        new TalentRequirerInfo("Sharpened Claws", 3, DisabledAtZero::No),
    }),
    ItemModificationRequirer({8345}),
    druid(druid),
    buff(cat_form),
    base_resource_cost(resource_cost) {
    buff->enable_buff();
}

CatForm::~CatForm() {
    delete cooldown;
}

void CatForm::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics("Wolfshead Helm", "Assets/items/Inv_helmet_04.png");
}

SpellStatus CatForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Cat)
        return SpellStatus::InCatForm;

    return SpellStatus::Available;
}

void CatForm::spell_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(resource_cost)));
    druid->switch_to_form(DruidForm::Cat);
    gain_energy(wolfshead_bonus);
}

void CatForm::gain_energy(const unsigned energy) {
    if (energy == 0)
        return;

    const unsigned before_gain = druid->get_resource_level(ResourceType::Energy);

    druid->gain_energy(energy);

    const unsigned delta = druid->get_resource_level(ResourceType::Energy) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Energy, delta);
}

void CatForm::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Natural Shapeshifter")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}

void CatForm::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Natural Shapeshifter")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}

void CatForm::activate_item_effect(const int) {
    wolfshead_bonus = 20;
}

void CatForm::deactivate_item_effect(const int) {
    wolfshead_bonus = 0;
}
