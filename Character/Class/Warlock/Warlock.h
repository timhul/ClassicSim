#ifndef WARLOCK_H
#define WARLOCK_H

#include "Character.h"

class WarlockSpells;


class Warlock: public Character {
    Q_OBJECT
public:
    Warlock(Race* race, EquipmentDb* equipment_db, QObject *parent = nullptr);
    virtual ~Warlock() override;

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

    void reset_resource() override;
    void reset_spells() override;

protected:
private:
    void initialize_talents() override;

    WarlockSpells* warlock_spells;
};

#endif // WARLOCK_H
