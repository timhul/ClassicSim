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

class Character: public QObject {
    Q_OBJECT

public:
    Character(Race*, Engine*, Equipment*, QObject* parent = 0);
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
    virtual float global_cooldown() const;

    int get_mh_dmg();
    int get_oh_dmg();

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    int get_melee_ap();

    virtual void increase_hit(float);
    virtual void increase_crit(float);
    virtual void increase_attack_speed(int);

    virtual void decrease_hit(float);
    virtual void decrease_crit(float);
    virtual void decrease_attack_speed(int);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();

    float get_avg_mh_damage();

    bool has_mainhand() const;
    bool has_offhand() const;

    void reset();
    virtual void reset_spells() const = 0;

protected:
    Race* race;
    Engine* engine;
    Equipment* equipment;
    Talents* talents;
    Stats* stats;
    QVector<Buff*> buffs;
    QVector<int> attack_speed_buffs;

    int melee_ap;
    int ranged_ap;
    float percent_hit;
    float percent_crit;
    float mh_wpn_speed;
    float oh_wpn_speed;

    int clvl;
    bool melee_attacking;
    float last_action;

    virtual int get_ap_per_strength() const = 0;
    virtual int get_ap_per_agi() const = 0;

    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);

    virtual void initialize_talents() = 0;
private:
};

#endif // CHARACTER_H
