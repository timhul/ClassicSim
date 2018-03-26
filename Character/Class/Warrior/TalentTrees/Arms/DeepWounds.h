#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Talent.h"

class DeepWounds: public Talent {
    Q_OBJECT
public:
    DeepWounds(Character* pchar);
    virtual ~DeepWounds();

private:
};

#endif // DEEPWOUNDS_H
