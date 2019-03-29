#include "RapidFire.h"

#include "Character.h"
#include "RapidFireBuff.h"

RapidFire::RapidFire(Character* pchar) :
    Spell("Rapid Fire",
          "Assets/ability/Ability_hunter_runningshot.png",
          pchar,
          RestrictedByGcd::Yes,
          0.0,
          ResourceType::Mana,
          100),
    rapid_fire(new RapidFireBuff(pchar))
{
    rapid_fire->enable_buff();
}

RapidFire::~RapidFire() {
    if (rapid_fire->is_enabled())
        rapid_fire->disable_buff();

    delete rapid_fire;
}

void RapidFire::spell_effect() {
    add_gcd_event();
    pchar->lose_mana(static_cast<unsigned>(resource_cost));
    rapid_fire->apply_buff();
}
