#pragma once

#include <QString>

enum class EventType: int {
    BuffRemoval,
    CastComplete,
    DotTick,
    EncounterEnd,
    EncounterStart,
    MainhandMeleeHit,
    OffhandMeleeHit,
    PeriodicRefreshBuff,
    PetAction,
    PetMeleeHit,
    PlayerAction,
    RangedHit,
    ResourceGain,
};

class Event {
public:
    friend bool operator<(const Event&, const Event&);
    friend bool operator>(const Event&, const Event&);
    friend bool operator<=(const Event&, const Event&);
    friend bool operator>=(const Event&, const Event&);

    Event(EventType event_type, const double priority);
    virtual ~Event() = default;

    virtual void act() = 0;

    static QString get_name_for_event_type(const EventType event_type);
    static QString get_name_for_event(const Event* event);

    const EventType event_type;
    const double priority;
};

class Compare {
public:
    bool operator() (Event*&, Event*&);
};
