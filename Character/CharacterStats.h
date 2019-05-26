#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include <QHash>
#include <QVector>

#include "ItemStatsEnum.h"
#include "Target.h"

class Buff;
class Character;
class Equipment;
class EquipmentDb;
class Race;
class Stats;
class Weapon;

class CharacterStats {
public:
    CharacterStats(Character*, EquipmentDb* equipment_db);
    ~CharacterStats();

    Equipment* get_equipment() const;
    Stats* get_stats() const;

    static void add_multiplicative_effect(QVector<int>& effects, int add_value, double& modifier);
    static void remove_multiplicative_effect(QVector<int>& effects, int remove_value, double& modifier);
    static void recalculate_multiplicative_effects(QVector<int>& effects, double& modifier);

    unsigned get_mh_wpn_skill() const;
    unsigned get_oh_wpn_skill() const;
    unsigned get_ranged_wpn_skill() const;

    void increase_wpn_skill(const int weapon_type, const unsigned value);
    void decrease_wpn_skill(const int weapon_type, const unsigned value);

    void increase_stat(const ItemStats stat_type, const unsigned value);
    void decrease_stat(const ItemStats stat_type, const unsigned value);

    double get_melee_attack_speed_mod() const;
    void increase_melee_attack_speed(const unsigned value);
    void decrease_melee_attack_speed(const unsigned value);

    double get_ranged_attack_speed_mod() const;
    void increase_ranged_attack_speed(const unsigned value);
    void decrease_ranged_attack_speed(const unsigned value);

    unsigned get_strength() const;
    void increase_strength(const unsigned value);
    void decrease_strength(const unsigned value);

    unsigned get_agility() const;
    void increase_agility(const unsigned value);
    void decrease_agility(const unsigned value);

    unsigned get_stamina() const;
    void increase_stamina(const unsigned value);
    void decrease_stamina(const unsigned value);

    unsigned get_intellect() const;
    void increase_intellect(const unsigned value);
    void decrease_intellect(const unsigned value);

    unsigned get_spirit() const;
    void increase_spirit(const unsigned value);
    void decrease_spirit(const unsigned value);

    unsigned get_melee_ap() const;
    void increase_melee_ap(const unsigned value);
    void decrease_melee_ap(const unsigned value);

    unsigned get_ranged_ap() const;
    void increase_ranged_ap(const unsigned value);
    void decrease_ranged_ap(const unsigned value);

    void increase_ap_vs_type(const Target::CreatureType target_type, const unsigned value);
    void decrease_ap_vs_type(const Target::CreatureType target_type, const unsigned value);

    void increase_dmg_vs_type(const Target::CreatureType target_type, const double value);
    void decrease_dmg_vs_type(const Target::CreatureType target_type, const double value);

    void increase_crit_dmg_vs_type(const Target::CreatureType target_type, const unsigned value);
    void decrease_crit_dmg_vs_type(const Target::CreatureType target_type, const unsigned value);

    unsigned get_melee_hit_chance() const;
    void increase_melee_hit(const unsigned value);
    void decrease_melee_hit(const unsigned value);

    unsigned get_mh_crit_chance() const;
    unsigned get_oh_crit_chance() const;
    void increase_melee_crit(const unsigned value);
    void decrease_melee_crit(const unsigned value);

    unsigned get_ranged_hit_chance() const;
    void increase_ranged_hit(const unsigned value);
    void decrease_ranged_hit(const unsigned value);

    unsigned get_ranged_crit_chance() const;
    void increase_ranged_crit(const unsigned value);
    void decrease_ranged_crit(const unsigned value);

    void increase_crit_for_weapon_type(const int weapon_type, const unsigned value);
    void decrease_crit_for_weapon_type(const int weapon_type, const unsigned value);

    void increase_total_phys_dmg_for_weapon_type(const int weapon_type, const int value);
    void decrease_total_phys_dmg_for_weapon_type(const int weapon_type, const int value);

    unsigned get_spell_hit_chance() const;
    void increase_spell_hit(const unsigned value);
    void decrease_spell_hit(const unsigned value);

    unsigned get_spell_crit_chance() const;
    void increase_spell_crit(const unsigned value);
    void decrease_spell_crit(const unsigned value);

    double get_melee_ability_crit_dmg_mod() const;
    void increase_melee_ability_crit_dmg_mod(const double value);
    void decrease_melee_ability_crit_dmg_mod(const double value);

