#ifndef RALLYINGCRYOFTHEDRAGONSLAYER_H
#define RALLYINGCRYOFTHEDRAGONSLAYER_H

#include "ExternalBuff.h"

class RallyingCryOfTheDragonslayer: public ExternalBuff {
public:
    RallyingCryOfTheDragonslayer(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // RALLYINGCRYOFTHEDRAGONSLAYER_H
