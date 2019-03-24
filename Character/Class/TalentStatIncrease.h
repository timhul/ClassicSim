#ifndef TALENTSTATINCREASE_H
#define TALENTSTATINCREASE_H

#include "Talent.h"

enum TalentStat {
    MeleeHit = 0,
    MeleeCrit,
    MeleeCritDmgBonus,
    RangedHit,
    RangedCrit,
    RangedCritDmgBonus,
    RangedDmgMod,
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
    ArcaneHit,
    FireHit,
    FrostHit,
    HolyHit,
    NatureHit,
    ShadowHit,
    FireCrit,
    ShadowDmgMod,
    TargetResistanceReduction,
    MaxManaMod,
    BaseManaRegenWhileCasting,
    SpellDmgMod
};

class CharacterStats;
class TalentTree;

class TalentStatIncrease: public Talent {
public:
    TalentStatIncrease(Character *pchar,
                       TalentTree* tree,
                       QString name,
                       QString location,
                       QString icon,
                       int max_points,
                       QString rank_description,
                       QVector<QPair<int, int>> format_values,
                       QVector<QPair<int, TalentStat>> affected_stats);
    ~TalentStatIncrease() override = default;

private:
    QVector<QPair<TalentStat, unsigned>> affected_stats;
    CharacterStats* cstats;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // TALENTSTATINCREASE_H
