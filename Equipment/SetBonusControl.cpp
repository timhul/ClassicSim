#include "SetBonusControl.h"

#include "AimedShot.h"
#include "AspectOfTheHawk.h"
#include "AspectOfTheHawkBuff.h"
#include "AutoShot.h"
#include "Backstab.h"
#include "CharacterStats.h"
#include "Energy.h"
#include "EquipmentDb.h"
#include "Eviscerate.h"
#include "ExposeWeaknessProc.h"
#include "Hemorrhage.h"
#include "Hunter.h"
#include "HunterSpells.h"
#include "InstantPoison.h"
#include "ItemNamespace.h"
#include "ManaDrainProc.h"
#include "MultiShot.h"
#include "Pet.h"
#include "RapidFire.h"
#include "RapidFireBuff.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SetBonusFileReader.h"
#include "SinisterStrike.h"
#include "SliceAndDice.h"
#include "Utils/Check.h"

SetBonusControl::SetBonusControl(EquipmentDb* equipment_db, Character* pchar) :
    equipment_db(equipment_db),
    pchar(pchar)
{
    SetBonusFileReader().read_set_bonuses("set_bonuses.xml", possible_set_items, set_bonus_tooltips);
}

SetBonusControl::~SetBonusControl() {
    for (auto & proc : active_procs) {
        if (proc->is_enabled())
            proc->disable_proc();
        delete proc;
    }
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
    else if (set_name == "Avenger's Battlegear") {
        switch (num_pieces) {
        case 5:
            pchar->get_stats()->increase_base_spell_damage(71);
            break;
        }
    }
    else if (set_name == "Major Mojo Infusion") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_melee_ap(30);
            pchar->get_stats()->increase_ranged_ap(30);
            break;
        }
    }
    else if (set_name == "Predator's Armor") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_melee_ap(20);
            pchar->get_stats()->increase_ranged_ap(20);
            break;
        }
    }
    else if (set_name == "Trappings of the Unseen Path") {
        switch (num_pieces) {
        case 3:
            dynamic_cast<Hunter*>(pchar)->get_pet()->increase_damage_modifier(3);
            break;
        }
    }
    else if (set_name == "Beaststalker Armor") {
        switch (num_pieces) {
        case 4:
            pchar->get_stats()->increase_melee_ap(40);
            pchar->get_stats()->increase_ranged_ap(40);
            break;
        case 6:
            if (!active_procs.contains("BEASTSTALKER_DRAIN"))
                active_procs["BEASTSTALKER_DRAIN"] = new ManaDrainProc(pchar,
                                                                       "Beaststalker 6 set",
                                                                       "Assets/items/Inv_belt_28.png",
                                                                       {ProcInfo::RangedAutoShot},
                                                                       0.04, 200, 200);
            active_procs["BEASTSTALKER_DRAIN"]->enable_proc();
            break;
        }
    }
    else if (set_name == "Beastmaster Armor") {
        switch (num_pieces) {
        case 4:
            if (!active_procs.contains("BEASTMASTER_DRAIN"))
                active_procs["BEASTMASTER_DRAIN"] = new ManaDrainProc(pchar,
                                                                      "Beastmaster 4 set",
                                                                      "Assets/items/Inv_belt_28.png",
                                                                      {ProcInfo::RangedAutoShot},
                                                                      0.04, 200, 200);
            active_procs["BEASTMASTER_DRAIN"]->enable_proc();
            break;
        case 6:
            pchar->get_stats()->increase_melee_ap(40);
            pchar->get_stats()->increase_ranged_ap(40);
            break;
        }
    }
    else if (set_name == "Giantstalker Armor") {
        switch (num_pieces) {
        case 8: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_multi_shot()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Dragonstalker Armor") {
        switch (num_pieces) {
        case 3: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_aspect_of_the_hawk()->get_aspect_of_the_hawk_buff()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        case 8: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_expose_weakness_proc()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Striker's Garb") {
        switch (num_pieces) {
        case 5: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_rapid_fire()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Cryptstalker Armor") {
        switch (num_pieces) {
        case 2: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_rapid_fire()->get_rapid_fire_buff()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        case 4:
            pchar->get_stats()->increase_melee_ap(50);
            pchar->get_stats()->increase_ranged_ap(50);
            dynamic_cast<Hunter*>(pchar)->get_pet()->increase_attack_power(50);
            break;
        case 6: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_aimed_shot()->activate_set_bonus(set_name, num_pieces);
            spells->get_auto_shot()->activate_set_bonus(set_name, num_pieces);
            spells->get_multi_shot()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        case 8: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_aimed_shot()->activate_set_bonus(set_name, num_pieces);
            spells->get_multi_shot()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "The Gladiator") {
        switch (num_pieces) {
        case 4:
            pchar->get_stats()->increase_melee_ap(10);
            pchar->get_stats()->increase_ranged_ap(10);
            break;
        case 5:
            pchar->get_stats()->increase_melee_crit(100);
            pchar->get_stats()->increase_ranged_crit(100);
            break;
        }
    }
    else if (set_name == "Devilsaur Armor") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_melee_hit(200);
            pchar->get_stats()->increase_ranged_hit(200);
            break;
        }
    }
    else if (set_name == "Cadaverous Garb") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->increase_melee_ap(10);
            pchar->get_stats()->increase_ranged_ap(10);
            break;
        case 5:
            pchar->get_stats()->increase_melee_hit(200);
            pchar->get_stats()->increase_ranged_hit(200);
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
    else if (set_name == "Black Dragon Mail") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_melee_hit(100);
            pchar->get_stats()->increase_ranged_hit(100);
            break;
        case 3:
            pchar->get_stats()->increase_melee_crit(200);
            pchar->get_stats()->increase_ranged_crit(200);
            break;
        }
    }
    else if (set_name == "Bloodsoul Embrace") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->increase_mp5(12);
            break;
        }
    }
    else if (set_name == "Bloodmail Regalia") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->increase_melee_ap(10);
            pchar->get_stats()->increase_ranged_ap(10);
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
            break;
        }
    }
    else if (set_name == "Lieutenant Commander's Battlearmor" || set_name == "Champion's Battlearmor")
        activate_warrior_r10_pvp_set_bonuses(num_pieces);
    else if (set_name == "Lieutenant Commander's Pursuance" || set_name == "Champion's Pursuit")
        activate_hunter_r10_pvp_set_bonuses(num_pieces);
    else if (set_name == "Field Marshal's Battlegear" || set_name == "Warlord's Battlegear")
        activate_warrior_r13_pvp_set_bonuses(num_pieces);
    else if (set_name == "Field Marshal's Pursuit" || set_name == "Warlord's Pursuit")
        activate_hunter_r13_pvp_set_bonuses(num_pieces);
    else if (set_name == "The Highlander's Resolution" || set_name == "The Defiler's Resolution" ||
             set_name == "The Highlander's Determination" || set_name == "The Defiler's Determination")
        activate_arathi_basin_physical_set_bonuses(num_pieces);
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
    else if (set_name == "Avenger's Battlegear") {
        switch (num_pieces) {
        case 5:
            pchar->get_stats()->decrease_base_spell_damage(71);
            break;
        }
    }
    else if (set_name == "Major Mojo Infusion") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_melee_ap(30);
            pchar->get_stats()->decrease_ranged_ap(30);
            break;
        }
    }
    else if (set_name == "Predator's Armor") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_melee_ap(20);
            pchar->get_stats()->decrease_ranged_ap(20);
            break;
        }
    }
    else if (set_name == "Trappings of the Unseen Path") {
        switch (num_pieces) {
        case 3:
            dynamic_cast<Hunter*>(pchar)->get_pet()->decrease_damage_modifier(3);
            break;
        }
    }
    else if (set_name == "Beaststalker Armor") {
        switch (num_pieces) {
        case 4:
            pchar->get_stats()->decrease_melee_ap(40);
            pchar->get_stats()->decrease_ranged_ap(40);
            break;
        case 6:
            active_procs["BEASTSTALKER_DRAIN"]->disable_proc();
            break;
        }
    }
    else if (set_name == "Beastmaster Armor") {
        switch (num_pieces) {
        case 4:
            active_procs["BEASTMASTER_DRAIN"]->disable_proc();
            break;
        case 6:
            pchar->get_stats()->decrease_melee_ap(40);
            pchar->get_stats()->decrease_ranged_ap(40);
            break;
        }
    }
    else if (set_name == "Giantstalker Armor") {
        switch (num_pieces) {
        case 8: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_multi_shot()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Dragonstalker Armor") {
        switch (num_pieces) {
        case 3: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_aspect_of_the_hawk()->get_aspect_of_the_hawk_buff()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        case 8: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_expose_weakness_proc()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Striker's Garb") {
        switch (num_pieces) {
        case 5: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_rapid_fire()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "Cryptstalker Armor") {
        switch (num_pieces) {
        case 2: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_rapid_fire()->get_rapid_fire_buff()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        case 4:
            pchar->get_stats()->decrease_melee_ap(50);
            pchar->get_stats()->decrease_ranged_ap(50);
            dynamic_cast<Hunter*>(pchar)->get_pet()->decrease_attack_power(50);
            break;
        case 6: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_aimed_shot()->deactivate_set_bonus(set_name, num_pieces);
            spells->get_auto_shot()->deactivate_set_bonus(set_name, num_pieces);
            spells->get_multi_shot()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        case 8: {
            auto* spells = dynamic_cast<HunterSpells*>(dynamic_cast<Hunter*>(pchar)->get_spells());
            spells->get_aimed_shot()->deactivate_set_bonus(set_name, num_pieces);
            spells->get_multi_shot()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    }
    else if (set_name == "The Gladiator") {
        switch (num_pieces) {
        case 4:
            pchar->get_stats()->decrease_melee_ap(10);
            pchar->get_stats()->decrease_ranged_ap(10);
            break;
        case 5:
            pchar->get_stats()->decrease_melee_crit(100);
            pchar->get_stats()->decrease_ranged_crit(100);
            break;
        }
    }
    else if (set_name == "Devilsaur Armor") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_melee_hit(200);
            pchar->get_stats()->decrease_ranged_hit(200);
            break;
        }
    }
    else if (set_name == "Cadaverous Garb") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->decrease_melee_ap(10);
            pchar->get_stats()->decrease_ranged_ap(10);
            break;
        case 5:
            pchar->get_stats()->decrease_melee_hit(200);
            pchar->get_stats()->decrease_ranged_hit(200);
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
    else if (set_name == "Black Dragon Mail") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_melee_hit(100);
            pchar->get_stats()->decrease_ranged_hit(100);
            break;
        case 3:
            pchar->get_stats()->decrease_melee_crit(200);
            pchar->get_stats()->decrease_ranged_crit(200);
            break;
        }
    }
    else if (set_name == "Bloodsoul Embrace") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->decrease_mp5(12);
            break;
        }
    }
    else if (set_name == "Bloodmail Regalia") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->decrease_melee_ap(10);
            pchar->get_stats()->decrease_ranged_ap(10);
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
            break;
        }
    }
    else if (set_name == "Lieutenant Commander's Battlearmor" || set_name == "Champion's Battlearmor")
        deactivate_warrior_r10_pvp_set_bonuses(num_pieces);
    else if (set_name == "Lieutenant Commander's Pursuance" || set_name == "Champion's Pursuit")
        deactivate_hunter_r10_pvp_set_bonuses(num_pieces);
    else if (set_name == "Field Marshal's Battlegear" || set_name == "Warlord's Battlegear")
        deactivate_warrior_r13_pvp_set_bonuses(num_pieces);
    else if (set_name == "Field Marshal's Pursuit" || set_name == "Warlord's Pursuit")
        deactivate_hunter_r13_pvp_set_bonuses(num_pieces);
    else if (set_name == "The Highlander's Resolution" || set_name == "The Defiler's Resolution" ||
             set_name == "The Highlander's Determination" || set_name == "The Defiler's Determination")
        deactivate_arathi_basin_physical_set_bonuses(num_pieces);
}

