#pragma once

#include <QVector>

class Character;
class PetAutoAttack;
class Random;
class Resource;
class Spell;

class Pet {
public:
    Pet(Character* pchar, const QString& name, double base_attack_speed, double base_dps);
    virtual ~Pet();

    QString get_name() const;

    virtual unsigned get_resource_level() const = 0;
    virtual void use_resource() = 0;
    void lose_resource(const unsigned loss);

    void start_attack();
    void add_gcd_event();
    void add_pet_reaction();
    bool action_ready();
    void auto_attack(const int iteration);

    double get_attack_speed() const;
    void increase_attack_speed(const unsigned increase);
    void decrease_attack_speed(const unsigned decrease);

    double get_damage_modifier() const;
    void increase_damage_modifier(const unsigned increase);
    void decrease_damage_modifier(const unsigned decrease);

    unsigned get_crit_chance() const;
    void increase_crit_chance(const unsigned increase);
    void decrease_crit_chance(const unsigned decrease);

    unsigned get_min_dmg() const;
    unsigned get_max_dmg() const;

    void increase_attack_power(const unsigned increase);
    void decrease_attack_power(const unsigned decrease);

    unsigned get_random_normalized_dmg();

    virtual void melee_critical_effect();

    void reset();
    Resource* get_resource();

protected:
    unsigned attack_power {252};
    Character* pchar;
    Resource* resource;
    const QString name;
    const double base_attack_speed;
    const double base_dps;
    unsigned min;
    unsigned max;
    Random* normalized_dmg_roll;
    const double global_cooldown;
    double next_gcd;
    bool is_attacking;

    unsigned crit_chance;

    double attack_speed_modifier;
    double damage_modifier;
    QVector<int> attack_speed_modifiers;
    QVector<int> damage_modifiers;

    PetAutoAttack* pet_auto_attack;
    QVector<Spell*> spells;

    void add_next_auto_attack();
    void add_spells();
    void remove_spells();
};
