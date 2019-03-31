#ifndef FOCUS_H
#define FOCUS_H

#include "RegeneratingResource.h"

class Character;

class Focus: public RegeneratingResource {
public:
    Focus(Character*);

    friend class Cat;

    unsigned get_max_resource() const override;
    unsigned get_resource_per_tick() override;
    ResourceType get_resource_type() const override;
    double get_tick_rate() const override;

private:
    void reset_effect() override;
    void lose_resource_effect() override;
};

#endif // FOCUS_H
