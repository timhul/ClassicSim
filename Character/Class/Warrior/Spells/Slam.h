#ifndef SLAM_H
#define SLAM_H

#include "Spell.h"
#include "TalentRequirer.h"
#include <QVector>

class Warrior;

class Slam: public Spell, public TalentRequirer {
public:
    Slam(Character* pchar);

    void perform_periodic() override;

    double get_cast_time() const;

protected:
private:
    friend class ImprovedSlam;

    Warrior* warr;
    int cast_time;
    QVector<int> talent_ranks;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // SLAM_H
