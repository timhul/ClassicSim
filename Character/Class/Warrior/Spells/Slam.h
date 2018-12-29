#ifndef SLAM_H
#define SLAM_H

#include <QVector>

#include "SpellCastingTime.h"
#include "TalentRequirer.h"

class Warrior;

class Slam: public SpellCastingTime, public TalentRequirer {
public:
    Slam(Character* pchar);

protected:
private:
    friend class ImprovedSlam;

    Warrior* warr;
    QVector<int> talent_ranks;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void complete_cast_effect() override;
};

#endif // SLAM_H
