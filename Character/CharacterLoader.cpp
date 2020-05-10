#include "CharacterLoader.h"

#include "Character.h"
#include "CharacterDecoder.h"
#include "CharacterSpells.h"
#include "CharacterTalents.h"
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
#include "RaidControl.h"
#include "RandomAffixes.h"
#include "Rogue.h"
#include "Rotation.h"
#include "RotationFileReader.h"
#include "Shaman.h"
#include "SimSettings.h"
#include "Target.h"
#include "Tauren.h"
#include "Troll.h"
#include "Undead.h"
#include "Warlock.h"
#include "Warrior.h"
#include "Weapon.h"

CharacterLoader::CharacterLoader(
    EquipmentDb* equipment_db, RandomAffixes* random_affixes, SimSettings* sim_settings, RaidControl* raid_control, CharacterDecoder& decoder) :
    race(nullptr),
    equipment_db(equipment_db),
    random_affixes(random_affixes),
    sim_settings(sim_settings),
    target(raid_control->get_target()),
    raid_control(raid_control),
    decoder(decoder),
    enchant_info(EnchantInfo()),
    success(false) {}

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
    setup_target(decoder);
    select_rotation(decoder, pchar);
    apply_enchants(decoder, pchar);
    apply_ruleset(decoder, pchar);
    apply_tanking(decoder, pchar);

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
    const QString race_string = decoder.get_value("RACE", CharacterDecoder::MANDATORY);

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
    bool affix_converted;
    int item = decoder.get_value("MAINHAND").toInt(&key_converted);
    unsigned affix = decoder.get_value("MH_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_mainhand(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_mainhand(item);
    }

    item = decoder.get_value("OFFHAND").toInt(&key_converted);
    affix = decoder.get_value("OH_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_offhand(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_offhand(item);
    }

    item = decoder.get_value("RANGED").toInt(&key_converted);
    affix = decoder.get_value("RANGED_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_ranged(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_ranged(item);
    }

    item = decoder.get_value("HEAD").toInt(&key_converted);
    affix = decoder.get_value("HEAD_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_head(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_head(item);
    }

    item = decoder.get_value("NECK").toInt(&key_converted);
    affix = decoder.get_value("NECK_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_neck(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_neck(item);
    }

    item = decoder.get_value("SHOULDERS").toInt(&key_converted);
    affix = decoder.get_value("SHOULDERS_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_shoulders(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_shoulders(item);
    }

    item = decoder.get_value("BACK").toInt(&key_converted);
    affix = decoder.get_value("BACK_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_back(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_back(item);
    }

    item = decoder.get_value("CHEST").toInt(&key_converted);
    affix = decoder.get_value("CHEST_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_chest(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_chest(item);
    }

    item = decoder.get_value("WRIST").toInt(&key_converted);
    affix = decoder.get_value("WRIST_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_wrist(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_wrist(item);
    }

    item = decoder.get_value("GLOVES").toInt(&key_converted);
    affix = decoder.get_value("GLOVES_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_gloves(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_gloves(item);
    }

    item = decoder.get_value("BELT").toInt(&key_converted);
    affix = decoder.get_value("BELT_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_belt(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_belt(item);
    }

    item = decoder.get_value("LEGS").toInt(&key_converted);
    affix = decoder.get_value("LEGS_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_legs(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_legs(item);
    }

    item = decoder.get_value("BOOTS").toInt(&key_converted);
    affix = decoder.get_value("BOOTS_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_boots(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_boots(item);
    }

    item = decoder.get_value("RING1").toInt(&key_converted);
    affix = decoder.get_value("RING1_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_ring1(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_ring1(item);
    }

    item = decoder.get_value("RING2").toInt(&key_converted);
    affix = decoder.get_value("RING2_AFFIX").toUInt(&affix_converted);
    if (key_converted) {
        if (affix_converted)
            pchar->get_equipment()->set_ring2(item, random_affixes->get_affix(affix));
        else
            pchar->get_equipment()->set_ring2(item);
    }

    item = decoder.get_value("TRINKET1").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_trinket1(item);

    item = decoder.get_value("TRINKET2").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_trinket2(item);

    item = decoder.get_value("PROJECTILE").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_projectile(item);

    item = decoder.get_value("RELIC").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_relic(item);

    item = decoder.get_value("QUIVER").toInt(&key_converted);
    if (key_converted)
        pchar->get_equipment()->set_quiver(item);
}

