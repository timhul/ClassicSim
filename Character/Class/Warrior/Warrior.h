#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Flurry;
class UnbridledWrath;
class HeroicStrikeBuff;
class BattleShoutBuff;
class DeathWishBuff;
class WarriorSpells;

class Warrior: public Character {
    Q_OBJECT
public:
    Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, Faction* faction, QObject *parent = 0);
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
    int get_ap_per_strength() const override;
    int get_ap_per_agi() const override;
    void set_clvl(const int) override;

    float global_cooldown() const override;
    int get_resource_level() const override;
    int get_curr_rage() const;
    void gain_rage(const int);
    void lose_rage(const int);
    int rage_gained_from_dd(const int) const;

    Flurry* get_flurry() const;
    UnbridledWrath* get_unbridled_wrath() const;
    HeroicStrikeBuff* get_hs_buff() const;
    BattleShoutBuff* get_battle_shout_buff() const;
    DeathWishBuff* get_death_wish_buff() const;

    void melee_mh_white_hit_effect() override;
    void melee_mh_yellow_hit_effect() override;
    void melee_mh_white_critical_effect() override;
    void melee_mh_yellow_critical_effect() override;
    void melee_oh_white_hit_effect() override;
    void melee_oh_yellow_hit_effect() override;
    void melee_oh_white_critical_effect() override;
    void melee_oh_yellow_critical_effect() override;

    void reset_resource() override;
    void reset_spells() override;


protected:
private:
    int rage;
    double rage_conversion_value;
    Flurry* flurry;
    HeroicStrikeBuff* heroic_strike_buff;
    UnbridledWrath* unbridled_wrath;
    DeathWishBuff* death_wish_buff;
    BattleShoutBuff* battle_shout_buff;
    WarriorSpells* warr_spells;

    void initialize_talents() override;
};

#endif // WARRIOR_H
