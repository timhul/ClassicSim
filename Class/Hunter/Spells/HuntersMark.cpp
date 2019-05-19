#include "HuntersMark.h"

#include "Character.h"
#include "CooldownControl.h"
#include "HuntersMarkBuff.h"

HuntersMark::HuntersMark(Character* pchar) :
    Spell("Hunter's Mark",
          "Assets/ability/Ability_hunter_snipershot.png",
          pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          60),
    hunters_mark(new HuntersMarkBuff(pchar))
{
    hunters_mark->enable_buff();
}

HuntersMark::~HuntersMark() {
    if (hunters_mark->is_enabled())
        hunters_mark->disable_buff();

    delete hunters_mark;
    delete cooldown;
}

void HuntersMark::spell_effect() {
    cooldown->add_gcd_event();
    pchar->lose_mana(resource_cost);
    hunters_mark->apply_buff();
}

Buff* HuntersMark::get_hunters_mark_buff() const {
    return hunters_mark;
}
