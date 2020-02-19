#pragma once

#include <QVector>

#include "SelfBuff.h"

enum class ItemStats : int;

class GenericStatBuff : public SelfBuff {
public:
    GenericStatBuff(
        Character* pchar, const QString& name, const QString& icon, const int duration, const QVector<QPair<ItemStats, unsigned>>& stat_type_values);

private:
    const QVector<QPair<ItemStats, unsigned>> stat_type_values;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
