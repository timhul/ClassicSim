#ifndef STATS_H
#define STATS_H

#include <QObject>
#include "Target.h"

class Stats: public QObject {
    Q_OBJECT

public:
    Stats(QObject* parent = nullptr);
    ~Stats();

    void add(const Stats*);
    void remove(const Stats*);

    int get_strength() const;
    int get_agility() const;
    int get_stamina() const;
    int get_intellect() const;
    int get_spirit() const;

    int get_melee_ap_str_excluded() const;
    int get_melee_ap_total() const;

    void increase_base_melee_ap(const int increase);
    void decrease_base_melee_ap(const int decrease);

    void increase_str(const int increase);
    void decrease_str(const int decrease);

    void increase_agi(const int);
    void decrease_agi(const int);

    void increase_stam(const int);
    void decrease_stam(const int);

    void increase_int(const int);
    void decrease_int(const int);

    void increase_spi(const int);
    void decrease_spi(const int);

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

    double get_hit_chance(void) const;
    void increase_hit(const double value);
    void decrease_hit(const double value);

    double get_crit_chance(void) const;
    void increase_crit(const double value);
    void decrease_crit(const double value);

    double get_spell_hit_chance(void) const;
    void increase_spell_hit(const double value);
    void decrease_spell_hit(const double value);

    double get_spell_crit_chance(void) const;
    void increase_spell_crit(const double value);
    void decrease_spell_crit(const double value);

    double get_attack_speed(void) const;
    void increase_attack_speed(const double value);
    void decrease_attack_speed(const double value);

    double get_mh_wpn_speed() const;
    double get_oh_wpn_speed() const;

    void set_melee_ap_per_str(const int value);
    void set_melee_ap_per_agi(const int value);

    void set_str_multiplier(const double value);
    void set_agi_multiplier(const double value);
    void set_stam_multiplier(const double value);
    void set_spi_multiplier(const double value);
    void set_int_multiplier(const double value);

    void increase_melee_ap_against_type(const Target::CreatureType, const int);
    void decrease_melee_ap_against_type(const Target::CreatureType, const int);
    int get_melee_ap_against_type(const Target::CreatureType) const;

private:
    int STR;
    int AGI;
    int STAM;
    int INT;
    int SPI;

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

    int melee_ap;
    int melee_ap_per_str;
    int melee_ap_per_agi;
    int ranged_ap{};
    double percent_hit;
    double percent_crit;
    double percent_spell_hit;
    double percent_spell_crit;
    double percent_attack_speed;

    QMap<Target::CreatureType, int> melee_ap_against_creature;

    double str_multiplier;
    double agi_multiplier;
    double stam_multiplier;
    double spi_multiplier;
    double int_multiplier;
};

#endif // STATS_H
