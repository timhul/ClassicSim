#ifndef ELIXIROFBRUTEFORCE_H
#define ELIXIROFBRUTEFORCE_H

#include "ExternalBuff.h"

class ElixirOfBruteForce: public ExternalBuff {
public:
    ElixirOfBruteForce(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // ELIXIROFBRUTEFORCE_H
