#ifndef ROGUE_H
#define ROGUE_H

#include "Character.h"

class Energy;
class RogueSpells;


class Rogue: public Character {
public:
    Rogue(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings);
    virtual ~Rogue() override;

    QString get_name() const override;
    QString get_class_color() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    double get_agi_needed_for_one_percent_phys_crit() const override;
    double get_int_needed_for_one_percent_spell_crit() const override;
    double global_cooldown() const override;

    int get_ap_per_strength() const override;
    int get_ap_per_agi() const override;
    int get_highest_possible_armor_type() const override;
    QVector<int> get_weapon_proficiencies_for_slot(const int slot) const override;

    unsigned get_resource_level(const ResourceType) const override;
    void gain_energy(const unsigned) override;
    void lose_energy(const unsigned) override;

    unsigned get_combo_points() const;
    void spend_combo_points();
    void gain_combo_points(const unsigned);
    void enter_stealth();
    void exit_stealth();
    bool is_stealthed() const;

private:
    RogueSpells* rogue_spells;
    class Energy* energy;

    unsigned combo_points;
    bool stealthed;

    void initialize_talents() override;
    void reset_class_specific() override;
};

#endif // ROGUE_H
