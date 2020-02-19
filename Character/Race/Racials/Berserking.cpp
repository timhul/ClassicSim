#include "Berserking.h"

#include "BerserkingBuff.h"
#include "Character.h"
#include "CooldownControl.h"
#include "Race.h"

Berserking::Berserking(Character* pchar_, const ResourceType resource_type_, const unsigned resource_cost_) :
    Spell("Berserking",
          "Assets/races/Racial_troll_berserk.png",
          pchar_,
          new CooldownControl(pchar_, 180.0),
          RestrictedByGcd::Yes,
          resource_type_,
          resource_cost_),
    buff(new BerserkingBuff(pchar_)) {
    this->enabled = false;
}

Berserking::~Berserking() {
    delete buff;
    delete cooldown;
}

void Berserking::spell_effect() {
    buff->apply_buff();

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();
}

void Berserking::enable_spell_effect() {
    buff->enable_buff();
}

void Berserking::disable_spell_effect() {
    buff->disable_buff();
}
