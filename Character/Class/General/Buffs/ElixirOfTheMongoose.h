#ifndef ELIXIROFTHEMONGOOSE_H
#define ELIXIROFTHEMONGOOSE_H

#include "ExternalBuff.h"

class ElixirOfTheMongoose: public ExternalBuff {
public:
    ElixirOfTheMongoose(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // ELIXIROFTHEMONGOOSE_H
