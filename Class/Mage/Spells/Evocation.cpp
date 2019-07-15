#include "Evocation.h"

#include "Buff.h"
#include "CooldownControl.h"
#include "EvocationBuff.h"

Evocation::Evocation(Character* pchar) :
    SpellPeriodic("Evocation", "Assets/spell/Spell_nature_purge.png", pchar, new EvocationBuff(pchar), RestrictedByGcd::Yes, ResourceType::Mana, 2.0, 0,  1),
    CastingTimeRequirer(pchar, 8000)
{
    delete cooldown;
    cooldown = new CooldownControl(pchar, 480.0);
    level_req = 20;

    enabled = true;
    marker_buff->enable_buff();
}

Evocation::~Evocation() {
    delete marker_buff;
}

void Evocation::complete_cast_effect() {
    marker_buff->cancel_buff();
}

bool Evocation::check_application_success() {
    return true;
}

void Evocation::new_application_effect() {
    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();

    start_cast();
}

void Evocation::refresh_effect() {

}

void Evocation::reset_effect() {

}

void Evocation::tick_effect() {

}
