#ifndef STATS_H
#define STATS_H

#include <QString>
#include <QMap>
#include <QObject>

class Character;

class Stats: public QObject {
    Q_OBJECT

public:
    Stats(Character*, QObject* parent = 0);
    ~Stats();

    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();

    int get_melee_ap_str_excluded();
    int get_melee_ap_total();

    void increase_base_melee_ap(const int increase);
    void decrease_base_melee_ap(const int decrease);

    float get_hit_chance(void) const;
    float get_crit_chance(void) const;

    void increase_str(const int increase);
    void decrease_str(const int decrease);

    void increase_agi(const int);
    void decrease_agi(const int);

    void increase_stam(const int);
    void decrease_stam(const int);

    void increase_int(const int);
    void decrease_int(const int);

    void increase_spi(const int);
    void decrease_spi(const int);

    void increase_crit(const float value);
    void decrease_crit(const float value);

    void increase_hit(const float value);
    void decrease_hit(const float value);

    void increase_attack_speed(const float value);
    void decrease_attack_speed(const float value);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();

    void set_melee_ap_per_str(const int value);
    void set_melee_ap_per_agi(const int value);

    void set_str_multiplier(const float value);
    void set_agi_multiplier(const float value);
    void set_stam_multiplier(const float value);
    void set_spi_multiplier(const float value);
    void set_int_multiplier(const float value);

private:
    Character* pchar;
    int STR;
    int AGI;
    int STAM;
    int INT;
    int SPI;
    int melee_ap;
    int melee_ap_per_str;
    int melee_ap_per_agi;
    int ranged_ap;
    float percent_hit;
    float percent_crit;
    float percent_attack_speed;

    float str_multiplier;
    float agi_multiplier;
    float stam_multiplier;
    float spi_multiplier;
    float int_multiplier;
};

#endif // STATS_H
