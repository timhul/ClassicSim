
#include "GUIControl.h"

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

#include "Statistics.h"

#include "EncounterStart.h"
#include "EncounterEnd.h"

#include "Mainhand.h"
#include "Offhand.h"

#include <QDebug>

GUIControl::GUIControl(QObject* parent) :
    QObject(parent),
    last_quick_sim_result(0.0)
{
    races.insert("DWARF", new Dwarf());
    races.insert("GNOME", new Gnome());
    races.insert("HUMAN", new Human());
    races.insert("NIGHTELF", new NightElf());
    races.insert("ORC", new Orc());
    races.insert("TAUREN", new Tauren());
    races.insert("TROLL", new Troll());
    races.insert("UNDEAD", new Undead());

    engine = new Engine();
    equipment = new Equipment();
    Random* mh_dmg_range = new Random(80, 150);
    Mainhand* mainhand = new Mainhand("Frostbite", mh_dmg_range, 0, 80, 150, 2.7, 0.0);
    equipment->set_mainhand(mainhand);
    Random* oh_dmg_range = new Random(80, 150);
    Offhand* offhand = new Offhand("Frostbite", oh_dmg_range, 0, 80, 150, 2.7, 0.0);
    equipment->set_offhand(offhand);
    target = new Target(63);
    combat = new CombatRoll(target);

    chars.insert("DRUID", dynamic_cast<Character*>(new Druid(races["NIGHTELF"], engine, equipment, combat)));
    chars.insert("HUNTER", dynamic_cast<Character*>(new Hunter(races["DWARF"], engine, equipment, combat)));
    chars.insert("MAGE", dynamic_cast<Character*>(new Mage(races["GNOME"], engine, equipment, combat)));
    chars.insert("PALADIN", dynamic_cast<Character*>(new Paladin(races["HUMAN"], engine, equipment, combat)));
    chars.insert("PRIEST", dynamic_cast<Character*>(new Priest(races["UNDEAD"], engine, equipment, combat)));
    chars.insert("ROGUE", dynamic_cast<Character*>(new Rogue(races["ORC"], engine, equipment, combat)));
    chars.insert("SHAMAN", dynamic_cast<Character*>(new Shaman(races["TAUREN"], engine, equipment, combat)));
    chars.insert("WARLOCK", dynamic_cast<Character*>(new Warlock(races["TROLL"], engine, equipment, combat)));
    chars.insert("WARRIOR", dynamic_cast<Character*>(new Warrior(races["ORC"], engine, equipment, combat)));

    current_char = chars["WARRIOR"];
}

GUIControl::~GUIControl() {
    for (auto it : chars.keys()) {
        delete chars.value(it);
    }

    chars.clear();

    for (auto it : races.keys()) {
        delete races.value(it);
    }

    races.clear();

    delete engine;
    delete equipment;
    delete target;
    delete combat;
}

QString GUIControl::getLeftBackgroundImage() const {
    return current_char->get_talents()->get_background_image("LEFT");
}

QString GUIControl::getMidBackgroundImage() const {
    return current_char->get_talents()->get_background_image("MID");
}

QString GUIControl::getRightBackgroundImage() const {
    return current_char->get_talents()->get_background_image("RIGHT");
}

QString GUIControl::getIcon(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_icon(tree_position, talent_position);
}

bool GUIControl::showPosition(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->show_position(tree_position, talent_position);
}

bool GUIControl::showBottomArrow(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->show_bottom_arrow(tree_position, talent_position);
}
bool GUIControl::showRightArrow(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->show_right_arrow(tree_position, talent_position);
}

QString GUIControl::getBottomArrow(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_bottom_arrow(tree_position, talent_position);
}

QString GUIControl::getRightArrow(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_right_arrow(tree_position, talent_position);
}

bool GUIControl::bottomChildAvailable(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->bottom_child_available(tree_position, talent_position);
}

bool GUIControl::bottomChildActive(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->bottom_child_active(tree_position, talent_position);
}

bool GUIControl::rightChildAvailable(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->right_child_available(tree_position, talent_position);
}

bool GUIControl::rightChildActive(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->right_child_active(tree_position, talent_position);
}

bool GUIControl::isActive(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->is_active(tree_position, talent_position);
}

bool GUIControl::isAvailable(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->is_available(tree_position, talent_position);
}

