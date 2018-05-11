
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

#include "Spells.h"

#include "Statistics.h"

#include "EncounterStart.h"
#include "EncounterEnd.h"

#include "WeaponModel.h"
#include "EquipmentDb.h"

#include "CharacterStats.h"
#include "ClassStatistics.h"

#include <QDebug>

GUIControl::GUIControl(QObject* parent) :
    QObject(parent),
    last_quick_sim_result(0.0)
{
    QObject::connect(this, SIGNAL(startQuickSim()), this, SLOT(run_quick_sim()));

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
    target = new Target(63);
    combat = new CombatRoll(target);

    chars.insert("Druid", dynamic_cast<Character*>(new Druid(races["NIGHTELF"], engine, equipment, combat)));
    chars.insert("Hunter", dynamic_cast<Character*>(new Hunter(races["DWARF"], engine, equipment, combat)));
    chars.insert("Mage", dynamic_cast<Character*>(new Mage(races["GNOME"], engine, equipment, combat)));
    chars.insert("Paladin", dynamic_cast<Character*>(new Paladin(races["HUMAN"], engine, equipment, combat)));
    chars.insert("Priest", dynamic_cast<Character*>(new Priest(races["UNDEAD"], engine, equipment, combat)));
    chars.insert("Rogue", dynamic_cast<Character*>(new Rogue(races["ORC"], engine, equipment, combat)));
    chars.insert("Shaman", dynamic_cast<Character*>(new Shaman(races["TAUREN"], engine, equipment, combat)));
    chars.insert("Warlock", dynamic_cast<Character*>(new Warlock(races["TROLL"], engine, equipment, combat)));
    chars.insert("Warrior", dynamic_cast<Character*>(new Warrior(races["ORC"], engine, equipment, combat)));

    current_char = chars["Warrior"];

    item_model = new ItemModel(equipment->get_db());
    item_model->addItems(equipment->get_db());

    weapon_model = new WeaponModel(equipment->get_db());
    weapon_model->addWeapons(equipment->get_db());
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
    delete item_model;
    delete weapon_model;
}

