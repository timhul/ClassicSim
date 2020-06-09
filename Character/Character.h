#pragma once

#include <QMap>
#include <QString>
#include <QVector>

#include "Resource.h"

class BerserkingBuff;
class BloodFuryBuff;
class CharacterEnchants;
class CharacterSpells;
class CharacterStats;
class CharacterTalents;
class ClassStatistics;
class CombatRoll;
class EnabledBuffs;
class EnabledProcs;
class Engine;
class Equipment;
class EquipmentDb;
class Faction;
class Pet;
class Race;
class RaidControl;
class Rotation;
class SimSettings;
class Stats;
class Target;
class Weapon;

enum class MagicSchool : int;

class Character {
public:
    Character(
        QString class_name, QString class_color, Race* race, SimSettings* sim_settings, RaidControl* raid_control, const int party, const int member);
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
    Pet* get_pet() const;
    Race* get_race();
    Resource* get_resource() const;
    SimSettings* get_sim_settings() const;
    CharacterTalents* get_talents() const;
    Target* get_target() const;
    RaidControl* get_raid_control() const;

    void set_race(Race* race);
    bool race_available(Race*) const;

    void set_special_statistics();

    virtual int get_highest_possible_armor_type() const = 0;
    virtual QVector<int> get_weapon_proficiencies_for_slot(const int) const = 0;

    virtual double get_agi_needed_for_one_percent_phys_crit() const = 0;
    virtual double get_int_needed_for_one_percent_spell_crit() const = 0;
    virtual unsigned get_melee_ap_per_strength() const = 0;
    virtual unsigned get_melee_ap_per_agi() const = 0;
    virtual unsigned get_ranged_ap_per_agi() const = 0;
    virtual double get_mp5_from_spirit() const;

    void change_target_creature_type(const QString& creature_type);

    void switch_faction();

    unsigned get_clvl() const;
    virtual void set_clvl(const unsigned);

    int get_party() const;
    int get_party_member() const;

    void add_player_reaction_event();

    bool is_attacking_from_behind() const;
    void set_is_tanking(bool new_value);
    bool is_tanking() const;

    virtual bool is_dual_wielding() const;
    bool action_ready() const;
    void start_global_cooldown();
    virtual double global_cooldown() const;
    bool on_global_cooldown() const;
    void start_trinket_cooldown(const double);
    bool on_trinket_cooldown() const;
    double time_until_action_ready() const;

    virtual void melee_mh_white_hit_effect();
    virtual void melee_mh_white_critical_effect();
    void melee_mh_yellow_hit_effect();
    virtual void melee_mh_yellow_critical_effect();
    void melee_oh_white_hit_effect();
    virtual void melee_oh_white_critical_effect();

    void ranged_white_hit_effect();
    void ranged_yellow_hit_effect();

    virtual void spell_hit_effect(MagicSchool magic_school);
    virtual void spell_critical_effect(MagicSchool magic_school);

    double get_random_normalized_mh_dmg();
    double get_random_non_normalized_mh_dmg();

    double get_random_non_normalized_oh_dmg();

    double get_random_normalized_ranged_dmg();
    double get_random_non_normalized_ranged_dmg();

    unsigned get_mh_wpn_skill() const;
    unsigned get_oh_wpn_skill() const;
    unsigned get_ranged_wpn_skill() const;

    unsigned get_avg_mh_damage();
    unsigned get_avg_oh_damage();

    void increase_melee_attack_speed(unsigned);
    void decrease_melee_attack_speed(unsigned);

    void increase_ranged_attack_speed(unsigned);
    void decrease_ranged_attack_speed(unsigned);

    bool has_mainhand() const;
    bool has_offhand() const;
    bool has_ranged() const;

    virtual unsigned get_resource_level(const ResourceType) const = 0;
    virtual unsigned get_max_resource_level(const ResourceType) const = 0;

    void reset();
    void prepare_set_of_combat_iterations();

    void gain_resource(const ResourceType resource_type, const unsigned value);
    void lose_resource(const ResourceType resource_type, const unsigned value);
    virtual void gain_mana(const unsigned);
    virtual void lose_mana(const unsigned);
    virtual void gain_rage(const unsigned);
    virtual void lose_rage(const unsigned);
    virtual void gain_energy(const unsigned);
    virtual void lose_energy(const unsigned);
    virtual void gain_focus(const unsigned);

    virtual void increase_base_mana(const unsigned value);
    virtual void decrease_base_mana(const unsigned value);

    virtual void increase_mp5_within_5sr_modifier(const double increase);
    virtual void decrease_mp5_within_5sr_modifier(const double decrease);

    const int instance_id;
    const QString class_name;
    const QString class_color;

    QString const& get_rotation_name() const;
    void set_rotation_name(QString name);

protected:
    Race* race;
    Engine* engine;
    Target* target;
    CombatRoll* roll;
    Faction* faction;
    CharacterTalents* talents;
    CharacterEnchants* available_enchants {nullptr};
    CharacterStats* cstats {nullptr};
    EnabledProcs* enabled_procs;
    EnabledBuffs* enabled_buffs;
    CharacterSpells* spells {nullptr};
    ClassStatistics* statistics;
    SimSettings* sim_settings;
    Resource* resource {nullptr};
    Pet* pet {nullptr};
    RaidControl* raid_control {nullptr};

    QString rotation_name;

    QString player_name;
    QVector<QString> available_races;

    unsigned clvl {1};
    double next_gcd;
    double next_trinket_cd;
    int party;
    int party_member;

    bool char_is_tanking = false;

    virtual void initialize_talents() = 0;

    double get_normalized_dmg(const unsigned, const Weapon*);
    double get_non_normalized_dmg(const unsigned damage, const unsigned attack_power, const double wpn_speed);

    virtual void reset_resource();
    virtual void reset_class_specific() = 0;

private:
    // Special statistics cases
    bool is_orc_warlock = false;
    uint intellect_offset = 0;
    uint spirit_offset = 0;
};
