#pragma once

#include <QHash>
#include <QString>

enum class EventType : int
{
    BuffRemoval,
    CastComplete,
    DotTick,
    EncounterEnd,
    EncounterStart,
    IncomingDamage,
    MainhandMeleeHit,
    OffhandMeleeHit,
    PeriodicRefreshBuff,
    PetAction,
    PetMeleeHit,
    PlayerAction,
    RangedHit,
    SpellCallback,
};

inline uint qHash(const EventType event_type) {
    return qHash(static_cast<int>(event_type), 0xF0F0F);
}

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
    bool operator()(Event*&, Event*&);
};
