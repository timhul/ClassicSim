#include "Evocation.h"

#include "Buff.h"
#include "CooldownControl.h"
#include "EvocationBuff.h"
#include "Mage.h"
#include "Utils/Check.h"

Evocation::Evocation(Mage* mage) :
    SpellPeriodic("Evocation",
                  "Assets/spell/Spell_nature_purge.png",
                  mage,
                  new EvocationBuff(mage),
                  RestrictedByGcd::Yes,
                  ResourceType::Mana,
                  2.0,
                  0,
                  1),
    CastingTimeRequirer(mage, SuppressibleCast::No, 8000),
    SetBonusRequirer({"Frostfire Regalia"}) {
    delete cooldown;
    cooldown = new CooldownControl(mage, 480.0);
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

void Evocation::refresh_effect() {}

void Evocation::reset_effect() {}

void Evocation::tick_effect() {}

void Evocation::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Frostfire Regalia") {
        switch (set_bonus) {
        case 2:
            cooldown->base -= 60.0;
            break;
        default:
            check(false, "Evocation::activate_set_bonus_effect reached end of switch");
        }
    }
}

void Evocation::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Frostfire Regalia") {
        switch (set_bonus) {
        case 2:
            cooldown->base += 60.0;
            break;
        default:
            check(false, "Evocation::deactivate_set_bonus_effect reached end of switch");
        }
    }
}
