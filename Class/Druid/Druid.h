#pragma once

#include "Character.h"

class DruidSpells;
class Energy;
class Mana;
class Rage;

enum class DruidForm : int
{
    Caster,
    Bear,
    Cat,
    Moonkin,
};

class Druid : public Character {
public:
    Druid(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings, RaidControl* raid_control, const int party = -1, const int member = -1);
    ~Druid() override;

    double get_agi_needed_for_one_percent_phys_crit() const override;
    double get_int_needed_for_one_percent_spell_crit() const override;
    double get_mp5_from_spirit() const override;
    double global_cooldown() const override;
    double form_cooldown() const;
    void set_clvl(const unsigned clvl) override;

    unsigned get_melee_ap_per_strength() const override;
    unsigned get_melee_ap_per_agi() const override;
    unsigned get_ranged_ap_per_agi() const override;
    int get_highest_possible_armor_type() const override;
    QVector<int> get_weapon_proficiencies_for_slot(const int slot) const override;

    unsigned get_resource_level(const ResourceType) const override;
    unsigned get_max_resource_level(const ResourceType) const override;
    void gain_mana(const unsigned value) override;
    void lose_mana(const unsigned value) override;
    void gain_rage(const unsigned value) override;
    void lose_rage(const unsigned value) override;
    void gain_energy(const unsigned value) override;
    void lose_energy(const unsigned value) override;

    void increase_base_mana(const unsigned value) override;
    void decrease_base_mana(const unsigned value) override;

    void spell_critical_effect(MagicSchool magic_school) override;

    DruidForm get_current_form() const;
    bool on_form_cooldown() const;
    void cancel_form();
    void switch_to_form(const DruidForm new_form);

    unsigned rage_gained_from_dd(const unsigned damage_dealt) const;

    unsigned get_combo_points() const;
    void spend_combo_points();
    void gain_combo_points(const unsigned);

    void enter_stealth();
    void exit_stealth();
    bool is_stealthed() const;

private:
    DruidSpells* druid_spells;

    Energy* energy;
    Mana* mana;
    Rage* rage;

    DruidForm current_form {DruidForm::Caster};
    double next_form_cd {-10.0};
    double rage_conversion_value;
    unsigned combo_points {0};
    bool stealthed {false};

    void initialize_talents() override;
    void reset_class_specific() override;
    void reset_resource() override;
};
