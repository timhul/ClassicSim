#ifndef STATS_H
#define STATS_H

#include "Target.h"

class Stats {
public:
    Stats();
    ~Stats();

    void add(const Stats*);
    void remove(const Stats*);

    unsigned get_base_melee_ap() const;
    void increase_base_melee_ap(const unsigned increase);
    void decrease_base_melee_ap(const unsigned decrease);

    unsigned get_base_ranged_ap() const;
    void increase_base_ranged_ap(const unsigned);
    void decrease_base_ranged_ap(const unsigned);

    unsigned get_strength() const;
    void increase_strength(const unsigned increase);
    void decrease_strength(const unsigned decrease);

    unsigned get_agility() const;
    void increase_agility(const unsigned);
    void decrease_agility(const unsigned);

    unsigned get_stamina() const;
    void increase_stamina(const unsigned);
    void decrease_stamina(const unsigned);

    unsigned get_intellect() const;
    void increase_intellect(const unsigned);
    void decrease_intellect(const unsigned);

    unsigned get_spirit() const;
    void increase_spirit(const unsigned);
    void decrease_spirit(const unsigned);

    void increase_armor(const int);
    void decrease_armor(const int);

    void increase_defense(const int);
    void decrease_defense(const int);

    void increase_dodge(const double);
    void decrease_dodge(const double);

    void increase_parry(const double);
    void decrease_parry(const double);

    void increase_all_resistances(const int);
    void decrease_all_resistances(const int);

    void increase_arcane_resistance(const int);
    void decrease_arcane_resistance(const int);

    void increase_fire_resistance(const int);
    void decrease_fire_resistance(const int);

    void increase_frost_resistance(const int);
    void decrease_frost_resistance(const int);

    void increase_holy_resistance(const int);
    void decrease_holy_resistance(const int);

    void increase_nature_resistance(const int);
    void decrease_nature_resistance(const int);

    void increase_shadow_resistance(const int);
    void decrease_shadow_resistance(const int);

    int get_axe_skill() const;
    void increase_axe_skill(const int);
    void decrease_axe_skill(const int);

    int get_dagger_skill() const;
    void increase_dagger_skill(const int);
    void decrease_dagger_skill(const int);

    int get_mace_skill() const;
    void increase_mace_skill(const int);
    void decrease_mace_skill(const int);

    int get_sword_skill() const;
    void increase_sword_skill(const int);
    void decrease_sword_skill(const int);

    unsigned get_melee_hit_chance() const;
    void increase_melee_hit(const unsigned value);
    void decrease_melee_hit(const unsigned value);

    unsigned get_ranged_hit_chance() const;
    void increase_ranged_hit(const unsigned value);
    void decrease_ranged_hit(const unsigned value);

    unsigned get_melee_crit_chance() const;
    void increase_melee_crit(const unsigned value);
    void decrease_melee_crit(const unsigned value);

    unsigned get_ranged_crit_chance() const;
    void increase_ranged_crit(const unsigned value);
    void decrease_ranged_crit(const unsigned value);

    unsigned get_spell_hit_chance() const;
    void increase_spell_hit(const unsigned value);
    void decrease_spell_hit(const unsigned value);

    unsigned get_spell_crit_chance() const;
    void increase_spell_crit(const unsigned value);
    void decrease_spell_crit(const unsigned value);

    unsigned get_attack_speed() const;
    void increase_attack_speed(const unsigned value);
    void decrease_attack_speed(const unsigned value);

    double get_mh_wpn_speed() const;
    double get_oh_wpn_speed() const;

    void set_melee_ap_per_str(const unsigned value);
    void set_melee_ap_per_agi(const unsigned value);

    void set_str_multiplier(const double value);
    void set_agi_multiplier(const double value);
    void set_stam_multiplier(const double value);
    void set_spi_multiplier(const double value);
    void set_int_multiplier(const double value);

    void increase_melee_ap_against_type(const Target::CreatureType, const unsigned);
    void decrease_melee_ap_against_type(const Target::CreatureType, const unsigned);
    unsigned get_melee_ap_against_type(const Target::CreatureType) const;

    void increase_ranged_ap_against_type(const Target::CreatureType, const unsigned);
    void decrease_ranged_ap_against_type(const Target::CreatureType, const unsigned);
    unsigned get_ranged_ap_against_type(const Target::CreatureType) const;

private:
    unsigned STR;
    unsigned AGI;
    unsigned STAM;
    unsigned INT;
    unsigned SPI;

    int armor;
    int defense;
    double dodge_chance;
    double parry_chance;

    int arcane_res;
    int fire_res;
    int frost_res;
    int holy_res;
    int nature_res;
    int shadow_res;

    int axe_skill;
    int dagger_skill;
    int mace_skill;
    int sword_skill;

    unsigned melee_ap;
    unsigned melee_ap_per_str;
    unsigned melee_ap_per_agi;
    unsigned ranged_ap;
    unsigned ranged_ap_per_agi;
    unsigned melee_hit;
    unsigned melee_crit;
    unsigned ranged_hit;
    unsigned ranged_crit;
    unsigned spell_hit;
    unsigned spell_crit;
    unsigned attack_speed;

    QMap<Target::CreatureType, unsigned> melee_ap_against_creature;
    QMap<Target::CreatureType, unsigned> ranged_ap_against_creature;

    double str_multiplier;
    double agi_multiplier;
    double stam_multiplier;
    double spi_multiplier;
    double int_multiplier;
};

#endif // STATS_H
