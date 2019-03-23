#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMap>
#include <QString>
#include <QVector>

#include "Resource.h"
#include "Rulesets.h"

class BerserkingBuff;
class BloodFuryBuff;
class CharacterEnchants;
class CharacterSpells;
class CharacterStats;
class ClassStatistics;
class CombatRoll;
class EnabledBuffs;
class EnabledProcs;
class Engine;
class Equipment;
class EquipmentDb;
class Faction;
class Race;
class Rotation;
class SimSettings;
class Stats;
class Talents;
class Target;
class Weapon;

class Character {
public:
    Character(QString class_name, Race* race, SimSettings* sim_settings);
    virtual ~Character();

    CharacterEnchants* get_enchants() const;
    CharacterSpells* get_spells() const;
    CharacterStats* get_stats() const;
    ClassStatistics* get_statistics() const;
    ClassStatistics* relinquish_ownership_of_statistics();
    CombatRoll* get_combat_roll() const;
    EnabledBuffs* get_enabled_buffs() const;
    EnabledProcs* get_enabled_procs() const;
    Engine* get_engine() const;
    Equipment* get_equipment() const;
    Faction* get_faction() const;
    Race* get_race();
    Rotation* get_rotation();
    SimSettings* get_sim_settings() const;
    Talents* get_talents() const;
    Target* get_target() const;

    void set_race(Race* race);
    bool race_available(Race*) const;

    QString get_name() const;
    virtual QString get_class_color() const = 0;

    virtual int get_highest_possible_armor_type() const = 0;
    virtual QVector<int> get_weapon_proficiencies_for_slot(const int) const = 0;

    virtual unsigned get_strength_modifier() const = 0;
    virtual unsigned get_agility_modifier() const = 0;
    virtual unsigned get_stamina_modifier() const = 0;
    virtual unsigned get_intellect_modifier() const = 0;
    virtual unsigned get_spirit_modifier() const = 0;
    virtual double get_agi_needed_for_one_percent_phys_crit() const = 0;
    virtual double get_int_needed_for_one_percent_spell_crit() const = 0;
    virtual unsigned get_ap_per_strength() const = 0;
    virtual unsigned get_ap_per_agi() const = 0;

    void set_rotation(Rotation*);
    void relink_spells();
    QString get_current_rotation_name() const;
    void perform_rotation();

    void change_target_creature_type(const QString& creature_type);
    void run_pre_combat_actions();

    void switch_faction();

    int get_clvl() const;
    virtual void set_clvl(const int);

    void add_player_reaction_event();

    bool is_dual_wielding();
    bool action_ready() const;
    void start_global_cooldown();
    virtual double global_cooldown() const;
    virtual bool on_global_cooldown() const;
    void start_trinket_cooldown(const double);
    bool on_trinket_cooldown() const;

    virtual void melee_mh_white_hit_effect(const bool = true);
    virtual void melee_mh_yellow_hit_effect(const bool = true);
    virtual void melee_mh_white_critical_effect(const bool = true);
    virtual void melee_mh_yellow_critical_effect(const bool = true);
    virtual void melee_oh_white_hit_effect(const bool = true);
    virtual void melee_oh_yellow_hit_effect(const bool = true);
    virtual void melee_oh_white_critical_effect(const bool = true);
    virtual void melee_oh_yellow_critical_effect(const bool = true);

    virtual void ranged_white_hit_effect(const bool = true);
    virtual void ranged_white_critical_effect(const bool = true);

    virtual void spell_hit_effect();
    virtual void spell_critical_effect();

    void run_extra_mh_attack();
    void run_extra_oh_attack();

    double get_ability_crit_dmg_mod() const;
    double get_spell_crit_dmg_mod() const;

    double get_random_normalized_mh_dmg();
    double get_random_non_normalized_mh_dmg();

    double get_random_normalized_oh_dmg();
    double get_random_non_normalized_oh_dmg();

    double get_random_normalized_ranged_dmg();
    double get_random_non_normalized_ranged_dmg();

    int get_mh_wpn_skill() const;
    int get_oh_wpn_skill() const;
    int get_ranged_wpn_skill() const;

    unsigned get_avg_mh_damage();

    void increase_melee_attack_speed(unsigned);
    void decrease_melee_attack_speed(unsigned);

    void increase_ranged_attack_speed(unsigned);
    void decrease_ranged_attack_speed(unsigned);

    void increase_ability_crit_dmg_mod(double);
    void decrease_ability_crit_dmg_mod(double);

    void increase_spell_crit_dmg_mod(double);
    void decrease_spell_crit_dmg_mod(double);

    bool has_mainhand() const;
    bool has_offhand() const;
    bool has_ranged() const;

    virtual unsigned get_resource_level(const ResourceType) const = 0;

    void reset();
    void prepare_set_of_combat_iterations();

    virtual void gain_mana(const unsigned);
    virtual void lose_mana(const unsigned);
    virtual void gain_rage(const unsigned);
    virtual void lose_rage(const unsigned);
    virtual void gain_energy(const unsigned);
    virtual void lose_energy(const unsigned);

    void increase_mh_flat_damage_bonus(const unsigned);
    void decrease_mh_flat_damage_bonus(const unsigned);

    void increase_oh_flat_damage_bonus(const unsigned);
    void decrease_oh_flat_damage_bonus(const unsigned);

    void increase_ranged_flat_damage_bonus(const unsigned);
    void decrease_ranged_flat_damage_bonus(const unsigned);

protected:
    QString class_name;
    Race* race;
    Engine* engine;
    Target* target;
    CombatRoll* roll;
    Faction* faction;
    Talents* talents;
    CharacterEnchants* available_enchants;
    CharacterStats* cstats;
    EnabledProcs* enabled_procs;
    EnabledBuffs* enabled_buffs;
    CharacterSpells* spells;
    ClassStatistics* statistics;
    Rotation* current_rotation;
    SimSettings* sim_settings;
    Resource* resource;

    QVector<QString> available_races;
    double ability_crit_dmg_mod;
    double spell_crit_dmg_mod;

    int clvl;
    double next_gcd;
    double next_trinket_cd;
    Ruleset ruleset;
    unsigned mh_flat_dmg_bonus;
    unsigned oh_flat_dmg_bonus;
    unsigned ranged_flat_dmg_bonus;

    virtual void initialize_talents() = 0;

    double get_normalized_dmg(const unsigned, const Weapon*);
    double get_non_normalized_dmg(const unsigned damage, const unsigned attack_power, const double wpn_speed);

    void run_mh_white_specific_proc_effects();
    void run_mh_yellow_specific_proc_effects();
    void run_oh_white_specific_proc_effects();
    void run_oh_yellow_specific_proc_effects();
    void run_ranged_white_specific_proc_effects();
    void run_ranged_yellow_specific_proc_effects();

    virtual void reset_resource();
    virtual void reset_class_specific() = 0;
};

#endif // CHARACTER_H
