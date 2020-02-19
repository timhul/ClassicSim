#include "CooldownControl.h"

#include "Character.h"
#include "Engine.h"
#include "PlayerAction.h"

CooldownControl::CooldownControl(Character* pchar, double cooldown) :
    pchar(pchar), engine(pchar->get_engine()), base(cooldown), last_used(0 - cooldown) {}

double CooldownControl::get_next_use() const {
    return last_used + base;
}

void CooldownControl::reset() {
    last_used = 0 - base;
}

double CooldownControl::get_cooldown_remaining() const {
    double delta = last_used + base - engine->get_current_priority();

    return delta > 0 ? delta : 0;
}

void CooldownControl::add_spell_cd_event() const {
    double cooldown_ready = engine->get_current_priority() + base;
    engine->add_event(new PlayerAction(pchar->get_spells(), cooldown_ready));
}

void CooldownControl::add_gcd_event() const {
    if (engine->get_current_priority() < 0)
        return;

    pchar->start_global_cooldown();
    double gcd_ready = engine->get_current_priority() + pchar->global_cooldown();
    engine->add_event(new PlayerAction(pchar->get_spells(), gcd_ready));
}
