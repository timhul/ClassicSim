#ifndef WARRIORSPELLS_H
#define WARRIORSPELLS_H

#include "Spells.h"

class Warrior;
class Bloodthirst;
class Whirlwind;
class DeepWounds;
class HeroicStrike;
class Execute;
class Overpower;
class DeathWish;
class BattleShout;
class BerserkerRage;
class Bloodrage;
class MainhandAttackWarrior;
class OffhandAttackWarrior;

class WarriorSpells: public Spells {
    Q_OBJECT

public:
    WarriorSpells(Warrior *pchar);
    virtual ~WarriorSpells();

    void rotation() override;
    void reset() override;
    void mh_auto_attack(const int) override;
    void oh_auto_attack(const int) override;
    void add_next_mh_attack(void) override;
    void add_next_oh_attack(void) override;

    MainhandAttack* get_mh_attack() const override;
    OffhandAttack* get_oh_attack() const override;

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

    void apply_deep_wounds();
    void try_heroic_strike();
    void try_berserker_rage();
    void try_bloodrage();
    bool try_execute();
    bool try_overpower();
    bool try_death_wish();
    bool try_battle_shout();
    bool try_bloodthirst();
    bool try_whirlwind();

private:
    Warrior* pchar;
    Bloodthirst* bt;
    DeepWounds* deep_wounds;
    HeroicStrike* heroic_strike;
    Execute* execute;
    Overpower* overpower;
    DeathWish* death_wish;
    BattleShout* battle_shout;
    BerserkerRage* berserker_rage;
    Bloodrage* bloodrage;
    Whirlwind* whirlwind;

    MainhandAttackWarrior* mh_attack;
    OffhandAttackWarrior* oh_attack;
};

#endif // WARRIORSPELLS_H
