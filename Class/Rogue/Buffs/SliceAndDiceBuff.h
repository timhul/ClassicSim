#pragma once

#include "SelfBuff.h"

#include <QVector>

class SliceAndDiceBuff: public SelfBuff {
public:
    SliceAndDiceBuff(Character* pchar);

    void update_duration(const unsigned combo_points);
    void change_duration_modifier(const int);

private:
    QVector<int> durations;
    QVector<double> imp_snd_duration_modifiers;
    double imp_snd_modifier;


    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
