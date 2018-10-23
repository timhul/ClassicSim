
#include "WarriorRotation.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "RotationExecutor.h"
#include <QDebug>

#include "BattleShout.h"
#include "BattleStance.h"
#include "BerserkerRage.h"
#include "BerserkerStance.h"
#include "Berserking.h"
#include "BloodFury.h"
#include "Bloodrage.h"
#include "Bloodthirst.h"
#include "DeathWish.h"
#include "DeepWounds.h"
#include "Execute.h"
#include "HeroicStrike.h"
#include "MainhandAttack.h"
#include "MortalStrike.h"
#include "Overpower.h"
#include "Recklessness.h"
#include "Slam.h"
#include "Whirlwind.h"

#include "BattleShoutBuff.h"
#include "BattleStanceBuff.h"
#include "BerserkerStanceBuff.h"
#include "BerserkingBuff.h"
#include "BloodFuryBuff.h"
#include "DeathWishBuff.h"
#include "DefensiveStanceBuff.h"
#include "Flurry.h"
#include "HeroicStrikeBuff.h"
#include "OverpowerBuff.h"
#include "RecklessnessBuff.h"

WarriorRotation::WarriorRotation(QObject* parent) :
    Rotation("Warrior", parent)
{}

Spell* WarriorRotation::get_spell_from_name(const QString& spell_name) const {
    Spell* spell = nullptr;
    auto* spells = dynamic_cast<WarriorSpells*>(dynamic_cast<Warrior*>(pchar)->get_spells());

    if (spell_name == "Battle Shout")
        spell = spells->get_battle_shout();
    else if (spell_name == "Battle Stance")
        spell = spells->get_battle_stance();
    else if (spell_name == "Berserker Rage")
        spell = spells->get_berserker_rage();
    else if (spell_name == "Berserker Stance")
        spell = spells->get_berserker_stance();
    else if (spell_name == "Berserking")
        spell = spells->get_berserking();
    else if (spell_name == "Blood Fury")
        spell = spells->get_blood_fury();
    else if (spell_name == "Bloodrage")
        spell = spells->get_bloodrage();
    else if (spell_name == "Bloodthirst")
        spell = spells->get_bloodthirst();
    else if (spell_name == "Death Wish")
        spell = spells->get_death_wish();
    else if (spell_name == "Deep Wounds")
        spell = spells->get_deep_wounds();
    else if (spell_name == "Execute")
        spell = spells->get_execute();
    else if (spell_name == "Hamstring")
        spell = nullptr;
    else if (spell_name == "Heroic Strike")
        spell = spells->get_heroic_strike();
    else if (spell_name == "Mainhand Attack")
        spell = spells->get_mh_attack();
    else if (spell_name == "Mortal Strike")
        spell = spells->get_mortal_strike();
    else if (spell_name == "Overpower")
        spell = spells->get_overpower();
    else if (spell_name == "Recklessness")
        spell = spells->get_recklessness();
    else if (spell_name == "Slam")
        spell = spells->get_slam();
    else if (spell_name == "Whirlwind")
        spell = spells->get_whirlwind();

    return spell;
}

Buff* WarriorRotation::get_buff_from_name(const QString &buff_name) const {
    Buff* buff = nullptr;

    if (buff_name == "Battle Shout")
        buff = dynamic_cast<Warrior*>(pchar)->get_battle_shout_buff();
    else if (buff_name == "Battle Stance")
        buff = dynamic_cast<Warrior*>(pchar)->get_battle_stance_buff();
    else if (buff_name == "Berserker Stance")
        buff = dynamic_cast<Warrior*>(pchar)->get_berserker_stance_buff();
    else if (buff_name == "Berserking")
        buff = dynamic_cast<Warrior*>(pchar)->get_berserking_buff();
    else if (buff_name == "Blood Fury")
        buff = dynamic_cast<Warrior*>(pchar)->get_blood_fury_buff();
    else if (buff_name == "Defensive Stance")
        buff = dynamic_cast<Warrior*>(pchar)->get_defensive_stance_buff();
    else if (buff_name == "Flurry")
        buff = dynamic_cast<Warrior*>(pchar)->get_flurry();
    else if (buff_name == "Heroic Strike")
        buff = dynamic_cast<Warrior*>(pchar)->get_hs_buff();
    else if (buff_name == "Death Wish")
        buff = dynamic_cast<Warrior*>(pchar)->get_death_wish_buff();
    else if (buff_name == "Overpower")
        buff = dynamic_cast<Warrior*>(pchar)->get_overpower_buff();
    else if (buff_name == "Recklessness")
        buff = dynamic_cast<Warrior*>(pchar)->get_recklessness_buff();

    return buff;
}
