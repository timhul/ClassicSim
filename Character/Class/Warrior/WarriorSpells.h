#ifndef WARRIORSPELLS_H
#define WARRIORSPELLS_H

#include "Spells.h"

class Warrior;

class BattleShout;
class BattleStance;
class BerserkerRage;
class Bloodrage;
class Bloodthirst;
class DeathWish;
class DeepWounds;
class Execute;
class HeroicStrike;
class Overpower;
class Recklessness;
class Whirlwind;

class MainhandAttackWarrior;
class OffhandAttackWarrior;

class WarriorSpells: public Spells {
    Q_OBJECT

public:
    WarriorSpells(Warrior *pchar);
    virtual ~WarriorSpells();

    void reset() override;
    void mh_auto_attack(const int) override;
    void oh_auto_attack(const int) override;
    void add_next_mh_attack(void) override;
    void add_next_oh_attack(void) override;

    MainhandAttack* get_mh_attack() const override;
    OffhandAttack* get_oh_attack() const override;

    BattleStance* get_battle_stance() const;
    Bloodthirst* get_bloodthirst() const;
    DeepWounds* get_deep_wounds() const;
    HeroicStrike* get_heroic_strike() const;
    Execute* get_execute() const;
    Overpower* get_overpower() const;
    OffhandAttackWarrior* get_oh_attack_warrior() const;
    DeathWish* get_death_wish() const;
    BattleShout* get_battle_shout() const;
    BerserkerRage* get_berserker_rage() const;
    Bloodrage* get_bloodrage() const;
    Whirlwind* get_whirlwind() const;
    Recklessness* get_recklessness() const;

    void apply_deep_wounds();

private:
    Warrior* pchar;
    BattleStance* battle_stance;
    Bloodthirst* bt;
    DeepWounds* deep_wounds;
    HeroicStrike* heroic_strike;
    Execute* execute;
    Overpower* overpower;
    DeathWish* death_wish;
    BattleShout* battle_shout;
    BerserkerRage* berserker_rage;
    Bloodrage* bloodrage;
    Recklessness* recklessness;
    Whirlwind* whirlwind;

    MainhandAttackWarrior* mh_attack;
    OffhandAttackWarrior* oh_attack;
};

#endif // WARRIORSPELLS_H
