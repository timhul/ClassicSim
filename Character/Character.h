#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QVector>

class Race;
class Engine;
class Equipment;
class Talents;
class Stats;
class Buff;
class CombatRoll;
class Spell;
class Weapon;

class Character: public QObject {
    Q_OBJECT

public:
    Character(Race*, Engine*, Equipment*, CombatRoll*, QObject* parent = 0);
    virtual ~Character();

    Race* get_race(void);
    virtual QString get_name() const = 0;

    virtual void rotation(void) = 0;
    virtual void mh_auto_attack(const int) = 0;
    virtual void oh_auto_attack(const int) = 0;

    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;

    virtual QString get_class_color() const = 0;


    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();
    float get_hit_chance(void) const;
    float get_crit_chance(void) const;
    int get_clvl(void) const;
    void set_clvl(const int&);
    Engine* get_engine(void) const;
    Equipment* get_equipment(void) const;
    Talents* get_talents(void) const;
    bool is_dual_wielding(void);
    bool is_melee_attacking(void) const;
    void start_attack(void);
    void stop_attack(void);
    bool action_ready(void) const;
    void start_global_cooldown();
    virtual float global_cooldown() const;

    float get_ability_crit_dmg_mod() const;
    float get_total_phys_dmg_mod() const;
    int get_random_mh_dmg();
    int get_random_oh_dmg();
    int get_avg_mh_damage();
    int get_normalized_dmg(const int, const float);

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    int get_melee_ap();
    void increase_melee_ap(const int);
    void decrease_melee_ap(const int);

    virtual void increase_hit(float);
    virtual void increase_crit(float);
    virtual void increase_attack_speed(int);

    virtual void decrease_hit(float);
    virtual void decrease_crit(float);
    virtual void decrease_attack_speed(int);

    void increase_ability_crit_dmg_mod(float);
    void decrease_ability_crit_dmg_mod(float);

    void increase_total_phys_dmg_mod(float);
    void decrease_total_phys_dmg_mod(float);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();


    bool has_mainhand() const;
    bool has_offhand() const;

    void reset();
    // TODO: Mark as abstract to force implementation.
    virtual void reset_resource() {}

    void dump();

protected:
    Race* race;
    Engine* engine;
    Equipment* equipment;
    CombatRoll* roll;
    Talents* talents;
    Stats* base_stats;
    QVector<Spell*> spells;
    QVector<Buff*> buffs;
    QVector<int> attack_speed_buffs;

    int ranged_ap;
    float mh_wpn_speed;
    float oh_wpn_speed;
    float ability_crit_dmg_mod;
    float total_phys_dmg_mod;

    int clvl;
    bool melee_attacking;
    float last_action;

    virtual int get_ap_per_strength() const = 0;
    virtual int get_ap_per_agi() const = 0;

    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);

    virtual void initialize_talents() = 0;

    int get_wpn_skill(Weapon*) const;

private:
};

#endif // CHARACTER_H