bool SetBonusControl::is_set_item(const int item_id) const {
    return possible_set_items.contains(item_id);
}

QString SetBonusControl::get_set_name(const int item_id) const {
    check(possible_set_items.contains(item_id), QString("Unknown item id '%1'").arg(item_id).toStdString());

    return possible_set_items[item_id];
}

QVector<QPair<QString, bool>> SetBonusControl::get_item_names_in_set(const int item_id) const {
    check(possible_set_items.contains(item_id), QString("Unknown item id '%1'").arg(item_id).toStdString());

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
    check(possible_set_items.contains(item_id), QString("Unknown item id '%1'").arg(item_id).toStdString());
    QString set_name = get_set_name(item_id);
    check(set_bonus_tooltips.contains(set_name), QString("Unknown set '%1'").arg(set_name).toStdString());

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

void SetBonusControl::activate_warrior_r10_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->increase_melee_ap(40);
        break;
    case 6:
        pchar->get_stats()->increase_stamina(20);
        break;
    }
}

void SetBonusControl::deactivate_warrior_r10_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->decrease_melee_ap(40);
        break;
    case 6:
        pchar->get_stats()->decrease_stamina(20);
        break;
    }
}

void SetBonusControl::activate_warrior_r13_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->increase_stamina(20);
        break;
    case 6:
        pchar->get_stats()->increase_melee_ap(40);
        break;
    }
}

