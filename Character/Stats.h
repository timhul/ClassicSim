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

    unsigned get_axe_skill() const;
    void increase_axe_skill(const unsigned value);
    void decrease_axe_skill(const unsigned value);

    unsigned get_dagger_skill() const;
    void increase_dagger_skill(const unsigned value);
    void decrease_dagger_skill(const unsigned value);

    unsigned get_mace_skill() const;
    void increase_mace_skill(const unsigned value);
    void decrease_mace_skill(const unsigned value);

    unsigned get_sword_skill() const;
    void increase_sword_skill(const unsigned value);
    void decrease_sword_skill(const unsigned value);

    unsigned get_bow_skill() const;
    void increase_bow_skill(const unsigned value);
    void decrease_bow_skill(const unsigned value);

    unsigned get_crossbow_skill() const;
    void increase_crossbow_skill(const unsigned value);
    void decrease_crossbow_skill(const unsigned value);

    unsigned get_gun_skill() const;
    void increase_gun_skill(const unsigned value);
    void decrease_gun_skill(const unsigned value);

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

    unsigned get_flat_weapon_damage() const;
    void increase_flat_weapon_damage(const unsigned value);
    void decrease_flat_weapon_damage(const unsigned value);

    unsigned get_mp5() const;
    void increase_mp5(const unsigned increase);
    void decrease_mp5(const unsigned decrease);

    unsigned get_base_spell_damage() const;
    void increase_base_spell_damage(const unsigned increase);
    void decrease_base_spell_damage(const unsigned decrease);

    unsigned get_spell_damage(const MagicSchool school) const;
    void increase_spell_damage_vs_school(const unsigned increase, const MagicSchool school);
    void decrease_spell_damage_vs_school(const unsigned decrease, const MagicSchool school);

private:
    unsigned STR {0};
    unsigned AGI {0};
    unsigned STAM {0};
    unsigned INT {0};
    unsigned SPI {0};

    int armor {0};
    int defense {0};
    double dodge_chance {0.0};
    double parry_chance {0.0};

    int arcane_res {0};
    int fire_res {0};
    int frost_res {0};
    int holy_res {0};
    int nature_res {0};
    int shadow_res {0};

    unsigned axe_skill {0};
    unsigned dagger_skill {0};
    unsigned mace_skill {0};
    unsigned sword_skill {0};
    unsigned bow_skill {0};
    unsigned crossbow_skill {0};
    unsigned gun_skill {0};

    unsigned melee_ap {0};
    unsigned ranged_ap {0};
    unsigned melee_hit {0};
    unsigned melee_crit {0};
    unsigned ranged_hit {0};
    unsigned ranged_crit {0};
    unsigned spell_hit {0};
    unsigned spell_crit {0};
    unsigned attack_speed {0};
    unsigned flat_weapon_damage {0};

    unsigned mp5 {0};
    unsigned spell_damage {0};

    QMap<Target::CreatureType, unsigned> melee_ap_against_creature;
    QMap<Target::CreatureType, unsigned> ranged_ap_against_creature;
    QMap<MagicSchool, unsigned> spell_school_damage_bonus;

    double str_multiplier {1.0};
    double agi_multiplier {1.0};
    double stam_multiplier {1.0};
    double spi_multiplier {1.0};
    double int_multiplier {1.0};
};

#endif // STATS_H
