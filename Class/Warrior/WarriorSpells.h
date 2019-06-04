#ifndef WARRIORSPELLS_H
#define WARRIORSPELLS_H

#include "CharacterSpells.h"

class AngerManagement;
class BattleShout;
class BattleShoutBuff;
class BattleStance;
class BerserkerRage;
class BerserkerStance;
class BerserkerStanceBuff;
class Bloodrage;
class Bloodthirst;
class Buff;
class DeathWish;
class DeepWounds;
class DefensiveStanceBuff;
class Execute;
class Flurry;
class Hamstring;
class HeroicStrike;
class MainhandAttackWarrior;
class MortalStrike;
class OffhandAttackWarrior;
class Overpower;
class Proc;
class Recklessness;
class RecklessnessBuff;
class Rend;
class Slam;
class SwordSpecialization;
class UnbridledWrath;
class Warrior;
class Whirlwind;

class WarriorSpells: public CharacterSpells {
public:
    WarriorSpells(Warrior *warr);
    ~WarriorSpells() override;

    void mh_auto_attack(const int) override;
    void oh_auto_attack(const int) override;
    void add_next_mh_attack() override;
    void add_next_oh_attack() override;

    MainhandAttack* get_mh_attack() const override;
    OffhandAttack* get_oh_attack() const override;

    BattleShout* get_battle_shout() const;
    BerserkerStance* get_berserker_stance() const;
    Bloodrage* get_bloodrage() const;
    Bloodthirst* get_bloodthirst() const;
    DeathWish* get_death_wish() const;
    DeepWounds* get_deep_wounds() const;
    Execute* get_execute() const;
    HeroicStrike* get_heroic_strike() const;
    MortalStrike* get_mortal_strike() const;
    Overpower* get_overpower() const;
    Recklessness* get_recklessness() const;
    Rend* get_rend() const;
    Slam* get_slam() const;
    Whirlwind* get_whirlwind() const;

    Buff* get_berserker_stance_buff() const;
    Buff* get_overpower_buff() const;
    Buff* get_defensive_stance_buff() const;
    Buff* get_flurry() const;
    Buff* get_recklessness_buff() const;

    Proc* get_sword_spec() const;
    Proc* get_unbridled_wrath() const;

    void apply_deep_wounds();

private:
    Warrior* warr;

    AngerManagement* anger_management;
    BattleShout* battle_shout;
    BattleStance* battle_stance;
    BerserkerRage* berserker_rage;
    BerserkerStance* berserker_stance;
    Bloodrage* bloodrage;
    Bloodthirst* bt;
    DeathWish* death_wish;
    DeepWounds* deep_wounds;
    Execute* execute;
    Hamstring* hamstring;
    HeroicStrike* heroic_strike;
    MainhandAttackWarrior* warr_mh_attack;
    MortalStrike* mortal_strike;
    OffhandAttackWarrior* warr_oh_attack;
    Overpower* overpower;
    Recklessness* recklessness;
    Rend* rend;
    Slam* slam;
    Whirlwind* whirlwind;

    BerserkerStanceBuff* berserker_stance_buff;
    Buff* battle_stance_buff;
    Buff* overpower_buff;
    DefensiveStanceBuff* defensive_stance_buff;
    Flurry* flurry;
    RecklessnessBuff* recklessness_buff;

    SwordSpecialization* sword_spec;
    UnbridledWrath* unbridled_wrath;
};

#endif // WARRIORSPELLS_H
