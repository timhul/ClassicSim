#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Flurry;
class SwordSpecialization;
class UnbridledWrath;
class BattleStanceBuff;
class BerserkerStanceBuff;
class DefensiveStanceBuff;
class HeroicStrikeBuff;
class BattleShoutBuff;
class DeathWishBuff;
class OverpowerBuff;
class RecklessnessBuff;
class WarriorSpells;

namespace WarriorStances {
    static const int Battle = 0;
    static const int Defensive = 1;
    static const int Berserker = 2;
}

class Warrior: public Character {
    Q_OBJECT
public:
    Warrior(Race* race, EquipmentDb *equipment_db, SimSettings* sim_settings, QObject *parent = nullptr);
    ~Warrior() override;

    QString get_name() const override;
    QString get_class_color() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    double get_agi_needed_for_one_percent_phys_crit() const override;
    double get_int_needed_for_one_percent_spell_crit() const override;
    int get_ap_per_strength() const override;
    int get_ap_per_agi() const override;
    void set_clvl(const int) override;

    int get_highest_possible_armor_type() const override;
    QVector<int> get_weapon_proficiencies_for_slot(const int slot) const override;

    double global_cooldown() const override;
    double stance_cooldown() const;
    bool on_stance_cooldown() const;
    void increase_stance_rage_remainder();
    void decrease_stance_rage_remainder();
    unsigned get_stance_remainder() const;
    unsigned get_resource_level() const override;
    unsigned get_curr_rage() const;
    void gain_rage(const unsigned) override;
    void lose_rage(const unsigned) override;
    unsigned rage_gained_from_dd(const unsigned) const;
    void switch_to_battle_stance();
    void switch_to_berserker_stance();
    void switch_to_defensive_stance();
    bool in_battle_stance() const;
    bool in_berserker_stance() const;
    bool in_defensive_stance() const;

    Flurry* get_flurry() const;
    SwordSpecialization* get_sword_spec() const;
    UnbridledWrath* get_unbridled_wrath() const;
    BattleStanceBuff* get_battle_stance_buff() const;
    BerserkerStanceBuff* get_berserker_stance_buff() const;
    DefensiveStanceBuff* get_defensive_stance_buff() const;
    HeroicStrikeBuff* get_hs_buff() const;
    BattleShoutBuff* get_battle_shout_buff() const;
    DeathWishBuff* get_death_wish_buff() const;
    OverpowerBuff* get_overpower_buff() const;
    RecklessnessBuff* get_recklessness_buff() const;

    ClassStatistics* relinquish_ownership_of_statistics() override;

    void melee_mh_white_hit_effect() override;
    void melee_mh_yellow_hit_effect() override;
    void melee_mh_white_critical_effect() override;
    void melee_mh_yellow_critical_effect() override;
    void melee_oh_white_hit_effect() override;
    void melee_oh_yellow_hit_effect() override;
    void melee_oh_white_critical_effect() override;
    void melee_oh_yellow_critical_effect() override;

private:
    unsigned rage;
    int stance;
    unsigned stance_rage_remainder;
    double next_stance_cd;
    double rage_conversion_value{};
    Flurry* flurry;
    SwordSpecialization* sword_spec;
    UnbridledWrath* unbridled_wrath;
    BattleStanceBuff* battle_stance_buff;
    BerserkerStanceBuff* berserker_stance_buff;
    DefensiveStanceBuff* defensive_stance_buff;
    HeroicStrikeBuff* heroic_strike_buff;
    DeathWishBuff* death_wish_buff;
    BattleShoutBuff* battle_shout_buff;
    OverpowerBuff* overpower_buff;
    RecklessnessBuff* recklessness_buff;
    WarriorSpells* warr_spells;

    void initialize_talents() override;
    void new_stance_effect();

    void reset_resource() override;
    void reset_spells() override;
};

#endif // WARRIOR_H
