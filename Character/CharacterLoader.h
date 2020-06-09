#pragma once

#include <QString>

#include "EnchantName.h"

class Character;
class CharacterDecoder;
class EquipmentDb;
class Race;
class RandomAffixes;
class RaidControl;
class SimSettings;
class Target;

class CharacterLoader {
public:
    CharacterLoader(
        EquipmentDb* equipment_db, RandomAffixes* random_affixes, SimSettings* sim_settings, RaidControl* raid_control, CharacterDecoder& decoder);
    ~CharacterLoader();

    Character* initialize_new();
    Character* initialize_raid_member(const int party, const int member);
    void initialize_existing(Character* pchar);
    bool successful() const;
    QString get_error() const;

    Race* relinquish_ownership_of_race();

private:
    Race* race;
    EquipmentDb* equipment_db;
    RandomAffixes* random_affixes;
    SimSettings* sim_settings;
    Target* target;
    RaidControl* raid_control;
    CharacterDecoder& decoder;

    bool success;
    QString error;

    void fail(const QString& error);

    void setup_race(CharacterDecoder& decoder);
    Character* setup_pchar(CharacterDecoder& decoder);
    void equip_gear(CharacterDecoder& decoder, Character* pchar);
    void invest_talent_points(CharacterDecoder& decoder, Character* pchar);
    void add_points_to_talent_tree(CharacterDecoder& decoder, const QString& tree_position, Character* pchar);
    void apply_external_buffs(CharacterDecoder& decoder, Character* pchar);
    void apply_external_debuffs(CharacterDecoder& decoder, Character* pchar);
    void apply_enchants(CharacterDecoder& decoder, Character* pchar);
    void apply_ruleset(CharacterDecoder& decoder, Character* pchar);
    void apply_tanking(CharacterDecoder& decoder, Character* pchar);
    void setup_target(CharacterDecoder& decoder);
    void select_rotation(CharacterDecoder& decoder, Character* pchar);
    EnchantName::Name get_enum_val(const QString& enum_val_as_string);
};
