#pragma once

#include "Character.h"

class EnchantInfo;
class Energy;
class InstantPoison;
class RogueSpells;
class RelentlessStrikes;
class Ruthlessness;
class SealFate;
class SwordSpecialization;

class Rogue : public Character {
public:
    Rogue(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings, RaidControl* raid_control, const int party = -1, const int member = -1);
    ~Rogue() override;

    double get_agi_needed_for_one_percent_phys_crit() const override;
    double get_int_needed_for_one_percent_spell_crit() const override;
    double global_cooldown() const override;

    unsigned get_melee_ap_per_strength() const override;
    unsigned get_melee_ap_per_agi() const override;
    unsigned get_ranged_ap_per_agi() const override;
    int get_highest_possible_armor_type() const override;
    QVector<int> get_weapon_proficiencies_for_slot(const int slot) const override;

    unsigned get_resource_level(const ResourceType) const override;
    unsigned get_max_resource_level(const ResourceType) const override;
    void gain_energy(const unsigned) override;
    void lose_energy(const unsigned) override;

    unsigned get_combo_points() const;
    void spend_combo_points();
    void gain_combo_points(const unsigned);
    void enter_stealth();
    void exit_stealth();
    bool is_stealthed() const;

    Energy* get_energy() const;
    InstantPoison* get_mh_instant_poison() const;
    InstantPoison* get_oh_instant_poison() const;
    RelentlessStrikes* get_relentless_strikes() const;
    Ruthlessness* get_ruthlessness() const;
    SealFate* get_seal_fate() const;
    SwordSpecialization* get_sword_spec() const;

private:
    RogueSpells* rogue_spells;
    Energy* energy;
    InstantPoison* mh_instant_poison;
    InstantPoison* oh_instant_poison;
    RelentlessStrikes* relentless_strikes;
    Ruthlessness* ruthlessness;
    SealFate* seal_fate;
    SwordSpecialization* sword_spec;
    EnchantInfo* enchant_info;

    unsigned combo_points;
    bool stealthed;

    void initialize_talents() override;
    void reset_class_specific() override;
};
