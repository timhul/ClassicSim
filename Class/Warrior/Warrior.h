#pragma once

#include "Character.h"

class Rage;
class WarriorSpells;

namespace WarriorStances {
    static const int Battle = 0;
    static const int Defensive = 1;
    static const int Berserker = 2;
} // namespace WarriorStances

class Warrior : public Character {
public:
    Warrior(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings, RaidControl* raid_control, const int party = -1, const int member = -1);
    ~Warrior() override;

    double get_agi_needed_for_one_percent_phys_crit() const override;
    double get_int_needed_for_one_percent_spell_crit() const override;
    unsigned get_melee_ap_per_strength() const override;
    unsigned get_melee_ap_per_agi() const override;
    unsigned get_ranged_ap_per_agi() const override;
    void set_clvl(const unsigned) override;

    int get_highest_possible_armor_type() const override;
    QVector<int> get_weapon_proficiencies_for_slot(const int slot) const override;

    double global_cooldown() const override;
    double stance_cooldown() const;
    bool on_stance_cooldown() const;
    void increase_stance_rage_remainder();
    void decrease_stance_rage_remainder();
    unsigned get_stance_remainder() const;
    unsigned get_resource_level(const ResourceType) const override;
    unsigned get_max_resource_level(const ResourceType) const override;
    void gain_rage(const unsigned) override;
    void lose_rage(const unsigned) override;
    unsigned rage_gained_from_dd(const unsigned) const;
    void switch_to_battle_stance();
    void switch_to_berserker_stance();
    void switch_to_defensive_stance();
    bool in_battle_stance() const;
    bool in_berserker_stance() const;
    bool in_defensive_stance() const;

    void melee_mh_white_critical_effect() override;
    void melee_mh_yellow_critical_effect() override;
    void melee_oh_white_critical_effect() override;

    bool is_dual_wielding() const override;

private:
    int stance;
    unsigned stance_rage_remainder;
    double next_stance_cd;
    double rage_conversion_value {};
    Rage* rage;
    WarriorSpells* warr_spells;

    void initialize_talents() override;
    void new_stance_effect();

    void reset_class_specific() override;
};
