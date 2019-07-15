#pragma once

#include "Talent.h"

enum TalentStat {
    MeleeHit = 0,
    MeleeCrit,
    MeleeCritDmgBonus,
    RangedHit,
    RangedCrit,
    RangedDmgMod,
    PetDmgMod,
    PetCritChance,
    PetFocusGain,
    AttackPower,
    DmgModAgainstBeast,
    DmgModAgainstDragonkin,
    DmgModAgainstGiant,
    DmgModAgainstHumanoid,
    CritDmgModAgainstBeast,
    CritDmgModAgainstDragonkin,
    CritDmgModAgainstGiant,
    CritDmgModAgainstHumanoid,
    AgilityMod,
    StrengthMod,
    IntellectMod,
    OneHandMeleeDmg,
    TwoHandMeleeDmg,
    Defense,
    Parry,
    ArmorModFromItems,
    SpellHit,
    ArcaneHit,
    FireHit,
    FrostHit,
    HolyHit,
    NatureHit,
    ShadowHit,
    FireCrit,
    FireDmgMod,
    FrostDmgMod,
    ShadowDmgMod,
    TargetResistanceReduction,
    MaxManaMod,
    BaseManaRegenWhileCasting,
    SpellDmgMod,
};

class CharacterStats;
class TalentTree;

class TalentStatIncrease: public Talent {
public:
    TalentStatIncrease(Character *pchar,
                       TalentTree* tree,
                       const QString& name,
                       const QString& location,
                       const QString& icon,
                       const unsigned max_points,
                       const QString& rank_description,
                       const QVector<QPair<unsigned, unsigned>>& format_values,
                       QVector<QPair<TalentStat, unsigned>> affected_stats);
    ~TalentStatIncrease() override = default;

private:
    CharacterStats* cstats;
    QVector<QPair<TalentStat, unsigned>> affected_stats;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
