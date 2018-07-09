#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include <QObject>
#include <QVector>

class Character;
class Race;
class Equipment;
class Stats;
class Weapon;

class CharacterStats: public QObject {
    Q_OBJECT

public:
    CharacterStats(Character*, Equipment*, QObject* parent = 0);
    virtual ~CharacterStats();

    Equipment* get_equipment(void) const;
    Stats* get_stats(void) const;

    int get_strength() const;
    int get_agility() const;
    int get_stamina() const;
    int get_intellect() const;
    int get_spirit() const;
    float get_hit_chance(void) const;
    float get_crit_chance(void) const;

    float get_total_phys_dmg_mod() const;

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

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

    int get_melee_ap();
    void increase_melee_ap(const int);
    void decrease_melee_ap(const int);

    virtual void increase_hit(float);
    virtual void increase_crit(float);

    virtual void decrease_hit(float);
    virtual void decrease_crit(float);

    void increase_total_phys_dmg_mod(const int);
    void decrease_total_phys_dmg_mod(const int);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();

protected:
    Character* pchar;
    Equipment* equipment;
    Stats* base_stats;
    QVector<int> attack_speed_buffs;
    QVector<int> phys_dmg_buffs;

    int ranged_ap;
    float haste_factor;
    float ability_crit_dmg_mod;
    float total_phys_dmg_mod;

private:
};

#endif // CHARACTERSTATS_H
