#include "MageArmor.h"

#include "MageArmorBuff.h"
#include "CooldownControl.h"
#include "Mage.h"

MageArmor::MageArmor(Mage* pchar) :
    Spell("Mage Armor",
          "Assets/spell/Spell_arcane_mage_armor.png",
          pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          0,
          0),
    buff(new MageArmorBuff(pchar)) {
    buff->enable_buff();
}

MageArmor::~MageArmor() {
    delete buff;
    delete cooldown;
}

void MageArmor::spell_effect() {
    cooldown->add_gcd_event();
    buff->apply_buff();
}
