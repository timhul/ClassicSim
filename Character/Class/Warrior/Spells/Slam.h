#ifndef SLAM_H
#define SLAM_H

#include "Spell.h"
#include <QVector>

class Warrior;

class Slam: public Spell {
public:
    Slam(Character* pchar);

    void increase_effect_via_talent() override;
    void decrease_effect_via_talent() override;

    void perform_periodic() override;

    double get_cast_time() const;

protected:
private:
    Warrior* warr;
    int cast_time;
    QVector<int> talent_ranks;

    void spell_effect() override;
};

#endif // SLAM_H
