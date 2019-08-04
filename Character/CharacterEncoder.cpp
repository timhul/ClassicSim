#include "CharacterEncoder.h"

#include "Character.h"
#include "CharacterEncoding.h"
#include "CharacterSpells.h"
#include "CharacterTalents.h"
#include "EnabledBuffs.h"
#include "Equipment.h"
#include "Item.h"
#include "Projectile.h"
#include "Race.h"
#include "Rotation.h"
#include "SimSettings.h"
#include "Target.h"
#include "Utils/Check.h"
#include "Weapon.h"

CharacterEncoder::CharacterEncoder(Character *pchar):
    pchar(pchar)
{}

void CharacterEncoder::set_character(Character* pchar) {
    this->pchar = pchar;
}

QString CharacterEncoder::get_current_setup_string() {
    check((pchar != nullptr), "pchar nullptr");

    this->pchar_str = "";

    key_val("PHASE", QString::number(static_cast<int>(pchar->get_sim_settings()->get_phase())));
    key_val("RACE", pchar->get_race()->get_name());
    key_val("CLASS", pchar->class_name);
    key_val("PARTY", QString::number(pchar->get_party()));
    key_val("PARTY_MEMBER", QString::number(pchar->get_party_member()));

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
    add_item("PROJECTILE", dynamic_cast<Item*>(pchar->get_equipment()->get_projectile()));
    add_item("RELIC", dynamic_cast<Item*>(pchar->get_equipment()->get_relic()));

    QVector<QPair<QString, QVector<QPair<QString, QString>>>> setup = pchar->get_talents()->get_current_talent_setup();
    add_vector(setup);
    add_vector_values_only("BUFFS", pchar->get_enabled_buffs()->get_active_external_buffs());
    add_vector_values_only("DEBUFFS", pchar->get_enabled_buffs()->get_active_external_debuffs());
    key_val("TARGET_LVL", QString::number(pchar->get_target()->get_lvl()));
    key_val("TARGET_TYPE", pchar->get_target()->get_creature_type_string());
    key_val("TARGET_BASE_ARMOR", QString::number(pchar->get_target()->get_base_armor()));

    key_val("ROTATION", pchar->get_spells()->get_rotation()->get_name());

    add_enchants();

    key_val("RULESET", QString::number(pchar->get_sim_settings()->get_ruleset()));

    return pchar_str;
}

void CharacterEncoder::add_item(const QString& key, Item* item) {
    if (item == nullptr)
        return;

    key_val(key, QString::number(item->item_id));
}

void CharacterEncoder::add_vector_values_only(const QString& name, const QVector<QString>& vec) {
    if (vec.empty())
        return;

    QVector<QPair<QString, QVector<QPair<QString, QString>>>> setup;
    QVector<QPair<QString, QString>> key_vals;

    for (const auto & i : vec) {
        key_vals.append(QPair<QString, QString>(i, "N/A"));
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

    for (const auto & i : vec) {
        new_element();

        pchar_str += i.first + QString(Encoding::LIST_INITIALIZER);
        for (const auto & j : i.second) {
            key_val_list(j.first, j.second);
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

void CharacterEncoder::add_enchants() {
    Weapon* wpn = pchar->get_equipment()->get_mainhand();
    if (wpn != nullptr) {
        key_val("MH_TEMPORARY_ENCHANT", QString::number(wpn->get_temporary_enchant_enum_value()));
        key_val("MH_ENCHANT", QString::number(wpn->get_enchant_enum_value()));
    }

    wpn = pchar->get_equipment()->get_offhand();
    if (wpn != nullptr) {
        key_val("OH_TEMPORARY_ENCHANT", QString::number(wpn->get_temporary_enchant_enum_value()));
        key_val("OH_ENCHANT", QString::number(wpn->get_enchant_enum_value()));
    }

    Item* item = pchar->get_equipment()->get_head();
    if (item != nullptr)
        key_val("HEAD_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_shoulders();
    if (item != nullptr)
        key_val("SHOULDER_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_back();
    if (item != nullptr)
        key_val("BACK_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_chest();
    if (item != nullptr)
        key_val("CHEST_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_wrist();
    if (item != nullptr)
        key_val("WRIST_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_gloves();
    if (item != nullptr)
        key_val("GLOVES_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_legs();
    if (item != nullptr)
        key_val("LEGS_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_boots();
    if (item != nullptr)
        key_val("BOOTS_ENCHANT", QString::number(item->get_enchant_enum_value()));

    item = pchar->get_equipment()->get_ranged();
    if (item != nullptr)
        key_val("RANGED_ENCHANT", QString::number(item->get_enchant_enum_value()));
}
