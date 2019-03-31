#ifndef RESOURCETICK_H
#define RESOURCETICK_H

#include "Spell.h"

class RegeneratingResource;

class ResourceTick : public Spell {
public:
    ResourceTick(Character* pchar, RegeneratingResource *resource);

    void perform_periodic() override;

private:
    RegeneratingResource* resource;

    void spell_effect() override;
};

#endif // RESOURCETICK_H