void SetBonusControl::deactivate_warrior_r13_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->decrease_stamina(20);
        break;
    case 6:
        pchar->get_stats()->decrease_melee_ap(40);
        break;
    }
}

void SetBonusControl::activate_hunter_r10_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->increase_agility(20);
        break;
    case 6:
        pchar->get_stats()->increase_stamina(20);
        break;
    }
}

void SetBonusControl::deactivate_hunter_r10_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->decrease_agility(20);
        break;
    case 6:
        pchar->get_stats()->decrease_stamina(20);
        break;
    }
}

void SetBonusControl::activate_hunter_r13_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->increase_stamina(20);
        break;
    case 6:
        pchar->get_stats()->increase_agility(20);
        break;
    }
}

void SetBonusControl::deactivate_hunter_r13_pvp_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->decrease_stamina(20);
        break;
    case 6:
        pchar->get_stats()->decrease_agility(20);
        break;
    }
}

void SetBonusControl::activate_arathi_basin_physical_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->increase_stamina(5);
        break;
    case 3:
        pchar->get_stats()->increase_melee_crit(100);
        pchar->get_stats()->increase_ranged_crit(100);
        break;
    }
}

void SetBonusControl::deactivate_arathi_basin_physical_set_bonuses(const int num_pieces) {
    switch (num_pieces) {
    case 2:
        pchar->get_stats()->decrease_stamina(5);
        break;
    case 3:
        pchar->get_stats()->decrease_melee_crit(100);
        pchar->get_stats()->decrease_ranged_crit(100);
        break;
    }
}
