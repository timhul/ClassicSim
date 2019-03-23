#include "CharacterLoader.h"

#include "Character.h"
#include "CharacterDecoder.h"
#include "CombatRoll.h"
#include "Druid.h"
#include "Dwarf.h"
#include "EnabledBuffs.h"
#include "Engine.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "GeneralBuffs.h"
#include "Gnome.h"
#include "Human.h"
#include "Hunter.h"
#include "Item.h"
#include "Mage.h"
#include "NightElf.h"
#include "Orc.h"
#include "Paladin.h"
#include "Priest.h"
#include "Race.h"
#include "Rogue.h"
#include "Rotation.h"
#include "RotationFileReader.h"
#include "Shaman.h"
#include "SimSettings.h"
#include "Talents.h"
#include "Target.h"
#include "Tauren.h"
#include "Troll.h"
#include "Undead.h"
#include "Warlock.h"
#include "Warrior.h"
#include "Weapon.h"

CharacterLoader::CharacterLoader(EquipmentDb *equipment_db,
                                 SimSettings *sim_settings,
                                 CharacterDecoder& decoder) :
    race(nullptr),
    equipment_db(equipment_db),
    sim_settings(sim_settings),
    decoder(decoder),
    success(false)
{}

CharacterLoader::~CharacterLoader() {
    delete race;
}

Character* CharacterLoader::initialize_new() {
    setup_race(decoder);
    if (race == nullptr) {
        fail("Failed to setup race");
        return nullptr;
    }

    Character* pchar = setup_pchar(decoder);
    if (pchar == nullptr) {
        fail("Failed to setup class");
        return nullptr;
    }

    initialize_existing(pchar);

    return pchar;
}

void CharacterLoader::initialize_existing(Character* pchar) {
    equip_gear(decoder, pchar);
    invest_talent_points(decoder, pchar);
    apply_external_buffs(decoder, pchar);
    apply_external_debuffs(decoder, pchar);
    setup_target(decoder, pchar);
    select_rotation(decoder, pchar);
    apply_enchants(decoder, pchar);
    apply_ruleset(decoder, pchar);

    success = true;
}

bool CharacterLoader::successful() const {
    return this->success;
}

QString CharacterLoader::get_error() const {
    return this->error;
}

void CharacterLoader::fail(const QString& error) {
    this->success = false;
    this->error = error;
}

Race* CharacterLoader::relinquish_ownership_of_race() {
    Race* tmp = race;
    race = nullptr;
    return tmp;
}

void CharacterLoader::setup_race(CharacterDecoder& decoder) {
    QString race_string = decoder.get_race();

    if (race_string == "Dwarf")
        race = new Dwarf();
    else if (race_string == "Gnome")
        race = new Gnome();
    else if (race_string == "Human")
        race = new Human();
    else if (race_string == "Night Elf")
        race = new NightElf();
    else if (race_string == "Orc")
        race = new Orc();
    else if (race_string == "Tauren")
        race = new Tauren();
    else if (race_string == "Troll")
        race = new Troll();
    else if (race_string == "Undead")
        race = new Undead();
}

void CharacterLoader::equip_gear(CharacterDecoder& decoder, Character* pchar) {
    bool key_converted;
    int item = decoder.get_value("MAINHAND").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_mainhand(item);

    item = decoder.get_value("OFFHAND").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_offhand(item);

    item = decoder.get_value("RANGED").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_ranged(item);

    item = decoder.get_value("HEAD").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_head(item);

    item = decoder.get_value("NECK").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_neck(item);

    item = decoder.get_value("SHOULDERS").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_shoulders(item);

    item = decoder.get_value("BACK").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_back(item);

    item = decoder.get_value("CHEST").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_chest(item);

    item = decoder.get_value("WRIST").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_wrist(item);

    item = decoder.get_value("GLOVES").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_gloves(item);

    item = decoder.get_value("BELT").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_belt(item);

    item = decoder.get_value("LEGS").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_legs(item);

    item = decoder.get_value("BOOTS").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_boots(item);

    item = decoder.get_value("RING1").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_ring1(item);

    item = decoder.get_value("RING2").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_ring2(item);

    item = decoder.get_value("TRINKET1").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_trinket1(item);

    item = decoder.get_value("TRINKET2").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_trinket2(item);
}

void CharacterLoader::invest_talent_points(CharacterDecoder &decoder, Character* pchar) {
    add_points_to_talent_tree(decoder, "LEFT", pchar);
    add_points_to_talent_tree(decoder, "MID", pchar);
    add_points_to_talent_tree(decoder, "RIGHT", pchar);
}

void CharacterLoader::add_points_to_talent_tree(CharacterDecoder &decoder, const QString& tree_position, Character* pchar) {
    QVector<QPair<QString, QString>> invested_talents = decoder.get_key_val_pairs(tree_position);

    for (auto & invested_talent : invested_talents) {
        for (int points = 0; points < invested_talent.second.toInt(); ++points) {
            pchar->get_talents()->increment_rank(tree_position, invested_talent.first);
        }
    }
}

void CharacterLoader::apply_external_buffs(CharacterDecoder& decoder, Character* pchar) {
    QVector<QPair<QString, QString>> buffs = decoder.get_key_val_pairs("BUFFS");

    for (auto & buff : buffs) {
        pchar->get_enabled_buffs()->get_general_buffs()->toggle_external_buff(buff.first);
    }
}

