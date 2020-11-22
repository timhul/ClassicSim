#include "Event.h"

bool Compare::operator()(Event*& l, Event*& r) {
    return *l > *r;
}

bool operator<(const Event& l, const Event& r) {
    return l.priority < r.priority;
}

bool operator>(const Event& l, const Event& r) {
    return r < l;
}

bool operator<=(const Event& l, const Event& r) {
    return !(l > r);
}

bool operator>=(const Event& l, const Event& r) {
    return !(r < l);
}

Event::Event(EventType event_type, const double priority) : event_type(event_type), priority(priority) {}

QString Event::get_name_for_event_type(const EventType event_type) {
    switch (event_type) {
    case EventType::BuffRemoval:
        return "BuffRemoval";
    case EventType::CastComplete:
        return "CastComplete";
    case EventType::DotTick:
        return "DotTick";
    case EventType::EncounterEnd:
        return "EncounterEnd";
    case EventType::EncounterStart:
        return "EncounterStart";
    case EventType::MainhandMeleeHit:
        return "MainhandMeleeHit";
    case EventType::OffhandMeleeHit:
        return "OffhandMeleeHit";
    case EventType::PeriodicRefreshBuff:
        return "PeriodicRefreshBuff";
    case EventType::PetAction:
        return "PetAction";
    case EventType::PetMeleeHit:
        return "PetMeleeHit";
    case EventType::PlayerAction:
        return "PlayerAction";
    case EventType::RangedHit:
        return "RangedHit";
    case EventType::SpellCallback:
        return "SpellCallback";
    case EventType::IncomingDamage:
        return "IncomingDamage";
    }

    return "<missing name for event>";
}

QString Event::get_name_for_event(const Event* event) {
    return get_name_for_event_type(event->event_type);
}
