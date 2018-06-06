#ifndef ELIXIROFGIANTS_H
#define ELIXIROFGIANTS_H

#include "ExternalBuff.h"

class ElixirOfGiants: public ExternalBuff {
public:
    ElixirOfGiants(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // ELIXIROFGIANTS_H
