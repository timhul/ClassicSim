
#include "CharacterEncoder.h"
#include "ActiveBuffs.h"
#include "Character.h"
#include "Equipment.h"
#include "Item.h"
#include "Talents.h"
#include "Weapon.h"
#include "Race.h"
#include "CharacterEncoding.h"
#include "CombatRoll.h"
#include "Target.h"
#include <QDebug>

CharacterEncoder::CharacterEncoder(Character* pchar, QObject* parent):
    QObject(parent),
    pchar(pchar)
{}

QString CharacterEncoder::get_current_setup_string() {
    this->pchar_str = "";

    key_val("RACE", pchar->get_race()->get_name());
    key_val("CLASS", pchar->get_name());

    add_item("MAINHAND", dynamic_cast<Item*>(pchar->get_equipment()->get_mainhand()));
    add_item("OFFHAND", dynamic_cast<Item*>(pchar->get_equipment()->get_offhand()));
    add_item("RANGED", dynamic_cast<Item*>(pchar->get_equipment()->get_ranged()));
    add_item("HEAD", dynamic_cast<Item*>(pchar->get_equipment()->get_head()));
    add_item("NECK", dynamic_cast<Item*>(pchar->get_equipment()->get_neck()));
    add_item("SHOULDERS", dynamic_cast<Item*>(pchar->get_equipment()->get_shoulders()));
    add_item("BACK", dynamic_cast<Item*>(pchar->get_equipment()->get_back()));
    add_item("CHEST", dynamic_cast<Item*>(pchar->get_equipment()->get_chest()));
    add_item("WRIST", dynamic_cast<Item*>(pchar->get_equipment()->get_wrist()));
    add_item("GLOVES", dynamic_cast<Item*>(pchar->get_equipment()->get_gloves()));
    add_item("BELT", dynamic_cast<Item*>(pchar->get_equipment()->get_belt()));
    add_item("LEGS", dynamic_cast<Item*>(pchar->get_equipment()->get_legs()));
    add_item("BOOTS", dynamic_cast<Item*>(pchar->get_equipment()->get_boots()));
    add_item("RING1", dynamic_cast<Item*>(pchar->get_equipment()->get_ring1()));
    add_item("RING2", dynamic_cast<Item*>(pchar->get_equipment()->get_ring2()));
    add_item("TRINKET1", dynamic_cast<Item*>(pchar->get_equipment()->get_trinket1()));
    add_item("TRINKET2", dynamic_cast<Item*>(pchar->get_equipment()->get_trinket2()));

    QVector<QPair<QString, QVector<QPair<QString, QString>>>> setup = pchar->get_talents()->get_current_talent_setup();
    add_vector(setup);
    add_vector_values_only("BUFFS", pchar->get_active_buffs()->get_active_external_buffs());
    key_val("TARGET_LVL", QString::number(pchar->get_combat_roll()->get_target()->get_lvl()));
    key_val("TARGET_TYPE", pchar->get_combat_roll()->get_target()->get_creature_type_string());
    key_val("TARGET_ARMOR", QString::number(pchar->get_combat_roll()->get_target()->get_armor()));

    return pchar_str;
}

void CharacterEncoder::add_item(const QString& key, Item* item) {
    if (item == nullptr)
        return;

    key_val(key, item->get_name());
}

void CharacterEncoder::add_vector_values_only(const QString& name, const QVector<QString>& vec) {
    if (vec.empty())
        return;

    QVector<QPair<QString, QVector<QPair<QString, QString>>>> setup;
    QVector<QPair<QString, QString>> key_vals;

    for (int i = 0; i < vec.size(); ++i) {
        key_vals.append(QPair<QString, QString>(vec[i], "N/A"));
    }

    QPair<QString, QVector<QPair<QString, QString>>> list = {name, key_vals};

    setup.append(list);
    add_vector(setup);
}

void CharacterEncoder::add_vector(QVector<QPair<QString, QVector<QPair<QString, QString>>>> & vec) {
    // Given on the format:
    // List of lists to add { List name [ List of key-value pairs ] }
    if (vec.empty())
        return;

    for (int i = 0; i < vec.size(); ++i) {
        new_element();

        pchar_str += vec[i].first + QString(Encoding::LIST_INITIALIZER);
        for (int j = 0; j < vec[i].second.size(); ++j) {
            key_val_list(vec[i].second[j].first, vec[i].second[j].second);
        }

        pchar_str += QString(Encoding::LIST_END);
    }
}

void CharacterEncoder::new_element() {
    pchar_str += pchar_str != "" ? QString(Encoding::ENTRY_SEPARATOR) : "";
}

void CharacterEncoder::new_list_element() {
    pchar_str += pchar_str.endsWith(QString(Encoding::LIST_INITIALIZER)) ?
                "" :
                QString(Encoding::LIST_ELEMENT_SEPARATOR);
}

void CharacterEncoder::key_val(const QString& key, const QString& value) {
    new_element();
    pchar_str += QString("%1%2%3").arg(key, QString(Encoding::KEY_VAL_SEPARATOR), value);
}

void CharacterEncoder::key_val_list(const QString& key, const QString& value) {
    new_list_element();
    pchar_str += QString("%1%2%3").arg(key, QString(Encoding::KEY_VAL_SEPARATOR), value);
}
