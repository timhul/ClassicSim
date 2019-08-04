#include "RegeneratingResource.h"

#include "Character.h"
#include "Engine.h"
#include "ResourceTick.h"
#include "Utils/Check.h"

RegeneratingResource::RegeneratingResource(Character* pchar) :
    pchar(pchar),
    resource_per_tick(0)
{
    this->resource_tick = new ResourceTick(pchar, this);
    this->resource_tick->enable();
}

RegeneratingResource::~RegeneratingResource() {
    delete resource_tick;
}

void RegeneratingResource::gain_resource(const unsigned value) {
    current += value;

    if (current > max)
        current = max;
}

void RegeneratingResource::lose_resource(const unsigned value) {
    resource_tick->perform();

    check((current >= value), "Underflow decrease RegeneratingResource::lose_resource()");
    current -= value;

    lose_resource_effect();
}

void RegeneratingResource::tick_resource() {
    if (current == max)
        return resource_tick->invalidate();

    switch (get_resource_type()) {
    case ResourceType::Mana:
        pchar->gain_mana(resource_per_tick);
        break;
    case ResourceType::Focus:
        pchar->gain_focus(resource_per_tick);
        break;
    case ResourceType::Energy:
        pchar->gain_energy(resource_per_tick);
        break;
    case ResourceType::Rage:
        check(false, "Rage is not a regenerating resource");
        break;
    }

    gain_resource(get_resource_per_tick());
}

void RegeneratingResource::reset_resource() {
    max = get_max_resource();
    current = max;
    resource_tick->invalidate();

    reset_effect();
}
