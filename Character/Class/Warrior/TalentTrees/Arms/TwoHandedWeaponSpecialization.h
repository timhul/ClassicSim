#ifndef TWOHANDEDWEAPONSPECIALIZATION_H
#define TWOHANDEDWEAPONSPECIALIZATION_H

#include "Talent.h"

#include <QVector>
#include <QSet>

class TalentTree;

class TwoHandedWeaponSpecialization: public Talent {
    Q_OBJECT
public:
    TwoHandedWeaponSpecialization(Character *pchar, TalentTree* tree);
    ~TwoHandedWeaponSpecialization() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
    QVector<int> talent_ranks;
    QSet<int> affected_weapon_types;
};

#endif // TWOHANDEDWEAPONSPECIALIZATION_H
