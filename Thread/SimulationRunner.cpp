
#include "SimulationRunner.h"

#include <utility>

#include "CharacterEncoder.h"
#include "CharacterDecoder.h"

#include "Dwarf.h"
#include "Gnome.h"
#include "Human.h"
#include "NightElf.h"
#include "Orc.h"
#include "Tauren.h"
#include "Troll.h"
#include "Undead.h"

#include "Druid.h"
#include "Hunter.h"
#include "Mage.h"
#include "Paladin.h"
#include "Priest.h"
#include "Rogue.h"
#include "Shaman.h"
#include "Warlock.h"
#include "Warrior.h"

#include "Engine.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Target.h"
#include "CombatRoll.h"
#include "Faction.h"
#include "Rotation.h"
#include "RotationFileReader.h"
#include "Talents.h"

#include "EncounterStart.h"
#include "EncounterEnd.h"

#include "ClassStatistics.h"
#include "ActiveBuffs.h"
#include "GeneralBuffs.h"
#include "SimControl.h"
#include "SimSettings.h"
#include "NumberCruncher.h"
#include "Weapon.h"
#include "Item.h"

SimulationRunner::SimulationRunner(unsigned thread_id, EquipmentDb* equipment_db, SimSettings *sim_settings, NumberCruncher* scaler, QObject* parent):
    QObject(parent),
    pchar(nullptr),
    equipment_db(equipment_db),
    race(nullptr),
    rotation(nullptr),
    global_sim_settings(sim_settings),
    local_sim_settings(nullptr),
    scaler(scaler),
    full_sim(false),
    thread_id(thread_id)
{}

SimulationRunner::~SimulationRunner() {
}

void SimulationRunner::run_sim(unsigned thread_id, QString setup_string, bool full_sim) {
    if (this->thread_id != thread_id) {
        emit finished();
        return;
    }

    this->setup_string = setup_string;
    this->full_sim = full_sim;

    CharacterDecoder decoder;
    decoder.initialize(this->setup_string);

    setup_race(decoder);
    if (race == nullptr)
        return exit_thread("Race nullptr: " + decoder.get_race());

    setup_pchar(decoder);
    if (pchar == nullptr)
        return exit_thread("Pchar nullptr: " + decoder.get_class());

    equip_gear(decoder);
    invest_talent_points(decoder);
    apply_external_buffs(decoder);
    setup_target(decoder);
    select_rotation(decoder);
    apply_enchants(decoder);

    CharacterEncoder encoder(pchar);
    if (encoder.get_current_setup_string() != this->setup_string)
        return exit_thread("Mismatch between setup strings after setup: dumped setup string: " + encoder.get_current_setup_string());

    pchar->get_combat_roll()->set_new_seed(this->thread_id);

    if (full_sim)
        SimControl(local_sim_settings, scaler).run_full_sim(pchar);
    else
        SimControl(local_sim_settings, scaler).run_quick_sim(pchar);

    double dps = double(pchar->get_statistics()->get_total_damage_dealt()) / (local_sim_settings->get_combat_iterations() * local_sim_settings->get_combat_length());

    delete pchar;
    delete race;
    delete rotation;
    delete local_sim_settings;

    emit result(QString::number(thread_id), dps);
    emit finished();
}

