#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class MageSpells;


class Mage: public Character {
public:
    Mage(Race* race, EquipmentDb *equipment_db, SimSettings* sim_settings);
    ~Mage() override;

    QString get_class_color() const override;
    unsigned get_strength_modifier() const override;
    unsigned get_agility_modifier() const override;
    unsigned get_stamina_modifier() const override;
    unsigned get_intellect_modifier() const override;
    unsigned get_spirit_modifier() const override;
    double get_agi_needed_for_one_percent_phys_crit() const override;
    double get_int_needed_for_one_percent_spell_crit() const override;
    unsigned get_mp5_from_spirit() const override;
    double global_cooldown() const override;

    unsigned get_ap_per_strength() const override;
    unsigned get_ap_per_agi() const override;
    int get_highest_possible_armor_type() const override;
    QVector<int> get_weapon_proficiencies_for_slot(const int slot) const override;

    unsigned get_resource_level(const ResourceType) const override;

private:
    MageSpells* mage_spells;
    class Mana* mana;

    void initialize_talents() override;
    void reset_class_specific() override;
};

#endif // MAGE_H