void CharacterLoader::invest_talent_points(CharacterDecoder& decoder, Character* pchar) {
    add_points_to_talent_tree(decoder, "LEFT", pchar);
    add_points_to_talent_tree(decoder, "MID", pchar);
    add_points_to_talent_tree(decoder, "RIGHT", pchar);
}

void CharacterLoader::add_points_to_talent_tree(CharacterDecoder& decoder, const QString& tree_position, Character* pchar) {
    const QVector<QPair<QString, QString>> key_val_pairs = decoder.get_key_val_pairs(tree_position);

    for (const auto& invested_talent : key_val_pairs) {
        for (int points = 0; points < invested_talent.second.toInt(); ++points) {
            pchar->get_talents()->increment_rank(tree_position, invested_talent.first);
        }
    }
}

void CharacterLoader::apply_external_buffs(CharacterDecoder& decoder, Character* pchar) {
    const QVector<QString> buffs = decoder.get_vector_values("BUFFS");

    for (const auto& buff : buffs) {
        pchar->get_enabled_buffs()->get_general_buffs()->toggle_external_buff(buff);
    }
}

void CharacterLoader::apply_external_debuffs(CharacterDecoder& decoder, Character* pchar) {
    const QVector<QString> buffs = decoder.get_vector_values("DEBUFFS");

    for (const auto& buff : buffs) {
        pchar->get_enabled_buffs()->get_general_buffs()->toggle_external_debuff(buff);
    }
}

void CharacterLoader::apply_enchants(CharacterDecoder& decoder, Character* pchar) {
    if (pchar->get_equipment()->get_mainhand() != nullptr) {
        pchar->get_equipment()->get_mainhand()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("MH_ENCHANT", CharacterDecoder::MANDATORY)),
                                                              pchar, WeaponSlots::MAINHAND);
        pchar->get_equipment()->get_mainhand()->apply_temporary_enchant(enchant_info.get_enum_val(
                                                                            decoder.get_value("MH_TEMPORARY_ENCHANT", CharacterDecoder::MANDATORY)),
                                                                        pchar, EnchantSlot::MAINHAND);
    }

    if (pchar->get_equipment()->get_offhand() != nullptr) {
        pchar->get_equipment()->get_offhand()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("OH_ENCHANT", CharacterDecoder::MANDATORY)),
                                                             pchar, WeaponSlots::OFFHAND);
        pchar->get_equipment()->get_offhand()->apply_temporary_enchant(enchant_info.get_enum_val(
                                                                           decoder.get_value("OH_TEMPORARY_ENCHANT", CharacterDecoder::MANDATORY)),
                                                                       pchar, EnchantSlot::OFFHAND);
    }

    if (pchar->get_equipment()->get_ranged() != nullptr)
        pchar->get_equipment()->get_ranged()->apply_enchant(enchant_info.get_enum_val(
                                                                decoder.get_value("RANGED_ENCHANT", CharacterDecoder::MANDATORY)),
                                                            pchar, WeaponSlots::RANGED);

    if (pchar->get_equipment()->get_head() != nullptr)
        pchar->get_equipment()->get_head()->apply_enchant(enchant_info.get_enum_val((decoder.get_value("HEAD_ENCHANT", CharacterDecoder::MANDATORY))),
                                                          pchar);

    if (pchar->get_equipment()->get_shoulders() != nullptr)
        pchar->get_equipment()->get_shoulders()->apply_enchant(enchant_info.get_enum_val(
                                                                   decoder.get_value("SHOULDER_ENCHANT", CharacterDecoder::MANDATORY)),
                                                               pchar);

    if (pchar->get_equipment()->get_back() != nullptr)
        pchar->get_equipment()->get_back()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("BACK_ENCHANT", CharacterDecoder::MANDATORY)),
                                                          pchar);

    if (pchar->get_equipment()->get_chest() != nullptr)
        pchar->get_equipment()->get_chest()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("CHEST_ENCHANT", CharacterDecoder::MANDATORY)),
                                                           pchar);

    if (pchar->get_equipment()->get_wrist() != nullptr)
        pchar->get_equipment()->get_wrist()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("WRIST_ENCHANT", CharacterDecoder::MANDATORY)),
                                                           pchar);

    if (pchar->get_equipment()->get_gloves() != nullptr)
        pchar->get_equipment()->get_gloves()->apply_enchant(enchant_info.get_enum_val(
                                                                decoder.get_value("GLOVES_ENCHANT", CharacterDecoder::MANDATORY)),
                                                            pchar);

    if (pchar->get_equipment()->get_legs() != nullptr)
        pchar->get_equipment()->get_legs()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("LEGS_ENCHANT", CharacterDecoder::MANDATORY)),
                                                          pchar);

    if (pchar->get_equipment()->get_boots() != nullptr)
        pchar->get_equipment()->get_boots()->apply_enchant(enchant_info.get_enum_val(decoder.get_value("BOOTS_ENCHANT", CharacterDecoder::MANDATORY)),
                                                           pchar);
}

