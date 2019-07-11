#pragma once

#include "Resource.h"

class Character;
class ResourceTick;

class RegeneratingResource: public Resource {
public:
    RegeneratingResource(Character* pchar);
    ~RegeneratingResource() override;

    void gain_resource(const unsigned) override;
    void lose_resource(const unsigned) override;
    void reset_resource() override;
    virtual ResourceType get_resource_type() const = 0;

    void tick_resource();

    virtual unsigned get_max_resource() const = 0;

protected:
    Character* pchar;
    ResourceTick* resource_tick;

    unsigned resource_per_tick;

    virtual double get_tick_rate() const = 0;
    virtual unsigned get_resource_per_tick() = 0;

    virtual void reset_effect() = 0;
    virtual void lose_resource_effect() = 0;
};
