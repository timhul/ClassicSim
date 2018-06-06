#ifndef SONGFLOWERSERENADE_H
#define SONGFLOWERSERENADE_H

#include "ExternalBuff.h"

class SongflowerSerenade: public ExternalBuff {
public:
    SongflowerSerenade(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // SONGFLOWERSERENADE_H
