#include "RegeneratingResource.h"

#include "Character.h"
#include "Engine.h"
#include "ResourceGain.h"
#include "ResourceTick.h"
#include "Utils/Check.h"

RegeneratingResource::RegeneratingResource(Character* pchar) :
    pchar(pchar),
    resource_per_tick(0),
    ticking(false)
{
    this->resource_tick = new ResourceTick(pchar, this);
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
    if (!ticking && current == max)
        add_next_tick();

    check((current >= value), "Underflow decrease");
    current -= value;

    lose_resource_effect();
}

void RegeneratingResource::add_next_tick() {
    ticking = true;

    auto* event = new ResourceGain(pchar, resource_tick, pchar->get_engine()->get_current_priority() + get_tick_rate());
    pchar->get_engine()->add_event(event);
}

void RegeneratingResource::tick_resource() {
    if (current == max) {
        ticking = false;
        return;
    }

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

    add_next_tick();
}

void RegeneratingResource::reset_resource() {
    max = get_max_resource();
    current = max;
    ticking = false;

    reset_effect();
}
