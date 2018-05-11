#ifndef ROGUE_H
#define ROGUE_H

#include "Character.h"
#include "CombatRoll.h"

class Rogue: public Character {
    Q_OBJECT
public:
    Rogue(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, Faction* faction, QObject *parent = 0) :
        Character(race, engine, _eq, _roll, faction, parent) {
        available_races.append("Dwarf");
        available_races.append("Gnome");
        available_races.append("Human");
        available_races.append("Night Elf");
        available_races.append("Orc");
        available_races.append("Troll");
        available_races.append("Undead");
    }

    virtual ~Rogue() {}

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

#endif // ROGUE_H
