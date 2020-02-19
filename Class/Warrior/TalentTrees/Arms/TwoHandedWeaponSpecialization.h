#pragma once

#include <QSet>
#include <QVector>

#include "Talent.h"

class TalentTree;

class TwoHandedWeaponSpecialization : public Talent {
public:
    TwoHandedWeaponSpecialization(Character* pchar, TalentTree* tree);
    ~TwoHandedWeaponSpecialization() override;

private:
    QVector<int> talent_ranks;
    QSet<int> affected_weapon_types;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};
