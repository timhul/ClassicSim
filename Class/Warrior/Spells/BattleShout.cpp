#include "BattleShout.h"

#include "BattleShoutBuff.h"
#include "CooldownControl.h"
#include "EnabledBuffs.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Warrior.h"

BattleShout::BattleShout(Warrior* pchar, BattleShoutBuff* buff, const int spell_rank) :
    Spell("Battle Shout", "Assets/ability/Ability_warrior_battleshout.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 10, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Battle Shout", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Booming Voice", 5, DisabledAtZero::No)
                   }),
    buff(buff)
{
    switch (spell_rank) {
    case 1:
        base_attack_power = 15;
        level_req = 1;
        break;
    case 2:
        base_attack_power = 35;
        level_req = 12;
        break;
    case 3:
        base_attack_power = 55;
        level_req = 22;
        break;
    case 4:
        base_attack_power = 85;
        level_req = 32;
        break;
    case 5:
        base_attack_power = 130;
        level_req = 42;
        break;
    case 6:
        base_attack_power = 185;
        level_req = 52;
        break;
    case 7:
        base_attack_power = 232;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    modified_by_talents_attack_power = base_attack_power;

    base_duration = buff->duration;
    next_duration = buff->duration;
}

BattleShout::~BattleShout() {
    delete cooldown;
}

bool BattleShout::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 6)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 7)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 5;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

Buff* BattleShout::get_buff() const {
    return this->buff;
}

void BattleShout::spell_effect() {
    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();

    if (buff->is_active())
        buff->cancel_buff();

    buff->duration = next_duration;
    buff->attack_power = modified_by_talents_attack_power;
    buff->apply_buff();

    pchar->lose_rage(resource_cost);
}

void BattleShout::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Battle Shout") {
        modified_by_talents_attack_power = static_cast<unsigned>(round(base_attack_power * ranks_imp_shout[curr]));
    }
    else if (talent_name == "Booming Voice") {
        next_duration = static_cast<int>(round(base_duration * ranks_booming_voice[curr]));
    }
}

void BattleShout::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Battle Shout") {
        modified_by_talents_attack_power = static_cast<unsigned>(round(base_attack_power * ranks_imp_shout[curr]));
    }
    else if (talent_name == "Booming Voice") {
        next_duration = static_cast<int>(round(base_duration * ranks_booming_voice[curr]));
    }
}
