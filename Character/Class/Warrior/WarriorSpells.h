#ifndef WARRIORSPELLS_H
#define WARRIORSPELLS_H

#include "Spells.h"

class Warrior;

class AngerManagement;
class BattleShout;
class BattleStance;
class BerserkerRage;
class BerserkerStance;
class Bloodrage;
class Bloodthirst;
class DeathWish;
class DeepWounds;
class Execute;
class Hamstring;
class HeroicStrike;
class MortalStrike;
class Overpower;
class Recklessness;
class Rend;
class Slam;
class Whirlwind;

class MainhandAttackWarrior;
class OffhandAttackWarrior;

class WarriorSpells: public Spells {
public:
    WarriorSpells(Warrior *warr);

    void mh_auto_attack(const int) override;
    void oh_auto_attack(const int) override;
    void add_next_mh_attack(void) override;
    void add_next_oh_attack(void) override;

    MainhandAttack* get_mh_attack() const override;
    OffhandAttack* get_oh_attack() const override;

    AngerManagement* get_anger_management() const;
    BattleStance* get_battle_stance() const;
    BattleShout* get_battle_shout() const;
    BerserkerStance* get_berserker_stance() const;
    BerserkerRage* get_berserker_rage() const;
    Bloodrage* get_bloodrage() const;
    Bloodthirst* get_bloodthirst() const;
    DeathWish* get_death_wish() const;
    DeepWounds* get_deep_wounds() const;
    Execute* get_execute() const;
    Hamstring* get_hamstring() const;
    HeroicStrike* get_heroic_strike() const;
    MortalStrike* get_mortal_strike() const;
    OffhandAttackWarrior* get_oh_attack_warrior() const;
    Overpower* get_overpower() const;
    Slam* get_slam() const;
    Rend* get_rend() const;
    Recklessness* get_recklessness() const;
    Whirlwind* get_whirlwind() const;

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
    MortalStrike* mortal_strike;
    Overpower* overpower;
    Recklessness* recklessness;
    Rend* rend;
    Slam* slam;
    Whirlwind* whirlwind;

    MainhandAttackWarrior* warr_mh_attack;
    OffhandAttackWarrior* warr_oh_attack;
};

#endif // WARRIORSPELLS_H
