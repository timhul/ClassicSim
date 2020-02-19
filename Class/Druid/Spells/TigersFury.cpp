#include "TigersFury.h"

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "SimSettings.h"
#include "TigersFuryBuff.h"
#include "Utils/Check.h"

TigersFury::TigersFury(Druid* pchar, DruidSpells* druid_spells, TigersFuryBuff* buff, const int spell_rank) :
    Spell("Tiger's Fury",
          "Assets/ability/Ability_mount_jungletiger.png",
          pchar,
          new CooldownControl(pchar, 1.0),
          RestrictedByGcd::Yes,
          ResourceType::Energy,
          30,
          spell_rank),
    druid(pchar),
    druid_spells(druid_spells),
    buff(buff) {
    switch (spell_rank) {
    case 1:
        bonus_damage = 10;
        level_req = 24;
        break;
    case 2:
        bonus_damage = 20;
        level_req = 36;
        break;
    case 3:
        bonus_damage = 30;
        level_req = 48;
        break;
    case 4:
        bonus_damage = 40;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }
}

TigersFury::~TigersFury() {
    delete cooldown;
}

bool TigersFury::is_rank_learned() const {
    return pchar->get_clvl() >= level_req;
}

void TigersFury::spell_effect() {
    if (buff->is_active())
        buff->cancel_buff();

    buff->flat_damage_bonus = bonus_damage;
    buff->apply_buff();
}

SpellStatus TigersFury::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Cat)
        return SpellStatus::Available;

    switch (druid->get_current_form()) {
    case DruidForm::Bear:
        return SpellStatus::InBearForm;
    case DruidForm::Caster:
        return SpellStatus::InCasterForm;
    case DruidForm::Moonkin:
        return SpellStatus::InMoonkinForm;
    default:
        check(false, "Reached end of switch in TigersFury::is_ready_spell_specific()");
        return SpellStatus::NotEnabled;
    }
}
