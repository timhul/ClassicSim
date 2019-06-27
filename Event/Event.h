#pragma once

#include <QString>

enum class Events: int {
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

    Event(Events event_enum_val, const double priority, const QString& name);
    virtual ~Event() = default;

    virtual void act() = 0;

    const Events event;
    const double priority;
    const QString name;
};

class Compare {
public:
    bool operator() (Event*&, Event*&);
};
