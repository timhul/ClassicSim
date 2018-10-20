#ifndef CHARACTER_H
#define CHARACTER_H


#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

#include "Resource.h"
#include "Rulesets.h"

class ActiveProcs;
class ActiveBuffs;
class BerserkingBuff;
class BloodFuryBuff;
class CharacterStats;
class ClassStatistics;
class CombatRoll;
class Engine;
class Equipment;
class EquipmentDb;
class Faction;
class Race;
class Rotation;
class SimSettings;
class Spells;
class Stats;
class Talents;
class Target;
class Weapon;

class Character: public QObject {
    Q_OBJECT

public:
    Character(Race*, EquipmentDb *equipment_db, SimSettings* sim_settings, QObject* parent = nullptr);
    virtual ~Character();

    Race* get_race(void);
    virtual QString get_name() const = 0;
    bool race_available(Race*) const;
    void set_race(Race* race);
    bool set_rotation(Rotation*);
    QString get_current_rotation_name() const;
    void perform_rotation();
    Rotation* get_rotation();
    void change_target_creature_type(const QString& creature_type);

    void switch_faction();

    virtual int get_highest_possible_armor_type() const = 0;
    virtual QVector<int> get_weapon_proficiencies_for_slot(const int) const = 0;

    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;
    virtual double get_agi_needed_for_one_percent_phys_crit() const = 0;
    virtual double get_int_needed_for_one_percent_spell_crit() const = 0;
    virtual int get_ap_per_strength() const = 0;
    virtual int get_ap_per_agi() const = 0;

    virtual QString get_class_color() const = 0;

    int get_clvl(void) const;
    virtual void set_clvl(const int);
    Engine* get_engine(void) const;
    Target* get_target(void) const;
    CombatRoll* get_combat_roll(void) const;
    Faction* get_faction(void) const;
    Equipment* get_equipment(void) const;
    Talents* get_talents(void) const;
    ActiveBuffs* get_active_buffs(void) const;
    Spells* get_spells(void) const;
    CharacterStats* get_stats(void) const;
    ClassStatistics* get_statistics(void) const;
    virtual ClassStatistics* relinquish_ownership_of_statistics(void); // mark pure virtual
    ActiveProcs* get_active_procs() const;
    SimSettings* get_sim_settings() const;

    BerserkingBuff* get_berserking_buff() const;
    BloodFuryBuff* get_blood_fury_buff() const;

    void add_player_reaction_event();

    bool is_dual_wielding(void);
    bool is_melee_attacking(void) const;
    void start_attack(void);
    void stop_attack(void);
    bool action_ready(void) const;
    void start_global_cooldown();
    virtual double global_cooldown() const;
    virtual bool on_global_cooldown() const;

    virtual void melee_mh_white_hit_effect();
    virtual void melee_mh_yellow_hit_effect();
    virtual void melee_mh_white_critical_effect();
    virtual void melee_mh_yellow_critical_effect();
    virtual void melee_oh_white_hit_effect();
    virtual void melee_oh_yellow_hit_effect();
    virtual void melee_oh_white_critical_effect();
    virtual void melee_oh_yellow_critical_effect();

    virtual void spell_hit_effect();
    virtual void spell_critical_effect();

    void run_mh_white_specific_proc_effects();
    void run_mh_yellow_specific_proc_effects();
    void run_oh_white_specific_proc_effects();
    void run_oh_yellow_specific_proc_effects();
    void run_extra_mh_attack();
    void run_extra_oh_attack();

    double get_ability_crit_dmg_mod() const;
    double get_spell_crit_dmg_mod() const;

    double get_random_normalized_mh_dmg();
    double get_random_non_normalized_mh_dmg();

    double get_random_normalized_oh_dmg();
    double get_random_non_normalized_oh_dmg();

    int get_mh_wpn_skill() const;
    int get_oh_wpn_skill() const;
    int get_wpn_skill(Weapon*) const;

    unsigned get_avg_mh_damage();
    double get_normalized_dmg(const unsigned, const Weapon*);
    double get_non_normalized_dmg(const unsigned, const double);

    void increase_attack_speed(int);
    void decrease_attack_speed(int);

    void increase_ability_crit_dmg_mod(double);
    void decrease_ability_crit_dmg_mod(double);

    void increase_spell_crit_dmg_mod(double);
    void decrease_spell_crit_dmg_mod(double);

    bool has_mainhand() const;
    bool has_offhand() const;

    virtual unsigned get_resource_level() const;

    void reset();
    void prepare_set_of_combat_iterations();
    virtual void reset_resource() = 0;
    virtual void reset_spells() = 0;

    virtual void gain_mana(const unsigned);
    virtual void lose_mana(const unsigned);
    virtual void gain_rage(const unsigned);
    virtual void lose_rage(const unsigned);
    virtual void gain_energy(const unsigned);
    virtual void lose_energy(const unsigned);

    void dump();

protected:
    Race* race;
    Engine* engine;
    Target* target;
    CombatRoll* roll;
    Faction* faction;
    Talents* talents;
    CharacterStats* cstats;
    ActiveProcs* active_procs;
    ActiveBuffs* active_buffs;
    Spells* spells{};
    ClassStatistics* statistics;
    Rotation* current_rotation;
    SimSettings* sim_settings;

    BerserkingBuff* berserking_buff;
    BloodFuryBuff* blood_fury_buff;

    QVector<QString> available_races;
    double ability_crit_dmg_mod;
    double spell_crit_dmg_mod;

    int clvl;
    bool melee_attacking;
    double next_gcd;
    Ruleset ruleset;

    virtual void initialize_talents() = 0;

    void apply_racial_effects();
    void remove_racial_effects();

private:
};

#endif // CHARACTER_H
