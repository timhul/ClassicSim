#pragma once

#include "Spell.h"

class RegeneratingResource;

class ResourceTick : public Spell {
public:
    ResourceTick(Character* pchar, RegeneratingResource *resource);
    ~ResourceTick() override;

    void perform_periodic() override;

private:
    RegeneratingResource* resource;

    void spell_effect() override;
};