void CharacterLoader::apply_external_debuffs(CharacterDecoder& decoder, Character* pchar) {
    QVector<QPair<QString, QString>> buffs = decoder.get_key_val_pairs("DEBUFFS");

    for (auto & buff : buffs) {
        pchar->get_enabled_buffs()->get_general_buffs()->toggle_external_debuff(buff.first);
    }
}

void CharacterLoader::apply_enchants(CharacterDecoder& decoder, Character* pchar) {
    if (pchar->get_equipment()->get_mainhand() != nullptr) {
        pchar->get_equipment()->get_mainhand()->apply_enchant(get_enum_val(decoder.get_value("MH_ENCHANT")), pchar, WeaponSlots::MAINHAND);
        pchar->get_equipment()->get_mainhand()->apply_temporary_enchant(get_enum_val(decoder.get_value("MH_TEMPORARY_ENCHANT")), pchar, WeaponSlots::MAINHAND);
    }

    if (pchar->get_equipment()->get_offhand() != nullptr) {
        pchar->get_equipment()->get_offhand()->apply_enchant(get_enum_val(decoder.get_value("OH_ENCHANT")), pchar, WeaponSlots::OFFHAND);
        pchar->get_equipment()->get_offhand()->apply_temporary_enchant(get_enum_val(decoder.get_value("OH_TEMPORARY_ENCHANT")), pchar, WeaponSlots::OFFHAND);
    }

    if (pchar->get_equipment()->get_ranged() != nullptr)
        pchar->get_equipment()->get_ranged()->apply_enchant(get_enum_val(decoder.get_value("RANGED_ENCHANT")), pchar, WeaponSlots::RANGED);

    if (pchar->get_equipment()->get_head() != nullptr)
        pchar->get_equipment()->get_head()->apply_enchant(get_enum_val(decoder.get_value("HEAD_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_shoulders() != nullptr)
        pchar->get_equipment()->get_shoulders()->apply_enchant(get_enum_val(decoder.get_value("SHOULDER_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_back() != nullptr)
        pchar->get_equipment()->get_back()->apply_enchant(get_enum_val(decoder.get_value("BACK_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_chest() != nullptr)
        pchar->get_equipment()->get_chest()->apply_enchant(get_enum_val(decoder.get_value("CHEST_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_wrist() != nullptr)
        pchar->get_equipment()->get_wrist()->apply_enchant(get_enum_val(decoder.get_value("WRIST_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_gloves() != nullptr)
        pchar->get_equipment()->get_gloves()->apply_enchant(get_enum_val(decoder.get_value("GLOVES_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_legs() != nullptr)
        pchar->get_equipment()->get_legs()->apply_enchant(get_enum_val(decoder.get_value("LEGS_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_boots() != nullptr)
        pchar->get_equipment()->get_boots()->apply_enchant(get_enum_val(decoder.get_value("BOOTS_ENCHANT")), pchar);
}

void CharacterLoader::apply_ruleset(CharacterDecoder& decoder, Character* pchar) {
    pchar->get_sim_settings()->use_ruleset(static_cast<Ruleset>(decoder.get_value("RULESET").toInt()), pchar);
}

void CharacterLoader::setup_target(CharacterDecoder& decoder, Character* pchar) {
    pchar->get_target()->set_creature_type(decoder.get_value("TARGET_TYPE"));
    pchar->get_target()->set_lvl(decoder.get_value("TARGET_LVL").toInt());
}

void CharacterLoader::select_rotation(CharacterDecoder& decoder, Character* pchar) {
    QVector<Rotation*> new_rotations;
    RotationFileReader::add_rotations(new_rotations);

    QString rotation_name = decoder.get_value("ROTATION");

    for (auto & rotation : new_rotations) {
        if (rotation == nullptr)
            continue;

        if (pchar->get_name() != rotation->get_class() || rotation->get_name() != rotation_name) {
            delete rotation;
            continue;
        }

        pchar->set_rotation(rotation);
    }

    if (pchar->get_current_rotation_name() != rotation_name)
        fail("Failed to set rotation to " + rotation_name);
}

Character* CharacterLoader::setup_pchar(CharacterDecoder& decoder) {
    QString pchar_string = decoder.get_class();

    Character* pchar = nullptr;

    if (pchar_string == "Druid")
        pchar = dynamic_cast<Character*>(new Druid(race, equipment_db, sim_settings));
    if (pchar_string == "Hunter")
        pchar = dynamic_cast<Character*>(new Hunter(race, equipment_db, sim_settings));
    if (pchar_string == "Mage")
        pchar = dynamic_cast<Character*>(new Mage(race, equipment_db, sim_settings));
    if (pchar_string == "Paladin")
        pchar = dynamic_cast<Character*>(new Paladin(race, equipment_db, sim_settings));
    if (pchar_string == "Priest")
        pchar = dynamic_cast<Character*>(new Priest(race, equipment_db, sim_settings));
    if (pchar_string == "Rogue")
        pchar = dynamic_cast<Character*>(new Rogue(race, equipment_db, sim_settings));
    if (pchar_string == "Shaman")
        pchar = dynamic_cast<Character*>(new Shaman(race, equipment_db, sim_settings));
    if (pchar_string == "Warlock")
        pchar = dynamic_cast<Character*>(new Warlock(race, equipment_db, sim_settings));
    if (pchar_string == "Warrior")
        pchar = dynamic_cast<Character*>(new Warrior(race, equipment_db, sim_settings));

    if (pchar == nullptr)
        delete race;

    return pchar;
}

EnchantName::Name CharacterLoader::get_enum_val(const QString& enum_val_as_string) {
    return static_cast<EnchantName::Name>(enum_val_as_string.toInt());
}