void CharacterLoader::apply_ruleset(CharacterDecoder& decoder, Character* pchar) {
    pchar->get_sim_settings()->use_ruleset(static_cast<Ruleset>(decoder.get_value("RULESET", CharacterDecoder::MANDATORY).toInt()), pchar);
}

void CharacterLoader::apply_tanking(CharacterDecoder& decoder, Character* pchar) {
    auto is_tanking = decoder.get_value("TANKING").toInt();
    pchar->set_is_tanking(is_tanking);
}

void CharacterLoader::setup_target(CharacterDecoder& decoder) {
    target->set_creature_type(decoder.get_value("TARGET_TYPE", CharacterDecoder::MANDATORY));
    target->set_lvl(decoder.get_value("TARGET_LVL", CharacterDecoder::MANDATORY).toUInt());
    target->set_base_armor(decoder.get_value("TARGET_BASE_ARMOR", CharacterDecoder::MANDATORY).toInt());
}

void CharacterLoader::select_rotation(CharacterDecoder& decoder, Character* pchar) {
    QVector<Rotation*> new_rotations;
    RotationFileReader::add_rotations(new_rotations);

    QString rotation_name = decoder.get_value("ROTATION", CharacterDecoder::MANDATORY);

    for (const auto& rotation : new_rotations) {
        if (rotation == nullptr)
            continue;

        if (pchar->class_name != rotation->get_class() || rotation->get_name() != rotation_name) {
            delete rotation;
            continue;
        }

        pchar->get_spells()->set_rotation(rotation);
    }

    if (pchar->get_spells()->get_rotation() == nullptr || pchar->get_spells()->get_rotation()->get_name() != rotation_name)
        fail("Failed to set rotation to " + rotation_name);
}

Character* CharacterLoader::setup_pchar(CharacterDecoder& decoder) {
    const QString pchar_string = decoder.get_value("CLASS", CharacterDecoder::MANDATORY);

    Character* pchar = nullptr;

    if (pchar_string == "Druid")
        pchar = new Druid(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                          decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Hunter")
        pchar = new Hunter(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                           decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Mage")
        pchar = new Mage(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                         decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Paladin")
        pchar = new Paladin(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                            decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Priest")
        pchar = new Priest(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                           decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Rogue")
        pchar = new Rogue(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                          decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Shaman")
        pchar = new Shaman(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                           decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Warlock")
        pchar = new Warlock(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                            decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());
    else if (pchar_string == "Warrior")
        pchar = new Warrior(race, equipment_db, sim_settings, raid_control, decoder.get_value("PARTY").toInt(),
                            decoder.get_value("PARTY_MEMBER", CharacterDecoder::MANDATORY).toInt());

    if (pchar == nullptr)
        delete race;

    return pchar;
}
