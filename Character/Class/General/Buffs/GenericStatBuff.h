#ifndef ATTACKPOWERBUFF_H
#define ATTACKPOWERBUFF_H

#include "Buff.h"
#include "ItemStatsEnum.h"

class GenericStatBuff: public Buff {
public:
    GenericStatBuff(Character* pchar,
                    const QString& name,
                    const QString& icon,
                    const int duration,
                    const ItemStats stat_type,
                    const int stat_value);

private:
    ItemStats stat_type;
    int stat_value;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // ATTACKPOWERBUFF_H
