#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QVector>

class ActiveProcs;
class ActiveBuffs;
class CharacterStats;
class ClassStatistics;
class CombatRoll;
class Engine;
class Equipment;
class Faction;
class Race;
class Rotation;
class Spells;
class Stats;
class Talents;
class Weapon;

class Character: public QObject {
    Q_OBJECT

public:
    Character(Race*, Engine*, Equipment*, CombatRoll*, Faction* faction, QObject* parent = 0);
    virtual ~Character();

    Race* get_race(void);
    virtual QString get_name() const = 0;
    bool race_available(Race*) const;
    void set_race(Race* race);
    bool set_rotation(const int index);
    QVector<QString> get_rotation_names() const;
    QString get_current_rotation_name() const;
    void perform_rotation();

    void switch_faction();

    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;
    virtual int get_agi_needed_for_one_percent_phys_crit() const = 0;
    virtual int get_int_needed_for_one_percent_spell_crit() const = 0;
    virtual int get_ap_per_strength() const = 0;
    virtual int get_ap_per_agi() const = 0;

    virtual QString get_class_color() const = 0;

    int get_clvl(void) const;
    virtual void set_clvl(const int);
    Engine* get_engine(void) const;
    CombatRoll* get_combat_roll(void) const;
    Equipment* get_equipment(void) const;
    Talents* get_talents(void) const;
    ActiveBuffs* get_active_buffs(void) const;
    Spells* get_spells(void) const;
    CharacterStats* get_stats(void) const;
    ClassStatistics* get_statistics(void) const;
    ActiveProcs* get_active_procs() const;

    bool is_dual_wielding(void);
    bool is_melee_attacking(void) const;
    void start_attack(void);
    void stop_attack(void);
    bool action_ready(void) const;
    void start_global_cooldown();
    virtual float global_cooldown() const;
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

    float get_ability_crit_dmg_mod() const;
    float get_total_phys_dmg_mod() const;

    float get_random_normalized_mh_dmg();
    float get_random_non_normalized_mh_dmg();

    float get_random_normalized_oh_dmg();
    float get_random_non_normalized_oh_dmg();

    int get_avg_mh_damage();
    float get_normalized_dmg(const int, const Weapon*);
    float get_non_normalized_dmg(const int, const float);

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    void increase_attack_speed(int);
    void decrease_attack_speed(int);

    void increase_ability_crit_dmg_mod(float);
    void decrease_ability_crit_dmg_mod(float);

    bool has_mainhand() const;
    bool has_offhand() const;

    virtual int get_resource_level() const;

    void reset();
    // TODO: Mark as abstract to force implementation.
    virtual void reset_resource() {}
    // TODO: Mark as abstract to force implementation.
    virtual void reset_spells() {}

    void dump();

protected:
    Race* race;
    Engine* engine;
    CombatRoll* roll;
    Faction* faction;
    Talents* talents;
    CharacterStats* cstats;
    ActiveProcs* active_procs;
    ActiveBuffs* active_buffs;
    Spells* spells;
    ClassStatistics* statistics;
    QVector<Rotation*> rotations;
    Rotation* current_rotation;

    QVector<QString> available_races;
    float ability_crit_dmg_mod;

    int clvl;
    bool melee_attacking;
    float last_action;


    virtual void initialize_talents() = 0;

    int get_wpn_skill(Weapon*) const;

private:
};

#endif // CHARACTER_H
