#include "Ignite.h"

#include <cmath>

#include "CharacterSpells.h"
#include "Engine.h"
#include "IgniteBuff.h"
#include "Mage.h"
#include "Utils/Check.h"

Ignite::Ignite(Mage* pchar, IgniteBuff* ignite_buff) :
    SpellPeriodic("Ignite", "Assets/spell/Spell_fire_incinerate.png", pchar, ignite_buff, RestrictedByGcd::No, ResourceType::Mana, 1.0, 0),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Ignite", 5, DisabledAtZero::Yes)}),
    ignite_buff(ignite_buff) {
    enabled = false;
}

void Ignite::inflict_ignite(const double original_dmg) {
    perform();

    if (!ignite_buff->is_active())
        return;

    ignite_buff->increase_ignite_size(original_dmg * ignite_percentage, pchar->instance_id);

    if (is_current_owner())
        current_iteration = ignite_buff->get_current_iteration();
}

void Ignite::tick_effect() {
    if (!is_current_owner())
        return;

    if (current_iteration != ignite_buff->get_current_iteration())
        return;

    add_hit_dmg(static_cast<int>(std::round(ignite_buff->get_tick_size())), 0, 0);

    add_next_tick();
}

void Ignite::reset_effect() {}

bool Ignite::is_current_owner() const {
    return pchar->instance_id == ignite_buff->get_current_owner();
}

bool Ignite::check_application_success() {
    return true;
}

void Ignite::new_application_effect() {}

void Ignite::refresh_effect() {}

void Ignite::increase_talent_rank_effect(const QString&, const int curr) {
    ignite_percentage = ignite_ranks[curr];
}

void Ignite::decrease_talent_rank_effect(const QString&, const int curr) {
    ignite_percentage = ignite_ranks[curr];
}
