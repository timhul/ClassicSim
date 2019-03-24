#include "TalentStatIncrease.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Utils/Check.h"

TalentStatIncrease::TalentStatIncrease(Character *pchar, TalentTree* tree,
                                       QString name, QString location, QString icon, int max_points,
                                       QString rank_description, QVector<QPair<int, int>> format_values,
                                       QVector<QPair<int, TalentStat> > affected_stats) :
    Talent(pchar, tree, name, location, icon, max_points, rank_description, format_values),
    cstats(pchar->get_stats())
{
    for (auto & affected_stat_pair: affected_stats) {
        check((affected_stat_pair.first < format_values.size()),
              QString("Out of range when constructing '%1'").arg(name).toStdString());

        this->affected_stats.append({affected_stat_pair.second,
                                     static_cast<unsigned>(format_values[affected_stat_pair.first].second)});
    }
}

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
            pchar->increase_ability_crit_dmg_mod(change);
            continue;
        case RangedHit:
            cstats->increase_ranged_hit(change);
            continue;
        case RangedCrit:
            cstats->increase_ranged_crit(change);
            continue;
        case RangedCritDmgBonus:
        case RangedDmgMod:
            continue;
        case DmgModAgainstBeast:
            cstats->increase_dmg_vs_type(Target::CreatureType::Beast, change);
            continue;
        case DmgModAgainstDragonkin:
            cstats->increase_dmg_vs_type(Target::CreatureType::Dragonkin, change);
            continue;
        case DmgModAgainstGiant:
            cstats->increase_dmg_vs_type(Target::CreatureType::Giant, change);
            continue;
        case DmgModAgainstHumanoid:
            cstats->increase_dmg_vs_type(Target::CreatureType::Humanoid, change);
            continue;
        case CritDmgModAgainstBeast:
        case CritDmgModAgainstDragonkin:
        case CritDmgModAgainstGiant:
        case CritDmgModAgainstHumanoid:
        case AgilityMod:
        case StrengthMod:
        case IntellectMod:
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
            pchar->decrease_ability_crit_dmg_mod(change);
            continue;
        case RangedHit:
            cstats->decrease_ranged_hit(change);
            continue;
        case RangedCrit:
            cstats->decrease_ranged_crit(change);
            continue;
        case RangedCritDmgBonus:
        case RangedDmgMod:
            continue;
        case DmgModAgainstBeast:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Beast, change);
            continue;
        case DmgModAgainstDragonkin:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Dragonkin, change);
            continue;
        case DmgModAgainstGiant:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Giant, change);
            continue;
        case DmgModAgainstHumanoid:
            cstats->decrease_dmg_vs_type(Target::CreatureType::Humanoid, change);
            continue;
        case CritDmgModAgainstBeast:
        case CritDmgModAgainstDragonkin:
        case CritDmgModAgainstGiant:
        case CritDmgModAgainstHumanoid:
        case AgilityMod:
        case StrengthMod:
        case IntellectMod:
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
