#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class CombatRoll;
class Talents;
class Bloodthirst;
class Whirlwind;
class Flurry;
class DeepWounds;
class HeroicStrike;
class HeroicStrikeBuff;
class Execute;
class Overpower;
class UnbridledWrath;
class DeathWish;
class DeathWishBuff;
class BattleShout;
class BattleShoutBuff;
class BerserkerRage;
class Bloodrage;
class OffhandAttackWarrior;

class Warrior: public Character {
    Q_OBJECT
public:
    Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, QObject *parent = 0);
    virtual ~Warrior();

    QString get_name() const override;
    QString get_class_color() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    int get_agi_needed_for_one_percent_phys_crit() const override;
    int get_int_needed_for_one_percent_spell_crit() const override;
    void rotation() override;
    void mh_auto_attack(const int) override;
    void oh_auto_attack(const int) override;
    float global_cooldown() const override;
    int get_curr_rage() const;
    void gain_rage(const int);
    void lose_rage(const int);
    int rage_gained_from_dd(const int) const;

    bool bt_available(void) const;

    Bloodthirst* get_bloodthirst() const;
    Flurry* get_flurry() const;
    DeepWounds* get_deep_wounds() const;
    HeroicStrike* get_heroic_strike() const;
    HeroicStrikeBuff* get_hs_buff() const;
    Execute* get_execute() const;
    Overpower* get_overpower() const;
    OffhandAttackWarrior* get_oh_attack_warrior() const;
    UnbridledWrath* get_unbridled_wrath() const;
    DeathWish* get_death_wish() const;
    DeathWishBuff* get_death_wish_buff() const;
    BattleShout* get_battle_shout() const;
    BattleShoutBuff* get_battle_shout_buff() const;
    BerserkerRage* get_berserker_rage() const;
    Bloodrage* get_bloodrage() const;
    Whirlwind* get_whirlwind() const;

    void melee_mh_hit_effect() override;
    void melee_mh_critical_effect() override;
    void melee_oh_hit_effect() override;
    void melee_oh_critical_effect() override;

    int get_ap_per_strength() const override;
    int get_ap_per_agi() const override;

    void reset_resource() override;

protected:
private:
    int rage;
    Bloodthirst* bt;
    Flurry* flurry;
    DeepWounds* deep_wounds;
    HeroicStrike* heroic_strike;
    HeroicStrikeBuff* heroic_strike_buff;
    Execute* execute;
    Overpower* overpower;
    UnbridledWrath* unbridled_wrath;
    DeathWish* death_wish;
    DeathWishBuff* death_wish_buff;
    BattleShout* battle_shout;
    BattleShoutBuff* battle_shout_buff;
    BerserkerRage* berserker_rage;
    Bloodrage* bloodrage;
    Whirlwind* whirlwind;

    void initialize_talents() override;
};

#endif // WARRIOR_H
