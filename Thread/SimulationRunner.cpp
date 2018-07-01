
#include "SimulationRunner.h"
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
#include "Target.h"
#include "CombatRoll.h"
#include "Faction.h"
#include "Talents.h"

#include "EncounterStart.h"
#include "EncounterEnd.h"

#include "ClassStatistics.h"
#include "ActiveBuffs.h"
#include "GeneralBuffs.h"

SimulationRunner::SimulationRunner(QString thread_id, QObject* parent):
    QObject(parent),
    pchar(nullptr),
    combat(nullptr),
    engine(nullptr),
    equipment(nullptr),
    faction(nullptr),
    race(nullptr),
    target(nullptr),
    seed(thread_id)
{}

SimulationRunner::~SimulationRunner() {
}

void SimulationRunner::run_sim(QString setup_string) {
    this->setup_string = setup_string;

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

    combat->set_new_seed(seed);

    pchar->get_statistics()->reset_statistics();
    engine->prepare();
    combat->drop_tables();

    // TODO: Remove hardcoded 1000 iterations for quick sim.
    for (int i = 0; i < 1000; ++i) {
        EncounterStart* start_event = new EncounterStart(pchar);
        EncounterEnd* end_event = new EncounterEnd(engine, pchar);

        engine->add_event(end_event);
        engine->add_event(start_event);
        engine->run();
    }

    engine->reset();
    // TODO: Remove hardcoded 1000 iterations 300 seconds fight for quick sim.
    float dps = float(pchar->get_statistics()->get_total_damage_dealt()) / (1000 * 300);

    delete_objects();

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
        equipment->set_mainhand(item);

    item = decoder.get_key("OFFHAND");
    if (item != "")
        equipment->set_offhand(item);

    item = decoder.get_key("RANGED");
    if (item != "")
        equipment->set_ranged(item);

    item = decoder.get_key("HEAD");
    if (item != "")
        equipment->set_head(item);

    item = decoder.get_key("NECK");
    if (item != "")
        equipment->set_neck(item);

    item = decoder.get_key("SHOULDERS");
    if (item != "")
        equipment->set_shoulders(item);

    item = decoder.get_key("BACK");
    if (item != "")
        equipment->set_back(item);

    item = decoder.get_key("CHEST");
    if (item != "")
        equipment->set_chest(item);

    item = decoder.get_key("WRIST");
    if (item != "")
        equipment->set_wrist(item);

    item = decoder.get_key("GLOVES");
    if (item != "")
        equipment->set_gloves(item);

    item = decoder.get_key("BELT");
    if (item != "")
        equipment->set_belt(item);

    item = decoder.get_key("LEGS");
    if (item != "")
        equipment->set_legs(item);

    item = decoder.get_key("BOOTS");
    if (item != "")
        equipment->set_boots(item);

    item = decoder.get_key("RING1");
    if (item != "")
        equipment->set_ring1(item);

    item = decoder.get_key("RING2");
    if (item != "")
        equipment->set_ring2(item);

    item = decoder.get_key("TRINKET1");
    if (item != "")
        equipment->set_trinket1(item);

    item = decoder.get_key("TRINKET2");
    if (item != "")
        equipment->set_trinket2(item);
}

void SimulationRunner::invest_talent_points(CharacterDecoder &decoder) {
    add_points_to_talent_tree(decoder, "LEFT");
    add_points_to_talent_tree(decoder, "MID");
    add_points_to_talent_tree(decoder, "RIGHT");
}

void SimulationRunner::add_points_to_talent_tree(CharacterDecoder &decoder, const QString& tree_position) {
    QVector<QPair<QString, QString>> invested_talents = decoder.get_key_val_pairs(tree_position);

    for (int i = 0; i < invested_talents.size(); ++i) {
        for (int points = 0; points < invested_talents[i].second.toInt(); ++points) {
            pchar->get_talents()->increment_rank(tree_position, invested_talents[i].first);
        }
    }
}

void SimulationRunner::apply_external_buffs(CharacterDecoder& decoder) {
    QVector<QPair<QString, QString>> buffs = decoder.get_key_val_pairs("BUFFS");

    for (int i = 0; i < buffs.size(); ++i) {
        pchar->get_active_buffs()->get_general_buffs()->toggle_external_buff(buffs[i].first);
    }
}

void SimulationRunner::setup_target(CharacterDecoder& decoder) {
    pchar->get_combat_roll()->get_target()->set_creature_type(decoder.get_key("TARGET_TYPE"));
    pchar->get_combat_roll()->get_target()->set_lvl(decoder.get_key("TARGET_LVL").toInt());
    pchar->get_combat_roll()->get_target()->set_armor(decoder.get_key("TARGET_ARMOR").toInt());
}

void SimulationRunner::exit_thread(QString err) {
    emit error(seed, err);
    emit finished();
}

void SimulationRunner::setup_pchar(CharacterDecoder& decoder) {
    if (engine == nullptr)
        engine = new Engine();
    if (equipment == nullptr)
        equipment = new Equipment();
    if (target == nullptr)
        target = new Target(63);
    if (combat == nullptr)
        combat = new CombatRoll(target);
    if (faction == nullptr)
        faction = new Faction();

    QString pchar_string = decoder.get_class();

    if (pchar_string == "Druid")
        pchar = dynamic_cast<Character*>(new Druid(race, engine, equipment, combat, faction));
    if (pchar_string == "Hunter")
        pchar = dynamic_cast<Character*>(new Hunter(race, engine, equipment, combat, faction));
    if (pchar_string == "Mage")
        pchar = dynamic_cast<Character*>(new Mage(race, engine, equipment, combat, faction));
    if (pchar_string == "Paladin")
        pchar = dynamic_cast<Character*>(new Paladin(race, engine, equipment, combat, faction));
    if (pchar_string == "Priest")
        pchar = dynamic_cast<Character*>(new Priest(race, engine, equipment, combat, faction));
    if (pchar_string == "Rogue")
        pchar = dynamic_cast<Character*>(new Rogue(race, engine, equipment, combat, faction));
    if (pchar_string == "Shaman")
        pchar = dynamic_cast<Character*>(new Shaman(race, engine, equipment, combat, faction));
    if (pchar_string == "Warlock")
        pchar = dynamic_cast<Character*>(new Warlock(race, engine, equipment, combat, faction));
    if (pchar_string == "Warrior")
        pchar = dynamic_cast<Character*>(new Warrior(race, engine, equipment, combat, faction));

    if (pchar == nullptr)
        delete_objects();
    else
        equipment->set_character(pchar);
}

void SimulationRunner::delete_objects() {
    if (pchar != nullptr) {
        equipment->set_character(nullptr);
        delete pchar;
    }

    if (race != nullptr)
        delete race;
}