void SimulationRunner::setup_race(CharacterDecoder& decoder) {
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

void SimulationRunner::equip_gear(CharacterDecoder& decoder) {
    QString item = decoder.get_key("MAINHAND");
    if (item != "")
        pchar->get_equipment()->set_mainhand(item);

    item = decoder.get_key("OFFHAND");
    if (item != "")
        pchar->get_equipment()->set_offhand(item);

    item = decoder.get_key("RANGED");
    if (item != "")
        pchar->get_equipment()->set_ranged(item);

    item = decoder.get_key("HEAD");
    if (item != "")
        pchar->get_equipment()->set_head(item);

    item = decoder.get_key("NECK");
    if (item != "")
        pchar->get_equipment()->set_neck(item);

    item = decoder.get_key("SHOULDERS");
    if (item != "")
        pchar->get_equipment()->set_shoulders(item);

    item = decoder.get_key("BACK");
    if (item != "")
        pchar->get_equipment()->set_back(item);

    item = decoder.get_key("CHEST");
    if (item != "")
        pchar->get_equipment()->set_chest(item);

    item = decoder.get_key("WRIST");
    if (item != "")
        pchar->get_equipment()->set_wrist(item);

    item = decoder.get_key("GLOVES");
    if (item != "")
        pchar->get_equipment()->set_gloves(item);

    item = decoder.get_key("BELT");
    if (item != "")
        pchar->get_equipment()->set_belt(item);

    item = decoder.get_key("LEGS");
    if (item != "")
        pchar->get_equipment()->set_legs(item);

    item = decoder.get_key("BOOTS");
    if (item != "")
        pchar->get_equipment()->set_boots(item);

    item = decoder.get_key("RING1");
    if (item != "")
        pchar->get_equipment()->set_ring1(item);

    item = decoder.get_key("RING2");
    if (item != "")
        pchar->get_equipment()->set_ring2(item);

    item = decoder.get_key("TRINKET1");
    if (item != "")
        pchar->get_equipment()->set_trinket1(item);

    item = decoder.get_key("TRINKET2");
    if (item != "")
        pchar->get_equipment()->set_trinket2(item);
}

void SimulationRunner::invest_talent_points(CharacterDecoder &decoder) {
    add_points_to_talent_tree(decoder, "LEFT");
    add_points_to_talent_tree(decoder, "MID");
    add_points_to_talent_tree(decoder, "RIGHT");
}

void SimulationRunner::add_points_to_talent_tree(CharacterDecoder &decoder, const QString& tree_position) {
    QVector<QPair<QString, QString>> invested_talents = decoder.get_key_val_pairs(tree_position);

    for (auto & invested_talent : invested_talents) {
        for (int points = 0; points < invested_talent.second.toInt(); ++points) {
            pchar->get_talents()->increment_rank(tree_position, invested_talent.first);
        }
    }
}

void SimulationRunner::apply_external_buffs(CharacterDecoder& decoder) {
    QVector<QPair<QString, QString>> buffs = decoder.get_key_val_pairs("BUFFS");

    for (auto & buff : buffs) {
        pchar->get_active_buffs()->get_general_buffs()->toggle_external_buff(buff.first);
    }
}

void SimulationRunner::apply_enchants(CharacterDecoder& decoder) {
    if (pchar->get_equipment()->get_mainhand() != nullptr) {
        pchar->get_equipment()->get_mainhand()->apply_enchant(get_enum_val(decoder.get_key("MH_ENCHANT")), pchar, true);
        pchar->get_equipment()->get_mainhand()->apply_temporary_enchant(get_enum_val(decoder.get_key("MH_TEMPORARY_ENCHANT")), pchar, true);
    }

    if (pchar->get_equipment()->get_offhand() != nullptr) {
        pchar->get_equipment()->get_offhand()->apply_enchant(get_enum_val(decoder.get_key("OH_ENCHANT")), pchar, false);
        pchar->get_equipment()->get_offhand()->apply_temporary_enchant(get_enum_val(decoder.get_key("OH_TEMPORARY_ENCHANT")), pchar, false);
    }

    if (pchar->get_equipment()->get_head() != nullptr)
        pchar->get_equipment()->get_head()->apply_enchant(get_enum_val(decoder.get_key("HEAD_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_shoulders() != nullptr)
        pchar->get_equipment()->get_shoulders()->apply_enchant(get_enum_val(decoder.get_key("SHOULDER_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_back() != nullptr)
        pchar->get_equipment()->get_back()->apply_enchant(get_enum_val(decoder.get_key("BACK_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_chest() != nullptr)
        pchar->get_equipment()->get_chest()->apply_enchant(get_enum_val(decoder.get_key("CHEST_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_wrist() != nullptr)
        pchar->get_equipment()->get_wrist()->apply_enchant(get_enum_val(decoder.get_key("WRIST_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_gloves() != nullptr)
        pchar->get_equipment()->get_gloves()->apply_enchant(get_enum_val(decoder.get_key("GLOVES_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_legs() != nullptr)
        pchar->get_equipment()->get_legs()->apply_enchant(get_enum_val(decoder.get_key("LEGS_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_boots() != nullptr)
        pchar->get_equipment()->get_boots()->apply_enchant(get_enum_val(decoder.get_key("BOOTS_ENCHANT")), pchar);

    if (pchar->get_equipment()->get_ranged())
        pchar->get_equipment()->get_ranged()->apply_enchant(get_enum_val(decoder.get_key("RANGED_ENCHANT")), pchar);
}

void SimulationRunner::setup_target(CharacterDecoder& decoder) {
    pchar->get_target()->set_creature_type(decoder.get_key("TARGET_TYPE"));
    pchar->get_target()->set_lvl(decoder.get_key("TARGET_LVL").toInt());
    pchar->get_target()->set_armor(decoder.get_key("TARGET_ARMOR").toInt());
}

void SimulationRunner::select_rotation(CharacterDecoder& decoder) {
    RotationFileReader rotation_file_reader;
    QVector<Rotation*> new_rotations;
    rotation_file_reader.add_rotations(new_rotations);

    QString rotation_name = decoder.get_key("ROTATION");

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
        exit_thread("Failed to set rotation to " + rotation_name);
}

void SimulationRunner::exit_thread(QString err) {
    delete pchar;
    delete race;
    delete rotation;
    delete local_sim_settings;
    emit error(QString::number(thread_id), std::move(err));
    emit finished();
}

void SimulationRunner::setup_pchar(CharacterDecoder& decoder) {
    this->local_sim_settings = new SimSettings();
    local_sim_settings->set_combat_iterations(global_sim_settings->get_combat_iterations());
    local_sim_settings->set_combat_length(global_sim_settings->get_combat_length());

    QString pchar_string = decoder.get_class();

    if (pchar_string == "Druid")
        pchar = dynamic_cast<Character*>(new Druid(race, equipment_db, local_sim_settings));
    if (pchar_string == "Hunter")
        pchar = dynamic_cast<Character*>(new Hunter(race, equipment_db, local_sim_settings));
    if (pchar_string == "Mage")
        pchar = dynamic_cast<Character*>(new Mage(race, equipment_db, local_sim_settings));
    if (pchar_string == "Paladin")
        pchar = dynamic_cast<Character*>(new Paladin(race, equipment_db, local_sim_settings));
    if (pchar_string == "Priest")
        pchar = dynamic_cast<Character*>(new Priest(race, equipment_db, local_sim_settings));
    if (pchar_string == "Rogue")
        pchar = dynamic_cast<Character*>(new Rogue(race, equipment_db, local_sim_settings));
    if (pchar_string == "Shaman")
        pchar = dynamic_cast<Character*>(new Shaman(race, equipment_db, local_sim_settings));
    if (pchar_string == "Warlock")
        pchar = dynamic_cast<Character*>(new Warlock(race, equipment_db, local_sim_settings));
    if (pchar_string == "Warrior")
        pchar = dynamic_cast<Character*>(new Warrior(race, equipment_db, local_sim_settings));

    if (pchar == nullptr)
        delete race;
}

EnchantName::Name SimulationRunner::get_enum_val(QString enum_val_as_string) {
    return static_cast<EnchantName::Name>(enum_val_as_string.toInt());
}
