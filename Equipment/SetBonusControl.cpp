#include "SetBonusControl.h"

#include "Backstab.h"
#include "CharacterStats.h"
#include "Energy.h"
#include "EquipmentDb.h"
#include "Eviscerate.h"
#include "Hemorrhage.h"
#include "InstantPoison.h"
#include "ItemNamespace.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SetBonusFileReader.h"
#include "SinisterStrike.h"
#include "SliceAndDice.h"

SetBonusControl::SetBonusControl(EquipmentDb* equipment_db, Character* pchar) :
    equipment_db(equipment_db),
    pchar(pchar)
{
    SetBonusFileReader().read_set_bonuses("set_bonuses.xml", possible_set_items, set_bonus_tooltips);
}

void SetBonusControl::equip_item(const int item_id) {
    if (!possible_set_items.contains(item_id))
        return;

    QString set_name = possible_set_items[item_id];
    current_set_items[item_id] = set_name;
    int num_pieces = get_num_equipped_pieces_for_set(set_name);

    if (set_name == "Nightslayer Armor") {
        switch (num_pieces) {
        case 5:
            dynamic_cast<Rogue*>(pchar)->get_energy()->max += 10;
            break;
        }
    }
    else if (set_name == "Bloodfang Armor") {
        switch (num_pieces) {
        case 3: {
            dynamic_cast<Rogue*>(pchar)->get_mh_instant_poison()->activate_set_bonus(set_name, num_pieces);
            dynamic_cast<Rogue*>(pchar)->get_oh_instant_poison()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Deathdealer's Embrace") {
        switch (num_pieces) {
        case 5: {
            auto* spells = dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells());
            spells->get_eviscerate()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Bonescythe Armor") {
        switch (num_pieces) {
        case 4: {
            auto* spells = dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells());
            spells->get_backstab()->activate_set_bonus(set_name, num_pieces);
            spells->get_hemorrhage()->activate_set_bonus(set_name, num_pieces);
            spells->get_sinister_strike()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Devilsaur Armor") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_hit(0.02);
            break;
        }
    }
    else if (set_name == "Dal'Rend's Arms") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_melee_ap(50);
            pchar->get_stats()->increase_ranged_ap(50);
            break;
        }
    }
    else if (set_name == "The Twin Blades of Hakkari") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_wpn_skill(WeaponTypes::SWORD, 6);
            break;
        }
    }
    else if (set_name == "Emblems of Veiled Shadows") {
        switch (num_pieces) {
        case 3:
            auto* spells = dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells());
            spells->get_slice_and_dice()->activate_set_bonus(set_name, num_pieces);
        }
    }
}

void SetBonusControl::unequip_item(const int item_id) {
    if (!current_set_items.contains(item_id))
        return;

    QString set_name = current_set_items[item_id];
    int num_pieces = get_num_equipped_pieces_for_set(set_name);
    current_set_items.take(item_id);

    if (set_name == "Nightslayer Armor") {
        switch (num_pieces) {
        case 5:
            dynamic_cast<Rogue*>(pchar)->get_energy()->max -= 10;
            break;
        }
    }
    else if (set_name == "Bloodfang Armor") {
        switch (num_pieces) {
        case 3: {
            dynamic_cast<Rogue*>(pchar)->get_mh_instant_poison()->deactivate_set_bonus(set_name, num_pieces);
            dynamic_cast<Rogue*>(pchar)->get_oh_instant_poison()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Deathdealer's Embrace") {
        switch (num_pieces) {
        case 5: {
            auto* spells = dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells());
            spells->get_eviscerate()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Bonescythe Armor") {
        switch (num_pieces) {
        case 4: {
            auto* spells = dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells());
            spells->get_backstab()->deactivate_set_bonus(set_name, num_pieces);
            spells->get_hemorrhage()->deactivate_set_bonus(set_name, num_pieces);
            spells->get_sinister_strike()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Devilsaur Armor") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_hit(0.02);
            break;
        }
    }
    else if (set_name == "Dal'Rend's Arms") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_melee_ap(50);
            pchar->get_stats()->decrease_ranged_ap(50);
            break;
        }
    }
    else if (set_name == "The Twin Blades of Hakkari") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_wpn_skill(WeaponTypes::SWORD, 6);
            break;
        }
    }
    else if (set_name == "Emblems of Veiled Shadows") {
        switch (num_pieces) {
        case 3:
            auto* spells = dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells());
            spells->get_slice_and_dice()->deactivate_set_bonus(set_name, num_pieces);
        }
    }
}

bool SetBonusControl::is_set_item(const int item_id) const {
    return possible_set_items.contains(item_id);
}

QString SetBonusControl::get_set_name(const int item_id) const {
    assert(possible_set_items.contains(item_id));

    return possible_set_items[item_id];
}

QVector<QPair<QString, bool>> SetBonusControl::get_item_names_in_set(const int item_id) const {
    assert(possible_set_items.contains(item_id));

    QVector<QPair<QString, bool>> item_names_and_equipped;

    QString set_name = get_set_name(item_id);
    QMap<int, QString>::const_iterator it = possible_set_items.constBegin();
    auto end = possible_set_items.constEnd();
    while (it != end) {
        if (it.value() == set_name) {
            item_names_and_equipped.append({equipment_db->get_name_for_item_id(it.key()),
                                            current_set_items.contains(it.key())});
        }

        ++it;
    }

    return item_names_and_equipped;
}

QVector<QPair<QString, bool>> SetBonusControl::get_set_bonus_tooltips(const int item_id) const {
    assert(possible_set_items.contains(item_id));
    QString set_name = get_set_name(item_id);
    assert(set_bonus_tooltips.contains(set_name));

    int num_equipped = get_num_equipped_pieces_for_set(set_name);

    QVector<QPair<QString, bool>> tooltips_and_active;
    for (auto & tooltip : set_bonus_tooltips[set_name])
        tooltips_and_active.append({tooltip.second, tooltip.first <= num_equipped});

    return tooltips_and_active;
}

int SetBonusControl::get_num_equipped_pieces_for_set(const QString& set_name) const {
    int num_set_pieces = 0;
    for (auto & equipped_set : current_set_items) {
        if (equipped_set == set_name)
            ++num_set_pieces;
    }

    return num_set_pieces;
}