    double get_ranged_ability_crit_dmg_mod() const;
    void increase_ranged_ability_crit_dmg_mod(const double value);
    void decrease_ranged_ability_crit_dmg_mod(const double value);

    unsigned get_mp5() const;
    void increase_mp5(const unsigned value);
    void decrease_mp5(const unsigned value);

    unsigned get_spell_damage(const MagicSchool school) const;
    void increase_base_spell_damage(const unsigned value);
    void decrease_base_spell_damage(const unsigned value);
    void increase_spell_damage_vs_school(const unsigned value, const MagicSchool school);
    void decrease_spell_damage_vs_school(const unsigned value, const MagicSchool school);

    double get_magic_school_damage_mod(const MagicSchool school) const;
    void increase_magic_school_damage_mod(const int increase, const MagicSchool school, Buff* buff = nullptr);
    void decrease_magic_school_damage_mod(const int decrease, const MagicSchool school, Buff* buff = nullptr);

    double get_spell_crit_dmg_mod() const;
    void increase_spell_crit_dmg_mod(const double value);
    void decrease_spell_crit_dmg_mod(const double value);

    double get_total_physical_damage_mod() const;
    void increase_total_phys_dmg_mod(const int mod);
    void decrease_total_phys_dmg_mod(const int mod);

    double get_physical_damage_taken_mod() const;
    void add_phys_damage_taken_mod(const int mod);
    void remove_phys_damage_taken_mod(const int mod);

    double get_spell_damage_taken_mod() const;
    void add_spell_damage_taken_mod(const int mod);
    void remove_spell_damage_taken_mod(const int mod);

    void add_total_stat_mod(const int mod);
    void remove_total_stat_mod(const int mod);

    void add_ap_multiplier(const int mod);
    void remove_ap_multiplier(const int mod);

    void add_agility_mod(const int mod);
    void remove_agility_mod(const int mod);

    void add_intellect_mod(const int mod);
    void remove_intellect_mod(const int mod);

    void add_spirit_mod(const int mod);
    void remove_spirit_mod(const int mod);

    void add_stamina_mod(const int mod);
    void remove_stamina_mod(const int mod);

    void add_strength_mod(const int mod);
    void remove_strength_mod(const int mod);

    double get_mh_wpn_speed();
    double get_oh_wpn_speed();
    double get_ranged_wpn_speed();

    void increase_dodge(const double value);
    void decrease_dodge(const double value);

private:
    Character* pchar;
    Equipment* equipment;
    Stats* base_stats;
    QVector<int> melee_attack_speed_buffs;
    QVector<int> ranged_attack_speed_buffs;
    QVector<int> phys_dmg_buffs;
    QVector<int> phys_damage_taken_changes;
    QVector<int> spell_damage_taken_changes;
    QVector<int> ap_total_multipliers;
    QVector<int> agility_mod_changes;
    QVector<int> intellect_mod_changes;
    QVector<int> spirit_mod_changes;
    QVector<int> stamina_mod_changes;
    QVector<int> strength_mod_changes;
    QHash<int, unsigned> crit_bonuses_per_weapon_type;
    QHash<int, int> damage_bonuses_per_weapon_type;
    QHash<Target::CreatureType, double> damage_bonuses_per_monster_type;
    QHash<Target::CreatureType, double> crit_dmg_bonuses_per_monster_type;
    QMap<MagicSchool, QVector<int>> magic_school_damage_changes;
    QMap<MagicSchool, double> magic_school_damage_modifiers;
    QMap<MagicSchool, QVector<Buff*>> magic_school_buffs_with_charges;

    unsigned axe_skill_bonus;
    unsigned dagger_skill_bonus;
    unsigned mace_skill_bonus;
    unsigned sword_skill_bonus;

    unsigned mp5;

    double melee_ability_crit_dmg_mod;
    double ranged_ability_crit_dmg_mod;
    double spell_crit_dmg_mod;
    double melee_attack_speed_mod;
    double ranged_attack_speed_mod;
    double total_phys_dmg_mod;
    double physical_damage_taken_mod;
    double spell_damage_taken_mod;
    double total_ap_mod;
    double agility_mod;
    double intellect_mod;
    double spirit_mod;
    double stamina_mod;
    double strength_mod;

    Target::CreatureType get_type_for_stat(const ItemStats);

    unsigned get_wpn_skill(Weapon*) const;
};

#endif // CHARACTERSTATS_H
