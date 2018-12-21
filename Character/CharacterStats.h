#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include <QVector>
#include <QHash>

#include "ItemStatsEnum.h"
#include "Target.h"

class Character;
class Race;
class Equipment;
class EquipmentDb;
class Stats;
class Weapon;

class CharacterStats {
public:
    CharacterStats(Character*, EquipmentDb* equipment_db);
    virtual ~CharacterStats();

    Equipment* get_equipment(void) const;
    Stats* get_stats(void) const;

    int get_strength() const;
    int get_agility() const;
    int get_stamina() const;
    int get_intellect() const;
    int get_spirit() const;
    double get_hit_chance(void) const;
    double get_mh_crit_chance(void) const;
    double get_oh_crit_chance(void) const;
    double get_spell_hit_chance(void) const;
    double get_spell_crit_chance(void) const;

    double get_total_phys_dmg_mod() const;
    double get_attack_speed_mod() const;
    double get_physical_damage_taken_mod() const;
    double get_spell_damage_taken_mod() const;

    int get_mh_wpn_skill() const;
    int get_oh_wpn_skill() const;
    int get_wpn_skill(Weapon*) const;
    int get_ranged_wpn_skill();

    void increase_wpn_skill(const int, const int);
    void decrease_wpn_skill(const int, const int);

    void increase_stat(const ItemStats, const int);
    void decrease_stat(const ItemStats, const int);

    void increase_haste(const int);
    void decrease_haste(const int);

    void increase_strength(const int);
    void decrease_strength(const int);

    void increase_agility(const int);
    void decrease_agility(const int);

    void increase_stamina(const int);
    void decrease_stamina(const int);

    void increase_intellect(const int);
    void decrease_intellect(const int);

    void increase_spirit(const int);
    void decrease_spirit(const int);

    int get_melee_ap() const;
    void increase_melee_ap(const int);
    void decrease_melee_ap(const int);

    int get_ranged_ap() const;
    void increase_ranged_ap(const int);
    void decrease_ranged_ap(const int);

    void increase_ap_vs_type(const Target::CreatureType, const int);
    void decrease_ap_vs_type(const Target::CreatureType, const int);

    void increase_dmg_vs_type(const Target::CreatureType, const double);
    void decrease_dmg_vs_type(const Target::CreatureType, const double);

    virtual void increase_hit(double);
    virtual void decrease_hit(double);

    virtual void increase_crit(double);
    virtual void decrease_crit(double);

    void increase_crit_for_weapon_type(const int, const double);
    void decrease_crit_for_weapon_type(const int, const double);

    void increase_total_phys_dmg_for_weapon_type(const int, const int);
    void decrease_total_phys_dmg_for_weapon_type(const int, const int);

    virtual void increase_spell_hit(double);
    virtual void decrease_spell_hit(double);

    virtual void increase_spell_crit(double);
    virtual void decrease_spell_crit(double);

    void increase_total_phys_dmg_mod(const int);
    void decrease_total_phys_dmg_mod(const int);

    void add_phys_damage_taken_mod(const int);
    void remove_phys_damage_taken_mod(const int);

    void add_spell_damage_taken_mod(const int);
    void remove_spell_damage_taken_mod(const int);

    void add_total_stat_mod(const int);
    void remove_total_stat_mod(const int);

    void add_ap_multiplier(const int);
    void remove_ap_multiplier(const int);

    double get_mh_wpn_speed();
    double get_oh_wpn_speed();

    void increase_dodge(const double);
    void decrease_dodge(const double);

protected:
    Character* pchar;
    Equipment* equipment;
    Stats* base_stats;
    QVector<int> attack_speed_buffs;
    QVector<int> phys_dmg_buffs;
    QVector<int> phys_damage_taken_changes;
    QVector<int> spell_damage_taken_changes;
    QVector<int> total_stat_mod_changes;
    QVector<int> ap_total_multipliers;
    QHash<int, double> crit_bonuses_per_weapon_type;
    QHash<int, int> damage_bonuses_per_weapon_type;
    QHash<int, double> damage_bonuses_per_monster_type;

    int axe_skill_bonus;
    int dagger_skill_bonus;
    int mace_skill_bonus;
    int sword_skill_bonus;

    int ranged_ap{};
    double melee_ability_crit_mod{};
    double attack_speed_mod;
    double total_phys_dmg_mod;
    double physical_damage_taken_mod;
    double spell_damage_taken_mod;
    double total_stat_mod;
    double total_ap_mod;

    void add_multiplicative_effect(QVector<int>& effects, int add_value, double& modifier);
    void remove_multiplicative_effect(QVector<int>& effects, int remove_value, double& modifier);
    void recalculate_multiplicative_effects(QVector<int>& effects, double& modifier);
    Target::CreatureType get_type_for_stat(const ItemStats);

private:
};

#endif // CHARACTERSTATS_H
