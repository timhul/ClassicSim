#include "Ignite.h"

#include "CharacterSpells.h"
#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "IgniteBuff.h"
#include "Mage.h"
#include "Utils/Check.h"

Ignite::Ignite(Mage* pchar, IgniteBuff* ignite_buff) :
    Spell("Ignite", "Assets/spell/Spell_fire_incinerate.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Ignite", 5, DisabledAtZero::Yes)}),
    ignite_buff(ignite_buff)
{
    enabled = false;
}

Ignite::~Ignite() {
    delete cooldown;
}

void Ignite::inflict_ignite(const double original_dmg) {
    if (!is_enabled())
        return;

    if (!ignite_buff->is_active())
        pchar->get_engine()->add_event(new DotTick(this, pchar->get_engine()->get_current_priority() + 1.0));

    ignite_buff->apply_buff();
    ignite_buff->increase_ignite_size(original_dmg * ignite_percentage, pchar->instance_id);

    if (is_current_owner())
        current_iteration = ignite_buff->get_current_iteration();
}

void Ignite::perform_periodic() {
    if (!is_current_owner())
        return;

    if (current_iteration != ignite_buff->get_current_iteration())
        return;

    if (!ignite_buff->is_active())
        return;

    add_hit_dmg(static_cast<int>(std::round(ignite_buff->get_tick_size())), 0, 0);

    pchar->get_engine()->add_event(new DotTick(this, pchar->get_engine()->get_current_priority() + 1.0));
}

void Ignite::spell_effect() {
    check(false, "Ignite::perform() is not callable, use inflict_ignite()");
}

bool Ignite::is_current_owner() const {
    return pchar->instance_id == ignite_buff->get_current_owner();
}

void Ignite::increase_talent_rank_effect(const QString&, const int curr) {
    ignite_percentage = ignite_ranks[curr];
}

void Ignite::decrease_talent_rank_effect(const QString&, const int curr) {
    ignite_percentage = ignite_ranks[curr];
}