void GUIControl::selectClass(const QString class_name) {
    if (!chars.contains(class_name)) {
        qDebug() << QString("Class %1 not found in char list!").arg(class_name);
        return;
    }

    if (class_name != "Warrior") {
        qDebug() << QString("Class %1 not implemented").arg(class_name);
        return;
    }

    current_char = chars[class_name];
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

bool GUIControl::get_faction() const {
    // TODO: Remove hardcoded faction
    // alliance = false, horde = true
    return true;
}

int GUIControl::get_strength() const {
    return current_char->get_stats()->get_strength();
}

int GUIControl::get_agility() const {
    return current_char->get_stats()->get_agility();
}

int GUIControl::get_stamina() const {
    return current_char->get_stats()->get_stamina();
}

int GUIControl::get_intellect() const {
    return current_char->get_stats()->get_intellect();
}

int GUIControl::get_spirit() const {
    return current_char->get_stats()->get_spirit();
}

QString GUIControl::get_crit_chance() const {
    return QString::number(current_char->get_stats()->get_crit_chance() * 100, 'f', 2);
}

QString GUIControl::get_hit_chance() const {
    return QString::number(current_char->get_stats()->get_hit_chance() * 100, 'f', 2);
}

int GUIControl::get_attack_power() const {
    return current_char->get_stats()->get_melee_ap();
}

int GUIControl::get_mainhand_wpn_skill() const {
    return current_char->get_mh_wpn_skill();
}

int GUIControl::get_offhand_wpn_skill() const {
    return current_char->get_oh_wpn_skill();
}

ItemModel* GUIControl::get_item_model() const {
    return this->item_model;
}

WeaponModel* GUIControl::get_weapon_model() const {
    return this->weapon_model;
}

int GUIControl::getNumStatisticsRows() const {
    return current_char->get_statistics()->getNumStatisticsRows();
}

QVariantList GUIControl::getChartInfo(const int index) const {
    return current_char->get_statistics()->getChartInfo(index);
}

QVariantList GUIControl::getTableInfo(const int index) const {
    return current_char->get_statistics()->getTableInfo(index);
}

QString GUIControl::getEntryIcon(const int index) const {
    return current_char->get_statistics()->getEntryIcon(index);
}

void GUIControl::run_quick_sim() {
    current_char->dump();
    engine->prepare();
    combat->drop_tables();
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
    current_char->dump();
    statisticsReady();
}

void GUIControl::runQuickSim() {
    statisticsCleared();
    startQuickSim();
}

QString GUIControl::get_mainhand_icon() const {
    if (equipment->get_mainhand() != nullptr)
        return "Assets/items/" + equipment->get_mainhand()->get_value("icon");
    return "";
}

QString GUIControl::get_offhand_icon() const {
    if (equipment->get_offhand() != nullptr)
        return "Assets/items/" + equipment->get_offhand()->get_value("icon");
    return "";
}

QString GUIControl::get_ranged_icon() const {
    if (equipment->get_ranged() != nullptr)
        return "Assets/items/" + equipment->get_ranged()->get_value("icon");
    return "";
}

QString GUIControl::get_head_icon() const {
    if (equipment->get_head() != nullptr)
        return "Assets/items/" + equipment->get_head()->get_value("icon");
    return "";
}

QString GUIControl::get_neck_icon() const {
    if (equipment->get_neck() != nullptr)
        return "Assets/items/" + equipment->get_neck()->get_value("icon");
    return "";
}

QString GUIControl::get_shoulders_icon() const {
    if (equipment->get_shoulders() != nullptr)
        return "Assets/items/" + equipment->get_shoulders()->get_value("icon");
    return "";
}

QString GUIControl::get_back_icon() const {
    if (equipment->get_back() != nullptr)
        return "Assets/items/" + equipment->get_back()->get_value("icon");
    return "";
}

QString GUIControl::get_chest_icon() const {
    if (equipment->get_chest() != nullptr)
        return "Assets/items/" + equipment->get_chest()->get_value("icon");
    return "";
}

QString GUIControl::get_wrist_icon() const {
    if (equipment->get_wrist() != nullptr)
        return "Assets/items/" + equipment->get_wrist()->get_value("icon");
    return "";
}

QString GUIControl::get_gloves_icon() const {
    if (equipment->get_gloves() != nullptr)
        return "Assets/items/" + equipment->get_gloves()->get_value("icon");
    return "";
}

QString GUIControl::get_belt_icon() const {
    if (equipment->get_belt() != nullptr)
        return "Assets/items/" + equipment->get_belt()->get_value("icon");
    return "";
}

QString GUIControl::get_legs_icon() const {
    if (equipment->get_legs() != nullptr)
        return "Assets/items/" + equipment->get_legs()->get_value("icon");
    return "";
}

QString GUIControl::get_boots_icon() const {
    if (equipment->get_boots() != nullptr)
        return "Assets/items/" + equipment->get_boots()->get_value("icon");
    return "";
}

QString GUIControl::get_ring1_icon() const {
    if (equipment->get_ring1() != nullptr)
        return "Assets/items/" + equipment->get_ring1()->get_value("icon");
    return "";
}

QString GUIControl::get_ring2_icon() const {
    if (equipment->get_ring2() != nullptr)
        return "Assets/items/" + equipment->get_ring2()->get_value("icon");
    return "";
}

QString GUIControl::get_trinket1_icon() const {
    if (equipment->get_trinket1() != nullptr)
        return "Assets/items/" + equipment->get_trinket1()->get_value("icon");
    return "";
}

QString GUIControl::get_trinket2_icon() const {
    if (equipment->get_trinket2() != nullptr)
        return "Assets/items/" + equipment->get_trinket2()->get_value("icon");
    return "";
}

void GUIControl::selectSlot(QString slot_string) {
    int slot = get_slot_int(slot_string);

    if (slot == -1)
        return;

    switch (slot) {
    case ItemSlots::MAINHAND:
    case ItemSlots::OFFHAND:
    case ItemSlots::RANGED:
        weapon_model->setSlot(slot);
        return;
    }

    item_model->setSlot(slot);
}

void GUIControl::setSlot(QString slot_string, QString item) {
    // TODO: Replace with switch on slot as int.
    if (slot_string == "MAINHAND")
        equipment->set_mainhand(item);
    if (slot_string == "OFFHAND")
        equipment->set_offhand(item);
    if (slot_string == "RANGED")
        equipment->set_ranged(item);
    if (slot_string == "HEAD")
        equipment->set_head(item);
    if (slot_string == "NECK")
        equipment->set_neck(item);
    if (slot_string == "SHOULDERS")
        equipment->set_shoulders(item);
    if (slot_string == "BACK")
        equipment->set_back(item);
    if (slot_string == "CHEST")
        equipment->set_chest(item);
    if (slot_string == "WRIST")
        equipment->set_wrist(item);
    if (slot_string == "GLOVES")
        equipment->set_gloves(item);
    if (slot_string == "BELT")
        equipment->set_belt(item);
    if (slot_string == "LEGS")
        equipment->set_legs(item);
    if (slot_string == "BOOTS")
        equipment->set_boots(item);
    if (slot_string == "RING1")
        equipment->set_ring1(item);
    if (slot_string == "RING2")
        equipment->set_ring2(item);
    if (slot_string == "TRINKET1")
        equipment->set_trinket1(item);
    if (slot_string == "TRINKET2")
        equipment->set_trinket2(item);

    equipmentChanged();
    statsChanged();
}

void GUIControl::clearSlot(QString slot_string) {
    if (slot_string == "MAINHAND")
        equipment->clear_mainhand();
    if (slot_string == "OFFHAND")
        equipment->clear_offhand();
    if (slot_string == "RANGED")
        equipment->clear_ranged();
    if (slot_string == "HEAD")
        equipment->clear_head();
    if (slot_string == "NECK")
        equipment->clear_neck();
    if (slot_string == "SHOULDERS")
        equipment->clear_shoulders();
    if (slot_string == "BACK")
        equipment->clear_back();
    if (slot_string == "CHEST")
        equipment->clear_chest();
    if (slot_string == "WRIST")
        equipment->clear_wrist();
    if (slot_string == "GLOVES")
        equipment->clear_gloves();
    if (slot_string == "BELT")
        equipment->clear_belt();
    if (slot_string == "LEGS")
        equipment->clear_legs();
    if (slot_string == "BOOTS")
        equipment->clear_boots();
    if (slot_string == "RING1")
        equipment->clear_ring1();
    if (slot_string == "RING2")
        equipment->clear_ring2();
    if (slot_string == "TRINKET1")
        equipment->clear_trinket1();
    if (slot_string == "TRINKET2")
        equipment->clear_trinket2();

    equipmentChanged();
    statsChanged();
}

void GUIControl::setPatch(QString patch) {
    weapon_model->set_patch(patch);
    item_model->set_patch(patch);
}

QVariantList GUIControl::getTooltip(const QString &slot_string) {
    Item* item = nullptr;

    if (slot_string == "MAINHAND")
        item = equipment->get_mainhand();
    if (slot_string == "OFFHAND")
        item = equipment->get_offhand();
    if (slot_string == "RANGED")
        item = equipment->get_ranged();
    if (slot_string == "HEAD")
        item = equipment->get_head();
    if (slot_string == "NECK")
        item = equipment->get_neck();
    if (slot_string == "SHOULDERS")
        item = equipment->get_shoulders();
    if (slot_string == "BACK")
        item = equipment->get_back();
    if (slot_string == "CHEST")
        item = equipment->get_chest();
    if (slot_string == "WRIST")
        item = equipment->get_wrist();
    if (slot_string == "GLOVES")
        item = equipment->get_gloves();
    if (slot_string == "BELT")
        item = equipment->get_belt();
    if (slot_string == "LEGS")
        item = equipment->get_legs();
    if (slot_string == "BOOTS")
        item = equipment->get_boots();
    if (slot_string == "RING1")
        item = equipment->get_ring1();
    if (slot_string == "RING2")
        item = equipment->get_ring2();
    if (slot_string == "TRINKET1")
        item = equipment->get_trinket1();
    if (slot_string == "TRINKET2")
        item = equipment->get_trinket2();

    if (item == nullptr)
        return QVariantList();

    QString boe_string = item->get_value("boe") == "yes" ? "Binds when equipped" :
                                                          "Binds when picked up";
    QString unique = item->get_value("unique") == "yes" ? "Unique" :
                                                          "";

    QString slot = item->get_value("slot");
    QString dmg_range = "";
    QString weapon_speed = "";
    QString dps = "";

    if (slot == "1H")
        set_weapon_tooltip(item, slot, "One-hand", dmg_range, weapon_speed, dps);
    else if (slot == "MH")
        set_weapon_tooltip(item, slot, "Mainhand", dmg_range, weapon_speed, dps);
    else if (slot == "OH")
        set_weapon_tooltip(item, slot, "Offhand", dmg_range, weapon_speed, dps);
    else if (slot == "2H")
        set_weapon_tooltip(item, slot, "Two-hand", dmg_range, weapon_speed, dps);
    else if (slot == "RING")
        slot = "Finger";
    else
        slot = get_capitalized_string(slot);

    QString class_restriction = "";
    set_class_restriction_tooltip(item, class_restriction);

    QString lvl_req = QString("Requires level %1").arg(item->get_value("req_lvl"));

    QVariantList tooltip_info = {
        QVariant(item->get_name()),
        QVariant(item->get_value("quality")),
        QVariant(boe_string),
        QVariant(unique),
        QVariant(slot),
        QVariant(get_capitalized_string(item->get_value("type"))),
        QVariant(dmg_range),
        QVariant(weapon_speed),
        QVariant(dps),
        QVariant(item->get_base_stat_tooltip()),
        QVariant(class_restriction),
        QVariant(lvl_req),
        QVariant(item->get_equip_effect_tooltip()),
        QVariant(item->get_value("special_equip_effect")),
        QVariant(item->get_value("flavour_text"))
    };

    return tooltip_info;
}

void GUIControl::set_weapon_tooltip(Item*& item, QString& slot, QString type, QString& dmg_range, QString& wpn_speed, QString& dps) {
    slot = type;
    Weapon* wpn = dynamic_cast<Weapon*>(item);
    dmg_range = QString("%1 - %2 Damage").arg(QString::number(wpn->get_min_dmg()), QString::number(wpn->get_max_dmg()));
    dps = QString("(%1 damage per second)").arg(QString::number(wpn->get_wpn_dps(), 'f', 1));
    wpn_speed = "Speed " + QString::number(wpn->get_base_weapon_speed(), 'f', 2);
}

void GUIControl::set_class_restriction_tooltip(Item *&item, QString &restriction) {
    QVector<QString> restrictions;

    if (item->get_value("RESTRICTED_TO_WARRIOR") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["WARRIOR"]->get_class_color(), chars["WARRIOR"]->get_name()));
    if (item->get_value("RESTRICTED_TO_PALADIN") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["PALADIN"]->get_class_color(), chars["PALADIN"]->get_name()));
    if (item->get_value("RESTRICTED_TO_ROGUE") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["ROGUE"]->get_class_color(), chars["ROGUE"]->get_name()));
    if (item->get_value("RESTRICTED_TO_HUNTER") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["HUNTER"]->get_class_color(), chars["HUNTER"]->get_name()));

    if (restrictions.empty())
        return;

    for (int i = 0; i < restrictions.size(); ++i) {
        if (restriction == "")
            restriction = "Classes: ";
        else
            restriction += ", ";
        restriction += restrictions[i];
    }
}

QString GUIControl::get_capitalized_string(const QString& string) const {
    return QString(string[0]) + QString(string.right(string.size() - 1)).toLower();
}
