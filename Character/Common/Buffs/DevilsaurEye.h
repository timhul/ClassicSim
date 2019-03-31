#ifndef DEVILSAUREYE_H
#define DEVILSAUREYE_H

#include "Buff.h"

class DevilsaurEye: public Buff {
public:
    DevilsaurEye(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // DEVILSAUREYE_H
