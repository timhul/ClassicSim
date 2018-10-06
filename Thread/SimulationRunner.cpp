
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
#include "Talents.h"

#include "EncounterStart.h"
#include "EncounterEnd.h"

#include "ClassStatistics.h"
#include "ActiveBuffs.h"
#include "GeneralBuffs.h"

SimulationRunner::SimulationRunner(EquipmentDb* equipment_db, QString thread_id, QObject* parent):
    QObject(parent),
    pchar(nullptr),
    equipment_db(equipment_db),
    race(nullptr),
    seed(std::move(thread_id))
{}

SimulationRunner::~SimulationRunner() {
    delete equipment_db;
}

void SimulationRunner::run_sim(QString setup_string) {
    this->setup_string = std::move(setup_string);

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

    CharacterEncoder encoder(pchar);
    if (encoder.get_current_setup_string() != this->setup_string)
        return exit_thread("Mismatch between setup strings after setup: dumped setup string: " + encoder.get_current_setup_string());

    pchar->get_combat_roll()->set_new_seed(seed);

    pchar->get_statistics()->reset_statistics();
    pchar->get_engine()->prepare();
    pchar->get_combat_roll()->drop_tables();

    // CSIM-59: Remove hardcoded 1000 iterations for quick sim.
    for (int i = 0; i < 1000; ++i) {
        auto* start_event = new EncounterStart(pchar);
        auto* end_event = new EncounterEnd(pchar->get_engine(), pchar);

        pchar->get_engine()->add_event(end_event);
        pchar->get_engine()->add_event(start_event);
        pchar->get_engine()->run();
    }

    pchar->get_engine()->reset();
    // CSIM-59: Remove hardcoded 1000 iterations 300 seconds fight for quick sim.
    double dps = double(pchar->get_statistics()->get_total_damage_dealt()) / (1000 * 300);

    delete pchar;
    delete race;

    emit result(seed, dps);
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

void SimulationRunner::setup_target(CharacterDecoder& decoder) {
    pchar->get_combat_roll()->get_target()->set_creature_type(decoder.get_key("TARGET_TYPE"));
    pchar->get_combat_roll()->get_target()->set_lvl(decoder.get_key("TARGET_LVL").toInt());
    pchar->get_combat_roll()->get_target()->set_armor(decoder.get_key("TARGET_ARMOR").toInt());
}

void SimulationRunner::exit_thread(QString err) {
    emit error(seed, std::move(err));
    emit finished();
}

void SimulationRunner::setup_pchar(CharacterDecoder& decoder) {
    QString pchar_string = decoder.get_class();

    if (pchar_string == "Druid")
        pchar = dynamic_cast<Character*>(new Druid(race, equipment_db));
    if (pchar_string == "Hunter")
        pchar = dynamic_cast<Character*>(new Hunter(race, equipment_db));
    if (pchar_string == "Mage")
        pchar = dynamic_cast<Character*>(new Mage(race, equipment_db));
    if (pchar_string == "Paladin")
        pchar = dynamic_cast<Character*>(new Paladin(race, equipment_db));
    if (pchar_string == "Priest")
        pchar = dynamic_cast<Character*>(new Priest(race, equipment_db));
    if (pchar_string == "Rogue")
        pchar = dynamic_cast<Character*>(new Rogue(race, equipment_db));
    if (pchar_string == "Shaman")
        pchar = dynamic_cast<Character*>(new Shaman(race, equipment_db));
    if (pchar_string == "Warlock")
        pchar = dynamic_cast<Character*>(new Warlock(race, equipment_db));
    if (pchar_string == "Warrior")
        pchar = dynamic_cast<Character*>(new Warrior(race, equipment_db));

    if (pchar == nullptr)
        delete race;
}
