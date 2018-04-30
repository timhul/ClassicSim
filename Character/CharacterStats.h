#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include <QObject>

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

    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();
    float get_hit_chance(void) const;
    float get_crit_chance(void) const;

    float get_total_phys_dmg_mod() const;

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    float get_mh_haste();
    float get_oh_haste();

    void increase_mh_haste(const float);
    void decrease_mh_haste(const float);

    void increase_oh_haste(const float);
    void decrease_oh_haste(const float);

    void increase_strength(const int);
    void decrease_strength(const int);

    int get_melee_ap();
    void increase_melee_ap(const int);
    void decrease_melee_ap(const int);

    virtual void increase_hit(float);
    virtual void increase_crit(float);

    virtual void decrease_hit(float);
    virtual void decrease_crit(float);

    void increase_total_phys_dmg_mod(float);
    void decrease_total_phys_dmg_mod(float);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();

protected:
    Character* pchar;
    Equipment* equipment;
    Stats* base_stats;

    int ranged_ap;
    float mh_haste;
    float oh_haste;
    float ability_crit_dmg_mod;
    float total_phys_dmg_mod;

private:
};

#endif // CHARACTERSTATS_H
