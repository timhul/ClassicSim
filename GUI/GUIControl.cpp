#include "GUIControl.h"

#include <QDebug>

#include "Character.h"
#include "EnchantModel.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Item.h"
#include "ItemModel.h"
#include "ItemTypeFilterModel.h"
#include "Projectile.h"
#include "Quiver.h"
#include "RandomAffixes.h"
#include "SetBonusControl.h"
#include "Weapon.h"
#include "WeaponModel.h"

GUIControl::GUIControl(QObject* parent) : ClassicSimControl(parent) {}
GUIControl::~GUIControl() {}

QVariantList GUIControl::get_tooltip_from_item(Item* item) {
    if (item == nullptr)
        return QVariantList();

    QString boe_string = item->get_value("boe") == "yes" ? "Binds when equipped" : "Binds when picked up";
    QString unique = item->get_value("unique") == "yes" ? "Unique" : "";

    QString slot = item->get_value("slot");
    QString dmg_range = "";
    QString weapon_speed = "";
    QString dps = "";

    if (slot == "1H")
        set_weapon_tooltip(item, slot, "One-hand", dmg_range, weapon_speed, dps);
    else if (slot == "MH")
        set_weapon_tooltip(item, slot, "Main Hand", dmg_range, weapon_speed, dps);
    else if (slot == "OH")
        if (item->get_item_type() != WeaponTypes::SHIELD)
            set_weapon_tooltip(item, slot, "Offhand", dmg_range, weapon_speed, dps);
        else
            slot = "Offhand";
    else if (slot == "2H")
        set_weapon_tooltip(item, slot, "Two-hand", dmg_range, weapon_speed, dps);
    else if (slot == "RANGED") {
        const QSet<QString> ranged_weapon_classes = {"Hunter", "Warrior", "Rogue", "Mage", "Warlock", "Priest"};
        if (ranged_weapon_classes.contains(current_char->class_name))
            set_weapon_tooltip(item, slot, "Ranged", dmg_range, weapon_speed, dps);
    } else if (slot == "PROJECTILE")
        set_projectile_tooltip(item, slot, dps);
    else if (slot == "RING")
        slot = "Finger";
    else if (slot == "GLOVES")
        slot = "Hands";
    else if (slot == "BELT")
        slot = "Waist";
    else if (slot == "BOOTS")
        slot = "Feet";
    else if (slot == "SHOULDERS")
        slot = "Shoulder";
    else
        slot = get_initial_upper_case_rest_lower_case(slot);

    QString class_restriction = "";
    set_class_restriction_tooltip(item, class_restriction);

    QString lvl_req = QString("Requires level %1").arg(item->get_value("req_lvl"));

    QVariantList tooltip_info = {QVariant(item->name),
                                 QVariant(item->get_value("quality")),
                                 QVariant(boe_string),
                                 QVariant(unique),
                                 QVariant(slot),
                                 QVariant(get_initial_upper_case_rest_lower_case(item->get_value("type"))),
                                 QVariant(dmg_range),
                                 QVariant(weapon_speed),
                                 QVariant(dps),
                                 QVariant(item->get_base_stat_tooltip()),
                                 QVariant(class_restriction),
                                 QVariant(lvl_req),
                                 QVariant(item->get_equip_effect_tooltip()),
                                 QVariant(item->get_value("flavour_text"))};

    set_set_bonus_tooltip(item, tooltip_info);

    return tooltip_info;
}

void GUIControl::set_weapon_tooltip(Item*& item, QString& slot, QString type, QString& dmg_range, QString& wpn_speed, QString& dps) {
    slot = std::move(type);
    auto wpn = static_cast<Weapon*>(item);
    dmg_range = QString("%1 - %2 Damage").arg(QString::number(wpn->get_min_dmg()), QString::number(wpn->get_max_dmg()));
    dps = QString("(%1 damage per second)").arg(QString::number(wpn->get_wpn_dps(), 'f', 1));
    wpn_speed = "Speed " + QString::number(wpn->get_base_weapon_speed(), 'f', 2);
}

void GUIControl::set_projectile_tooltip(Item* item, QString& slot, QString& dps) {
    slot = get_initial_upper_case_rest_lower_case(slot);

    auto projectile = static_cast<Projectile*>(item);
    dps = QString("Adds %1 damage per second").arg(QString::number(projectile->get_projectile_dps(), 'f', 1));
}

