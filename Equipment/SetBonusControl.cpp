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
#include "Evocation.h"
#include "ExposeWeaknessProc.h"
#include "Hemorrhage.h"
#include "Hunter.h"
#include "HunterSpells.h"
#include "InstantPoison.h"
#include "InstantSpellProc.h"
#include "ItemNamespace.h"
#include "MageSpells.h"
#include "MultiShot.h"
#include "Pet.h"
#include "RapidFire.h"
#include "RapidFireBuff.h"
#include "ResourceGainProc.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SetBonusFileReader.h"
#include "SinisterStrike.h"
#include "SliceAndDice.h"
#include "SpellRankGroup.h"
#include "Utils/Check.h"

SetBonusControl::SetBonusControl(EquipmentDb* equipment_db, Character* pchar) : equipment_db(equipment_db), pchar(pchar) {
    SetBonusFileReader().read_set_bonuses("set_bonuses.xml", possible_set_items, set_bonus_tooltips, set_bonus_effects);
}

SetBonusControl::~SetBonusControl() {
    for (const auto& proc : active_procs) {
        if (proc->is_enabled())
            proc->disable_proc();
        delete proc;
    }
}

void SetBonusControl::equip_item(const int item_id) {
    if (!possible_set_items.contains(item_id))
        return;

    const QString set_name = possible_set_items[item_id];
    current_set_items[item_id] = set_name;
    const int num_pieces = get_num_equipped_pieces_for_set(set_name);

    if (set_bonus_effects.contains(set_name) && set_bonus_effects[set_name].contains(num_pieces))
        pchar->get_stats()->increase_stat(set_bonus_effects[set_name][num_pieces].first, set_bonus_effects[set_name][num_pieces].second);

    if (set_name == "Darkmantle Armor") {
        switch (num_pieces) {
        case 4:
            if (!active_procs.contains("DARKMANTLE_GAIN"))
                active_procs["DARKMANTLE_GAIN"] = new ResourceGainProc(pchar, "Darkmantle 4 set", "Assets/items/Inv_helmet_41.png",
                                                                        {ProcInfo::MainhandSwing, ProcInfo::OffhandSwing},
                                                                        0.035, ResourceType::Energy, 35, 35);
            active_procs["DARKMANTLE_GAIN"]->enable_proc();
            break;
        }
    } else if (set_name == "Shadowcraft Armor") {
        switch (num_pieces) {
        case 6:
            if (!active_procs.contains("SHADOWCRAFT_GAIN"))
                active_procs["SHADOWCRAFT_GAIN"] = new ResourceGainProc(pchar, "Shadowcraft 6 set", "Assets/items/Inv_helmet_41.png",
                                                                        {ProcInfo::MainhandSwing, ProcInfo::OffhandSwing},
                                                                        0.035, ResourceType::Energy, 35, 35);
            active_procs["SHADOWCRAFT_GAIN"]->enable_proc();
            break;
        }
    } else if (set_name == "Nightslayer Armor") {
        switch (num_pieces) {
        case 5:
            static_cast<Rogue*>(pchar)->get_energy()->max += 10;
            break;
        }
    } else if (set_name == "Bloodfang Armor") {
        switch (num_pieces) {
        case 3: {
            static_cast<Rogue*>(pchar)->get_mh_instant_poison()->activate_set_bonus(set_name, num_pieces);
            static_cast<Rogue*>(pchar)->get_oh_instant_poison()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    } else if (set_name == "Deathdealer's Embrace") {
        switch (num_pieces) {
        case 5:
            activate_spell_rank_group("Eviscerate", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Bonescythe Armor") {
        switch (num_pieces) {
        case 4:
            activate_spell_rank_group("Backstab", set_name, num_pieces);
            activate_spell_rank_group("Hemorrhage", set_name, num_pieces);
            activate_spell_rank_group("Sinister Strike", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Zanzil's Concentration") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->increase_spell_hit(100);
            pchar->get_stats()->increase_base_spell_damage(6);
            break;
        }
    } else if (set_name == "Trappings of the Unseen Path") {
        switch (num_pieces) {
        case 3:
            static_cast<Hunter*>(pchar)->get_pet()->increase_damage_modifier(3);
            break;
        }
    } else if (set_name == "Beaststalker Armor") {
        switch (num_pieces) {
        case 6:
            if (!active_procs.contains("BEASTSTALKER_DRAIN"))
                active_procs["BEASTSTALKER_DRAIN"] = new ResourceGainProc(pchar, "Beaststalker 6 set", "Assets/items/Inv_belt_28.png",
                                                                          {ProcInfo::RangedAutoShot}, 0.04, ResourceType::Mana, 200, 200);
            active_procs["BEASTSTALKER_DRAIN"]->enable_proc();
            break;
        }
    } else if (set_name == "Beastmaster Armor") {
        switch (num_pieces) {
        case 4:
            if (!active_procs.contains("BEASTMASTER_DRAIN"))
                active_procs["BEASTMASTER_DRAIN"] = new ResourceGainProc(pchar, "Beastmaster 4 set", "Assets/items/Inv_belt_28.png",
                                                                         {ProcInfo::RangedAutoShot}, 0.04, ResourceType::Mana, 200, 200);
            active_procs["BEASTMASTER_DRAIN"]->enable_proc();
            break;
        }
    } else if (set_name == "Giantstalker Armor") {
        switch (num_pieces) {
        case 8:
            activate_spell_rank_group("Multi-Shot", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Dragonstalker Armor") {
        switch (num_pieces) {
        case 3: {
            // TODO: The set bonus is only applied to the max rank of Aspect of the Hawk.
            auto aspect = static_cast<AspectOfTheHawk*>(
                pchar->get_spells()->get_spell_rank_group_by_name("Aspect of the Hawk")->get_max_available_spell_rank());
            aspect->get_aspect_of_the_hawk_buff()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        case 8: {
            auto spells = static_cast<HunterSpells*>(pchar->get_spells());
            spells->get_expose_weakness_proc()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    } else if (set_name == "Striker's Garb") {
        switch (num_pieces) {
        case 5:
            activate_spell_rank_group("Rapid Fire", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Cryptstalker Armor") {
        switch (num_pieces) {
        case 2: {
            auto rapid_fire = static_cast<RapidFire*>(pchar->get_spells()->get_spell_rank_group_by_name("Rapid Fire")->get_max_available_spell_rank());
            rapid_fire->get_rapid_fire_buff()->activate_set_bonus(set_name, num_pieces);
            break;
        }
        case 4:
            pchar->get_stats()->increase_melee_ap(50);
            pchar->get_stats()->increase_ranged_ap(50);
            static_cast<Hunter*>(pchar)->get_pet()->increase_attack_power(50);
            break;
        case 6:
            activate_spell_rank_group("Aimed Shot", set_name, num_pieces);
            activate_spell_rank_group("Auto Shot", set_name, num_pieces);
            activate_spell_rank_group("Multi-Shot", set_name, num_pieces);
            break;
        case 8:
            activate_spell_rank_group("Aimed Shot", set_name, num_pieces);
            activate_spell_rank_group("Multi-Shot", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Netherwind Regalia") {
        switch (num_pieces) {
        case 8: {
            Proc* proc = static_cast<MageSpells*>(pchar->get_spells())->get_t2_8piece_proc();
            proc->enable();
            proc->enable_proc();
            break;
        }
        }
    } else if (set_name == "Enigma Vestments") {
        switch (num_pieces) {
        case 5: {
            Buff* buff = static_cast<MageSpells*>(pchar->get_spells())->get_enigma_5p_buff();
            buff->enable_buff();
            break;
        }
        }
    } else if (set_name == "Frostfire Regalia") {
        switch (num_pieces) {
        case 2:
            activate_spell_rank_group("Evocation", set_name, num_pieces);
            break;
        case 6: {
            Buff* buff = static_cast<MageSpells*>(pchar->get_spells())->get_t3_6piece_buff();
            dynamic_cast<SetBonusRequirer*>(buff)->activate_set_bonus(set_name, num_pieces);
            Proc* proc = static_cast<MageSpells*>(pchar->get_spells())->get_t3_6piece_proc();
            proc->enable();
            proc->enable_proc();
            break;
        }
        }
    } else if (set_name == "Regalia of Undead Cleansing") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->increase_magic_damage_mod_vs_type(Target::CreatureType::Undead, 2);
            break;
        }
    } else if (set_name == "Emblems of Veiled Shadows") {
        switch (num_pieces) {
        case 3:
            activate_spell_rank_group("Slice and Dice", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Stormshroud Armor") {
        switch (num_pieces) {
        case 2:
            if (!active_procs.contains("STORMSHROUD_2P_GAIN"))
                active_procs["STORMSHROUD_2P_GAIN"] = new InstantSpellProc(pchar, "Stormshroud 2 set", "Assets/items/Inv_shoulder_05.png",
                                                                           {ProcInfo::MainhandSpell, ProcInfo::MainhandSwing, ProcInfo::OffhandSwing},
                                                                           0.05, MagicSchool::Nature, 15, 25, 0.0, ConsumeCharge::No);
            active_procs["STORMSHROUD_2P_GAIN"]->enable_proc();
            break;
        case 3:
            if (!active_procs.contains("STORMSHROUD_3P_GAIN"))
                active_procs["STORMSHROUD_3P_GAIN"] = new ResourceGainProc(pchar, "Stormshroud 3 set", "Assets/items/Inv_shoulder_05.png",
                                                                           {ProcInfo::MainhandSpell, ProcInfo::MainhandSwing, ProcInfo::OffhandSwing},
                                                                           0.02, ResourceType::Energy, 30, 30);
            active_procs["STORMSHROUD_3P_GAIN"]->enable_proc();
            break;
        }
    }
}

void SetBonusControl::unequip_item(const int item_id) {
    if (!current_set_items.contains(item_id))
        return;

    const QString set_name = current_set_items[item_id];
    const int num_pieces = get_num_equipped_pieces_for_set(set_name);
    current_set_items.take(item_id);

    if (set_bonus_effects.contains(set_name) && set_bonus_effects[set_name].contains(num_pieces))
        pchar->get_stats()->decrease_stat(set_bonus_effects[set_name][num_pieces].first, set_bonus_effects[set_name][num_pieces].second);

    if (set_name == "Darkmantle Armor") {
        switch (num_pieces) {
        case 4:
            active_procs["DARKMANTLE_GAIN"]->disable_proc();
            break;
        }
    } else if (set_name == "Shadowcraft Armor") {
        switch (num_pieces) {
        case 6:
            active_procs["SHADOWCRAFT_GAIN"]->disable_proc();
            break;
        }
    } else if (set_name == "Nightslayer Armor") {
        switch (num_pieces) {
        case 5:
            static_cast<Rogue*>(pchar)->get_energy()->max -= 10;
            break;
        }
    } else if (set_name == "Bloodfang Armor") {
        switch (num_pieces) {
        case 3: {
            static_cast<Rogue*>(pchar)->get_mh_instant_poison()->deactivate_set_bonus(set_name, num_pieces);
            static_cast<Rogue*>(pchar)->get_oh_instant_poison()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    } else if (set_name == "Deathdealer's Embrace") {
        switch (num_pieces) {
        case 5:
            deactivate_spell_rank_group("Eviscerate", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Bonescythe Armor") {
        switch (num_pieces) {
        case 4:
            deactivate_spell_rank_group("Backstab", set_name, num_pieces);
            deactivate_spell_rank_group("Hemorrhage", set_name, num_pieces);
            deactivate_spell_rank_group("Sinister Strike", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Zanzil's Concentration") {
        switch (num_pieces) {
        case 2:
            pchar->get_stats()->decrease_spell_hit(100);
            pchar->get_stats()->decrease_base_spell_damage(6);
            break;
        }
    } else if (set_name == "Trappings of the Unseen Path") {
        switch (num_pieces) {
        case 3:
            static_cast<Hunter*>(pchar)->get_pet()->decrease_damage_modifier(3);
            break;
        }
    } else if (set_name == "Beaststalker Armor") {
        switch (num_pieces) {
        case 6:
            active_procs["BEASTSTALKER_DRAIN"]->disable_proc();
            break;
        }
    } else if (set_name == "Beastmaster Armor") {
        switch (num_pieces) {
        case 4:
            active_procs["BEASTMASTER_DRAIN"]->disable_proc();
            break;
        }
    } else if (set_name == "Giantstalker Armor") {
        switch (num_pieces) {
        case 8:
            deactivate_spell_rank_group("Multi-Shot", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Dragonstalker Armor") {
        switch (num_pieces) {
        case 3: {
            // TODO: The set bonus is only applied to the max rank of Aspect of the Hawk.
            auto aspect = static_cast<AspectOfTheHawk*>(
                pchar->get_spells()->get_spell_rank_group_by_name("Aspect of the Hawk")->get_max_available_spell_rank());
            aspect->get_aspect_of_the_hawk_buff()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        case 8: {
            auto spells = static_cast<HunterSpells*>(pchar->get_spells());
            spells->get_expose_weakness_proc()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        }
    } else if (set_name == "Striker's Garb") {
        switch (num_pieces) {
        case 5:
            deactivate_spell_rank_group("Rapid Fire", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Cryptstalker Armor") {
        switch (num_pieces) {
        case 2: {
            auto rapid_fire = static_cast<RapidFire*>(pchar->get_spells()->get_spell_rank_group_by_name("Rapid Fire")->get_max_available_spell_rank());
            rapid_fire->get_rapid_fire_buff()->deactivate_set_bonus(set_name, num_pieces);
            break;
        }
        case 4:
            pchar->get_stats()->decrease_melee_ap(50);
            pchar->get_stats()->decrease_ranged_ap(50);
            static_cast<Hunter*>(pchar)->get_pet()->decrease_attack_power(50);
            break;
        case 6:
            deactivate_spell_rank_group("Aimed Shot", set_name, num_pieces);
            deactivate_spell_rank_group("Auto Shot", set_name, num_pieces);
            deactivate_spell_rank_group("Multi-Shot", set_name, num_pieces);
            break;
        case 8:
            deactivate_spell_rank_group("Aimed Shot", set_name, num_pieces);
            deactivate_spell_rank_group("Multi-Shot", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Netherwind Regalia") {
        switch (num_pieces) {
        case 8: {
            Proc* proc = static_cast<MageSpells*>(pchar->get_spells())->get_t2_8piece_proc();
            proc->disable_proc();
            proc->disable();
            break;
        }
        }
    } else if (set_name == "Enigma Vestments") {
        switch (num_pieces) {
        case 5: {
            Buff* buff = static_cast<MageSpells*>(pchar->get_spells())->get_enigma_5p_buff();
            buff->disable_buff();
            break;
        }
        }
    } else if (set_name == "Frostfire Regalia") {
        switch (num_pieces) {
        case 2:
            deactivate_spell_rank_group("Evocation", set_name, num_pieces);
            break;
        case 6: {
            Buff* buff = static_cast<MageSpells*>(pchar->get_spells())->get_t3_6piece_buff();
            dynamic_cast<SetBonusRequirer*>(buff)->deactivate_set_bonus(set_name, num_pieces);
            Proc* proc = static_cast<MageSpells*>(pchar->get_spells())->get_t3_6piece_proc();
            proc->disable_proc();
            proc->disable();
        }
        }
    } else if (set_name == "Regalia of Undead Cleansing") {
        switch (num_pieces) {
        case 3:
            pchar->get_stats()->decrease_magic_damage_mod_vs_type(Target::CreatureType::Undead, 2);
            break;
        }
    } else if (set_name == "Emblems of Veiled Shadows") {
        switch (num_pieces) {
        case 3:
            deactivate_spell_rank_group("Slice and Dice", set_name, num_pieces);
            break;
        }
    } else if (set_name == "Stormshroud Armor") {
        switch (num_pieces) {
        case 2:
            active_procs["STORMSHROUD_2P_GAIN"]->disable_proc();
            break;
        case 3:
            active_procs["STORMSHROUD_3P_GAIN"]->disable_proc();
            break;
        }
    }
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
            item_names_and_equipped.append({equipment_db->get_name_for_item_id(it.key()), current_set_items.contains(it.key())});
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
    for (const auto& tooltip : set_bonus_tooltips[set_name])
        tooltips_and_active.append({tooltip.second, tooltip.first <= num_equipped});

    return tooltips_and_active;
}

int SetBonusControl::get_num_equipped_pieces_for_set(const QString& set_name) const {
    int num_set_pieces = 0;
    for (const auto& equipped_set : current_set_items) {
        if (equipped_set == set_name)
            ++num_set_pieces;
    }

    return num_set_pieces;
}

void SetBonusControl::activate_spell_rank_group(const QString& spell_name, const QString& set_name, const int num_pieces) {
    const auto spells = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
    check((spells != nullptr), QString("Failed to find SpellRankGroup for %1 when activating set bonus").arg(spell_name).toStdString());

    for (const auto& spell : spells->spell_group)
        dynamic_cast<SetBonusRequirer*>(spell)->activate_set_bonus(set_name, num_pieces);
}

void SetBonusControl::deactivate_spell_rank_group(const QString& spell_name, const QString& set_name, const int num_pieces) {
    const auto spells = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
    check((spells != nullptr), QString("Failed to find SpellRankGroup for %1 when deactivating set bonus").arg(spell_name).toStdString());

    for (const auto& spell : spells->spell_group)
        dynamic_cast<SetBonusRequirer*>(spell)->deactivate_set_bonus(set_name, num_pieces);
}
