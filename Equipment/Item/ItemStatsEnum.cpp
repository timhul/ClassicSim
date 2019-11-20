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
    else if (item_stat == "CRIT_CHANCE")
        return ItemStats::CritChance;
    else if (item_stat == "HIT_CHANCE")
        return ItemStats::HitChance;
    else if (item_stat == "ATTACK_POWER")
        return ItemStats::AttackPower;
    else if (item_stat == "ATTACK_POWER_BEAST")
        return ItemStats::APVersusBeast;
    else if (item_stat == "ATTACK_POWER_DEMON")
        return ItemStats::APVersusDemon;
    else if (item_stat == "ATTACK_POWER_DRAGONKIN")
        return ItemStats::APVersusDragonkin;
    else if (item_stat == "ATTACK_POWER_ELEMENTAL")
        return ItemStats::APVersusElemental;
    else if (item_stat == "ATTACK_POWER_GIANT")
        return ItemStats::APVersusGiant;
    else if (item_stat == "ATTACK_POWER_HUMANOID")
        return ItemStats::APVersusHumanoid;
    else if (item_stat == "ATTACK_POWER_MECHANICAL")
        return ItemStats::APVersusMechanical;
    else if (item_stat == "ATTACK_POWER_UNDEAD")
        return ItemStats::APVersusUndead;
    else if (item_stat == "SWORD_SKILL")
        return ItemStats::SkillSword;
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
    else if (item_stat == "SPELL_CRIT_CHANCE")
        return ItemStats::SpellCrit;
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
