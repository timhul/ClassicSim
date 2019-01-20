#ifndef CHARACTERLOADER_H
#define CHARACTERLOADER_H

#include <QString>

#include "EnchantName.h"

class Character;
class CharacterDecoder;
class EquipmentDb;
class Race;
class SimSettings;

class CharacterLoader {
public:
    CharacterLoader(EquipmentDb* equipment_db, SimSettings* sim_settings, CharacterDecoder &decoder);
    ~CharacterLoader();

    void initialize();
    bool successful() const;
    QString get_error() const;

    Character* relinquish_ownership_of_pchar();
    Race* relinquish_ownership_of_race();

private:
    Character* pchar;
    Race* race;
    EquipmentDb* equipment_db;
    SimSettings* sim_settings;
    CharacterDecoder& decoder;

    bool success;
    QString error;

    void fail(QString error);

    void setup_race(CharacterDecoder& decoder);
    void setup_pchar(CharacterDecoder& decoder);
    void equip_gear(CharacterDecoder& decoder);
    void invest_talent_points(CharacterDecoder& decoder);
    void add_points_to_talent_tree(CharacterDecoder &decoder, const QString& tree_position);
    void apply_external_buffs(CharacterDecoder& decoder);
    void apply_enchants(CharacterDecoder& decoder);
    void apply_ruleset(CharacterDecoder& decoder);
    void setup_target(CharacterDecoder& decoder);
    void select_rotation(CharacterDecoder& decoder);
    EnchantName::Name get_enum_val(const QString& enum_val_as_string);
};

#endif // CHARACTERLOADER_H
