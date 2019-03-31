#include "Focus.h"

Focus::Focus(Character* pchar) :
    RegeneratingResource(pchar)
{
    reset_resource();
}

unsigned Focus::get_max_resource() const {
    return 100;
}

unsigned Focus::get_resource_per_tick() {
    return 20;
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
