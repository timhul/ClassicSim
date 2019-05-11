#ifndef JOMGABBAR_H
#define JOMGABBAR_H

#include "Buff.h"

class JomGabbar: public Buff {
public:
    JomGabbar(Character* pchar);

private:
    unsigned curr_stacks;
    const unsigned max_stacks;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void buff_effect_when_refreshed() override;
    void reset_effect() override;
};

#endif // JOMGABBAR_H
