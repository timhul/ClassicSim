#include "ItemStatsEnum.h"

ItemStats get_item_stats_from_string(const QString& item_stat)  {
    if (item_stat == "ATTACK_SPEED")
        return ItemStats::AttackSpeedPercent;
    else if (item_stat == "MELEE_ATTACK_SPEED")
        return ItemStats::MeleeAttackSpeedPercent;
    else if (item_stat == "RANGED_ATTACK_SPEED")
        return ItemStats::RangedAttackSpeedPercent;
    else if (item_stat == "CASTING_SPEED")
        return ItemStats::CastingSpeedPercent;
    else if (item_stat == "ATTACK_POWER")
        return ItemStats::AttackPower;
    else if (item_stat == "STRENGTH")
        return ItemStats::Strength;
    else if (item_stat == "AGILITY")
        return ItemStats::Agility;
    else if (item_stat == "INTELLECT")
        return ItemStats::Intellect;
    else if (item_stat == "STAMINA")
        return ItemStats::Stamina;
    else if (item_stat == "SPIRIT")
        return ItemStats::Spirit;
    else if (item_stat == "SPELL_DAMAGE")
        return ItemStats::SpellDamage;
    else if (item_stat == "MANA_PER_5")
        return ItemStats::ManaPer5;
    else if (item_stat == "MANA_SKILL_REDUCTION")
        return ItemStats::ManaSkillReduction;
    else if (item_stat == "SPELL_PENETRATION")
        return ItemStats::SpellPenetration;
    else {
        return ItemStats::Armor;
        check(false, QString("Unsupported stat use type '%1'").arg(item_stat).toStdString());
    }
}