bool GUIControl::isMaxed(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->is_maxed(tree_position, talent_position);
}

bool GUIControl::hasTalentPointsRemaining() const {
    return current_char->get_talents()->has_talent_points_remaining();
}

QString GUIControl::getRank(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_rank(tree_position, talent_position);
}

QString GUIControl::getMaxRank(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_max_rank(tree_position, talent_position);
}

void GUIControl::incrementRank(const QString tree_position, const QString talent_position) {
    current_char->get_talents()->increment_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
    Q_EMIT statsChanged();
}

void GUIControl::decrementRank(const QString tree_position, const QString talent_position) {
    current_char->get_talents()->decrement_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
    Q_EMIT statsChanged();
}

QString GUIControl::getRequirements(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_requirements(tree_position, talent_position);
}

QString GUIControl::getCurrentRankDescription(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_current_rank_description(tree_position, talent_position);
}

QString GUIControl::getNextRankDescription(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_next_rank_description(tree_position, talent_position);
}

int GUIControl::getTreePoints(const QString tree_position) const {
    return current_char->get_talents()->get_tree_points(tree_position);
}

QString GUIControl::getTreeName(const QString tree_position) const {
    return current_char->get_talents()->get_tree_name(tree_position);
}

QString GUIControl::getTalentName(const QString tree_position, const QString talent_position) const {
    return current_char->get_talents()->get_talent_name(tree_position, talent_position);
}

void GUIControl::maxRank(const QString tree_position, const QString talent_position) {
    current_char->get_talents()->increase_to_max_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
    Q_EMIT statsChanged();
}

void GUIControl::minRank(const QString tree_position, const QString talent_position) {
    current_char->get_talents()->decrease_to_min_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
    Q_EMIT statsChanged();
}

void GUIControl::clearTree(const QString tree_position) {
    current_char->get_talents()->clear_tree(tree_position);
    Q_EMIT talentsUpdated();
    Q_EMIT statsChanged();
}

void GUIControl::setTalentSetup(const int talent_index) {
    current_char->get_talents()->set_current_index(talent_index);
    Q_EMIT talentsUpdated();
    Q_EMIT statsChanged();
}

int GUIControl::get_talent_points_remaining() const {
    return current_char->get_talents()->get_talent_points_remaining();
}

QString GUIControl::get_class_color() const {
    return current_char->get_class_color();
}

QString GUIControl::get_class_name() const {
    return current_char->get_name();
}

int GUIControl::get_strength() const {
    return current_char->get_strength();
}

int GUIControl::get_agility() const {
    return current_char->get_agility();
}

int GUIControl::get_stamina() const {
    return current_char->get_stamina();
}

int GUIControl::get_intellect() const {
    return current_char->get_intellect();
}

int GUIControl::get_spirit() const {
    return current_char->get_spirit();
}

QString GUIControl::get_crit_chance() const {
    return QString::number(current_char->get_crit_chance() * 100, 'f', 2);
}

QString GUIControl::get_hit_chance() const {
    return QString::number(current_char->get_hit_chance() * 100, 'f', 2);
}

void GUIControl::run_quick_sim() {
    engine->prepare();
    // TODO: Remove hardcoded 1000 iterations for quick sim.
    for (int i = 0; i < 1000; ++i) {
        EncounterStart* start_event = new EncounterStart(current_char);
        EncounterEnd* end_event = new EncounterEnd(engine, current_char);

        engine->add_event(end_event);
        engine->add_event(start_event);
        engine->run();
    }

    engine->dump();
    engine->reset();
    // TODO: Remove hardcoded 1000 iterations 300 seconds fight for quick sim.
    float previous = last_quick_sim_result;
    last_quick_sim_result = float(engine->get_statistics()->get_total_damage()) / (1000 * 300);

    float delta = ((last_quick_sim_result - previous) / previous);
    QString change = delta > 0 ? "+" : "";
    change += QString::number(((last_quick_sim_result - previous) / previous) * 100, 'f', 1) + "%";

    QString dps = QString::number(last_quick_sim_result, 'f', 2);
    qDebug() << "Total DPS: " << dps;
    quickSimChanged(dps, change, delta > 0);
}

void GUIControl::runQuickSim() {
    run_quick_sim();
}
