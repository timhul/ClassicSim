#ifndef SHAMAN_H
#define SHAMAN_H

#include "Character.h"
#include "CombatRoll.h"

class Shaman: public Character {
    Q_OBJECT
public:
    Shaman(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, Faction* faction, QObject *parent = 0) :
        Character(race, engine, _eq, _roll, faction, parent) {
        available_races.append("Orc");
        available_races.append("Tauren");
        available_races.append("Troll");
    }

    virtual ~Shaman() {}

    QString get_name() const override;
    QString get_class_color() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    int get_agi_needed_for_one_percent_phys_crit() const override;
    int get_int_needed_for_one_percent_spell_crit() const override;
    float global_cooldown() const override;

    int get_ap_per_strength() const override;
    int get_ap_per_agi() const override;

protected:
private:
    CombatRoll* roll;

    void initialize_talents() override;
};

#endif // SHAMAN_H