void GUIControl::set_class_restriction_tooltip(Item*& item, QString& restriction) {
    QVector<QString> restrictions;

    if (item->get_value("RESTRICTED_TO_WARRIOR") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Warrior"]->class_color, chars["Warrior"]->class_name));
    if (item->get_value("RESTRICTED_TO_PALADIN") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Paladin"]->class_color, chars["Paladin"]->class_name));
    if (item->get_value("RESTRICTED_TO_ROGUE") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Rogue"]->class_color, chars["Rogue"]->class_name));
    if (item->get_value("RESTRICTED_TO_HUNTER") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Hunter"]->class_color, chars["Hunter"]->class_name));
    if (item->get_value("RESTRICTED_TO_SHAMAN") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Shaman"]->class_color, chars["Shaman"]->class_name));
    if (item->get_value("RESTRICTED_TO_DRUID") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Druid"]->class_color, chars["Druid"]->class_name));
    if (item->get_value("RESTRICTED_TO_MAGE") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Mage"]->class_color, chars["Mage"]->class_name));
    if (item->get_value("RESTRICTED_TO_PRIEST") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Priest"]->class_color, chars["Priest"]->class_name));
    if (item->get_value("RESTRICTED_TO_WARLOCK") != "")
        restrictions.append(QString("<font color=\"%1\">%2</font>").arg(chars["Warlock"]->class_color, chars["Warlock"]->class_name));

    if (restrictions.empty())
        return;

    for (const auto& i : restrictions) {
        if (restriction == "")
            restriction = "Classes: ";
        else
            restriction += ", ";
        restriction += i;
    }
}

void GUIControl::set_set_bonus_tooltip(Item* item, QVariantList& tooltip) const {
    SetBonusControl* set_bonuses = current_char->get_equipment()->get_set_bonus_control();
    const int item_id = item->item_id;

    if (!set_bonuses->is_set_item(item_id)) {
        tooltip.append(false);
        return;
    }
    tooltip.append(true);

    QString set_name = set_bonuses->get_set_name(item_id);
    QVector<QPair<QString, bool>> item_names_in_set = set_bonuses->get_item_names_in_set(item_id);

    int num_equipped_set_items = set_bonuses->get_num_equipped_pieces_for_set(set_name);
    tooltip.append(QString("%1 (%2/%3)").arg(set_name).arg(num_equipped_set_items).arg(item_names_in_set.size()));

    tooltip.append(item_names_in_set.size());
    for (const auto& item_name : item_names_in_set) {
        QString font_color = item_name.second ? "#ffd100" : "#727171";
        tooltip.append(QString("<font color=\"%1\">%2</font>").arg(font_color, item_name.first));
    }

    QVector<QPair<QString, bool>> set_bonus_tooltips = set_bonuses->get_set_bonus_tooltips(item_id);
    tooltip.append(set_bonus_tooltips.size());
    for (const auto& bonus_tooltip : set_bonus_tooltips) {
        QString font_color = bonus_tooltip.second ? "#1eff00" : "#727171";
        tooltip.append(QString("<font color=\"%1\">%2</font>").arg(font_color, bonus_tooltip.first));
    }
}

QVariantList GUIControl::getTooltip(const QString& slot_string) {
    Item* item = nullptr;

    if (slot_string == "MAINHAND")
        item = current_char->get_equipment()->get_mainhand();
    if (slot_string == "OFFHAND")
        item = current_char->get_equipment()->get_offhand();
    if (slot_string == "RANGED")
        item = current_char->get_equipment()->get_ranged();
    if (slot_string == "HEAD")
        item = current_char->get_equipment()->get_head();
    if (slot_string == "NECK")
        item = current_char->get_equipment()->get_neck();
    if (slot_string == "SHOULDERS")
        item = current_char->get_equipment()->get_shoulders();
    if (slot_string == "BACK")
        item = current_char->get_equipment()->get_back();
    if (slot_string == "CHEST")
        item = current_char->get_equipment()->get_chest();
    if (slot_string == "WRIST")
        item = current_char->get_equipment()->get_wrist();
    if (slot_string == "GLOVES")
        item = current_char->get_equipment()->get_gloves();
    if (slot_string == "BELT")
        item = current_char->get_equipment()->get_belt();
    if (slot_string == "LEGS")
        item = current_char->get_equipment()->get_legs();
    if (slot_string == "BOOTS")
        item = current_char->get_equipment()->get_boots();
    if (slot_string == "RING1")
        item = current_char->get_equipment()->get_ring1();
    if (slot_string == "RING2")
        item = current_char->get_equipment()->get_ring2();
    if (slot_string == "TRINKET1")
        item = current_char->get_equipment()->get_trinket1();
    if (slot_string == "TRINKET2")
        item = current_char->get_equipment()->get_trinket2();
    if (slot_string == "PROJECTILE")
        item = current_char->get_equipment()->get_projectile();
    if (slot_string == "RELIC")
        item = current_char->get_equipment()->get_relic();
    if (slot_string == "QUIVER")
        item = current_char->get_equipment()->get_quiver();

    return get_tooltip_from_item(item);
}

QVariantList GUIControl::getTooltip(const int item_id) {
    Item* item = this->equipment_db->get_item(item_id);
    return get_tooltip_from_item(item);
}

void GUIControl::setSlot(const QString& slot_string, const int item_id, const uint affix_id) {
    RandomAffix* affix = random_affixes_db->get_affix(affix_id);

    if (slot_string == "MAINHAND") {
        current_char->get_equipment()->set_mainhand(item_id, affix);
        mh_enchants->update_enchants();
        mh_temporary_enchants->update_enchants();
    }
    if (slot_string == "OFFHAND") {
        current_char->get_equipment()->set_offhand(item_id, affix);
        oh_temporary_enchants->update_enchants();
    }
    if (slot_string == "RANGED")
        current_char->get_equipment()->set_ranged(item_id, affix);
    if (slot_string == "HEAD")
        current_char->get_equipment()->set_head(item_id, affix);
    if (slot_string == "NECK")
        current_char->get_equipment()->set_neck(item_id, affix);
    if (slot_string == "SHOULDERS")
        current_char->get_equipment()->set_shoulders(item_id, affix);
    if (slot_string == "BACK")
        current_char->get_equipment()->set_back(item_id, affix);
    if (slot_string == "CHEST")
        current_char->get_equipment()->set_chest(item_id, affix);
    if (slot_string == "WRIST")
        current_char->get_equipment()->set_wrist(item_id, affix);
    if (slot_string == "GLOVES")
        current_char->get_equipment()->set_gloves(item_id, affix);
    if (slot_string == "BELT")
        current_char->get_equipment()->set_belt(item_id, affix);
    if (slot_string == "LEGS")
        current_char->get_equipment()->set_legs(item_id, affix);
    if (slot_string == "BOOTS")
        current_char->get_equipment()->set_boots(item_id, affix);
    if (slot_string == "RING1")
        current_char->get_equipment()->set_ring1(item_id, affix);
    if (slot_string == "RING2")
        current_char->get_equipment()->set_ring2(item_id, affix);
    if (slot_string == "TRINKET1")
        current_char->get_equipment()->set_trinket1(item_id);
    if (slot_string == "TRINKET2")
        current_char->get_equipment()->set_trinket2(item_id);
    if (slot_string == "PROJECTILE")
        current_char->get_equipment()->set_projectile(item_id);
    if (slot_string == "RELIC")
        current_char->get_equipment()->set_relic(item_id);
    if (slot_string == "QUIVER")
        current_char->get_equipment()->set_quiver(item_id);

    emit equipmentChanged();
    emit statsChanged();
    emit enchantChanged();
}

void GUIControl::clearSlot(const QString& slot_string) {
    if (slot_string == "MAINHAND")
        current_char->get_equipment()->clear_mainhand();
    if (slot_string == "OFFHAND")
        current_char->get_equipment()->clear_offhand();
    if (slot_string == "RANGED")
        current_char->get_equipment()->clear_ranged();
    if (slot_string == "HEAD")
        current_char->get_equipment()->clear_head();
    if (slot_string == "NECK")
        current_char->get_equipment()->clear_neck();
    if (slot_string == "SHOULDERS")
        current_char->get_equipment()->clear_shoulders();
    if (slot_string == "BACK")
        current_char->get_equipment()->clear_back();
    if (slot_string == "CHEST")
        current_char->get_equipment()->clear_chest();
    if (slot_string == "WRIST")
        current_char->get_equipment()->clear_wrist();
    if (slot_string == "GLOVES")
        current_char->get_equipment()->clear_gloves();
    if (slot_string == "BELT")
        current_char->get_equipment()->clear_belt();
    if (slot_string == "LEGS")
        current_char->get_equipment()->clear_legs();
    if (slot_string == "BOOTS")
        current_char->get_equipment()->clear_boots();
    if (slot_string == "RING1")
        current_char->get_equipment()->clear_ring1();
    if (slot_string == "RING2")
        current_char->get_equipment()->clear_ring2();
    if (slot_string == "TRINKET1")
        current_char->get_equipment()->clear_trinket1();
    if (slot_string == "TRINKET2")
        current_char->get_equipment()->clear_trinket2();
    if (slot_string == "PROJECTILE")
        current_char->get_equipment()->clear_projectile();
    if (slot_string == "RELIC")
        current_char->get_equipment()->clear_relic();
    if (slot_string == "QUIVER")
        current_char->get_equipment()->clear_quiver();

    emit equipmentChanged();
    emit statsChanged();
    emit enchantChanged();
}

void GUIControl::selectSlot(const QString& slot_string) {
    int slot = get_slot_int(slot_string);

    if (slot == -1 || (slot == ItemSlots::PROJECTILE && current_char->class_name != "Hunter"))
        return;

    if (slot == ItemSlots::QUIVER && current_char->class_name != "Hunter")
        return;

    item_type_filter_model->set_item_slot(slot);

    switch (slot) {
    case ItemSlots::MAINHAND:
    case ItemSlots::OFFHAND:
    case ItemSlots::RANGED:
        weapon_model->setSlot(slot);
        break;
    default:
        item_model->setSlot(slot);
        break;
    }

    emit equipmentSlotSelected();
}

void GUIControl::selectClass(const QString& class_name) {
    if (!chars.contains(class_name)) {
        qDebug() << QString("Class %1 not found in char list!").arg(class_name);
        return;
    }

    if (!supported_classes.contains(class_name)) {
        qDebug() << QString("Class %1 not implemented").arg(class_name);
        return;
    }

    set_character(chars[class_name]);
}

