#ifndef SLAM_H
#define SLAM_H

#include "SpellCastingTime.h"
#include "TalentRequirer.h"
#include <QVector>

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

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;

    void complete_cast_effect() override;
};

#endif // SLAM_H
