#ifndef RAGE_H
#define RAGE_H

#include "Resource.h"

class Rage: public Resource {
public:
    Rage();

    void gain_resource(const unsigned) override;
    void lose_resource(const unsigned) override;
    void reset_resource() override;

    friend class Druid;
    friend class Warrior;
};

#endif // RAGE_H
