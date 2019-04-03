#include "Focus.h"

#include "Utils/Check.h"

Focus::Focus(Character* pchar) :
    RegeneratingResource(pchar),
    focus_gain(20)
{
    reset_resource();
}

unsigned Focus::get_max_resource() const {
    return 100;
}

unsigned Focus::get_resource_per_tick() {
    return focus_gain;
}

ResourceType Focus::get_resource_type() const {
    return ResourceType::Focus;
}

double Focus::get_tick_rate() const {
    return 2.0;
}

void Focus::reset_effect() {

}

void Focus::lose_resource_effect() {

}

void Focus::increase_focus_gain() {
    focus_gain += 2;
    check((focus_gain <= 24), "Focus gain increased beyond cap");
}

void Focus::decrease_focus_gain() {
    focus_gain -= 2;
    check((focus_gain >= 20), "Focus gain reduced below min");
}
