#ifndef AIMEDSHOT_H
#define AIMEDSHOT_H

#include "SpellCastingTime.h"

class AimedShot: public SpellCastingTime {
public:
    AimedShot(Character* pchar);

private:
    QVector<double> talent_ranks;

    void spell_effect() override;
    void complete_cast_effect() override;
};


#endif // AIMEDSHOT_H
