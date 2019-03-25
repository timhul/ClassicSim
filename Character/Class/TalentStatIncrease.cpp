#include "TalentStatIncrease.h"

#include "Character.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"
#include "Utils/Check.h"

TalentStatIncrease::TalentStatIncrease(Character *pchar, TalentTree* tree,
                                       const QString& name, const QString& location,
                                       const QString& icon, const int max_points,
                                       const QString& rank_description,
                                       const QVector<QPair<int, int>>& format_values,
                                       QVector<QPair<TalentStat, unsigned>> affected_stats) :
    Talent(pchar, tree, name, location, icon, max_points, rank_description, format_values),
    cstats(pchar->get_stats()),
    affected_stats(std::move(affected_stats))
{}

void TalentStatIncrease::apply_rank_effect() {
    for (auto & affected_stat_pair: affected_stats) {
        TalentStat stat = affected_stat_pair.first;
        unsigned change = affected_stat_pair.second;
        switch (stat) {
        case MeleeHit:
            cstats->increase_melee_hit(change);
            continue;
        case MeleeCrit:
            cstats->increase_melee_crit(change);
            continue;
        case MeleeCritDmgBonus:
            cstats->increase_melee_ability_crit_dmg_mod(change);
            continue;
        case RangedHit:
            cstats->increase_ranged_hit(change);
            continue;
        case RangedCrit:
            cstats->increase_ranged_crit(change);
            continue;
        case RangedDmgMod:
            cstats->increase_total_phys_dmg_for_weapon_type(WeaponTypes::BOW, static_cast<int>(change));
            cstats->increase_total_phys_dmg_for_weapon_type(WeaponTypes::GUN, static_cast<int>(change));
            continue;
        case DmgModAgainstBeast:
            cstats->increase_dmg_vs_type(Target::CreatureType::Beast, static_cast<double>(change) / 100);
            continue;
        case DmgModAgainstDragonkin:
            cstats->increase_dmg_vs_type(Target::CreatureType::Dragonkin, static_cast<double>(change) / 100);
            continue;
        case DmgModAgainstGiant:
            cstats->increase_dmg_vs_type(Target::CreatureType::Giant, static_cast<double>(change) / 100);
            continue;
        case DmgModAgainstHumanoid:
            cstats->increase_dmg_vs_type(Target::CreatureType::Humanoid, static_cast<double>(change) / 100);
            continue;
        case CritDmgModAgainstBeast:
            cstats->increase_crit_dmg_vs_type(Target::CreatureType::Beast, change);
            continue;
        case CritDmgModAgainstDragonkin:
            cstats->increase_crit_dmg_vs_type(Target::CreatureType::Dragonkin, change);
            continue;
        case CritDmgModAgainstGiant:
            cstats->increase_crit_dmg_vs_type(Target::CreatureType::Giant, change);
            continue;
        case CritDmgModAgainstHumanoid:
            cstats->increase_crit_dmg_vs_type(Target::CreatureType::Humanoid, change);
            continue;
        case AgilityMod:
            if (curr_points != 1)
                cstats->remove_agility_mod((curr_points - 1) * static_cast<int>(change));
            cstats->add_agility_mod(static_cast<int>(change) * static_cast<int>(curr_points));
            continue;
        case StrengthMod:
            if (curr_points != 1)
                cstats->remove_strength_mod((curr_points - 1) * static_cast<int>(change));
            cstats->add_strength_mod(static_cast<int>(change) * static_cast<int>(curr_points));
            continue;
        case IntellectMod:
            if (curr_points != 1)
                cstats->remove_intellect_mod((curr_points - 1) * static_cast<int>(change));
            cstats->add_intellect_mod(static_cast<int>(change) * static_cast<int>(curr_points));
            continue;
        case OneHandMeleeDmg:
        case TwoHandMeleeDmg:
        case Defense:
        case Parry:
        case ArmorModFromItems:
        case ArcaneHit:
        case FireHit:
        case FrostHit:
        case HolyHit:
        case NatureHit:
        case ShadowHit:
        case FireCrit:
        case ShadowDmgMod:
        case TargetResistanceReduction:
        case MaxManaMod:
        case BaseManaRegenWhileCasting:
        case SpellDmgMod:
            continue;
        }
    }
}

void TalentStatIncrease::remove_rank_effect() {
    for (auto & affected_stat_pair: affected_stats) {
        TalentStat stat = affected_stat_pair.first;
        unsigned change = affected_stat_pair.second;
        switch (stat) {
        case MeleeHit:
            cstats->decrease_melee_hit(change);
            continue;
        case MeleeCrit:
            cstats->decrease_melee_crit(change);
            continue;
        case MeleeCritDmgBonus:
            cstats->decrease_melee_ability_crit_dmg_mod(change);
            continue;
        case RangedHit:
            cstats->decrease_ranged_hit(change);
            continue;
        case RangedCrit:
            cstats->decrease_ranged_crit(change);
            continue;
        case RangedDmgMod:
            cstats->decrease_total_phys_dmg_for_weapon_type(WeaponTypes::BOW, static_cast<int>(change));
            cstats->decrease_total_phys_dmg_for_weapon_type(WeaponTypes::GUN, static_cast<int>(change));
            continue;
        case DmgModAgainstBeast:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Beast, static_cast<double>(change) / 100);
            continue;
        case DmgModAgainstDragonkin:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Dragonkin, static_cast<double>(change) / 100);
            continue;
        case DmgModAgainstGiant:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Giant, static_cast<double>(change) / 100);
            continue;
        case DmgModAgainstHumanoid:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Humanoid, static_cast<double>(change) / 100);
            continue;
        case CritDmgModAgainstBeast:
            cstats->decrease_crit_dmg_vs_type(Target::CreatureType::Beast, change);
            continue;
        case CritDmgModAgainstDragonkin:
            cstats->decrease_crit_dmg_vs_type(Target::CreatureType::Dragonkin, change);
            continue;
        case CritDmgModAgainstGiant:
            cstats->decrease_crit_dmg_vs_type(Target::CreatureType::Giant, change);
            continue;
        case CritDmgModAgainstHumanoid:
            cstats->decrease_crit_dmg_vs_type(Target::CreatureType::Humanoid, change);
            continue;
        case AgilityMod:
            cstats->remove_agility_mod((curr_points + 1) * static_cast<int>(change));
            cstats->add_agility_mod(static_cast<int>(change) * static_cast<int>(curr_points));
            continue;
        case StrengthMod:
            cstats->remove_strength_mod((curr_points + 1) * static_cast<int>(change));
            cstats->add_strength_mod(static_cast<int>(change) * static_cast<int>(curr_points));
            continue;
        case IntellectMod:
            cstats->remove_intellect_mod((curr_points + 1) * static_cast<int>(change));
            cstats->add_intellect_mod(static_cast<int>(change) * static_cast<int>(curr_points));
            continue;
        case OneHandMeleeDmg:
        case TwoHandMeleeDmg:
        case Defense:
        case Parry:
        case ArmorModFromItems:
        case ArcaneHit:
        case FireHit:
        case FrostHit:
        case HolyHit:
        case NatureHit:
        case ShadowHit:
        case FireCrit:
        case ShadowDmgMod:
        case TargetResistanceReduction:
        case MaxManaMod:
        case BaseManaRegenWhileCasting:
        case SpellDmgMod:
            continue;
        }
    }
}
