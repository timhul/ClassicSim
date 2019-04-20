#ifndef EVENT_H
#define EVENT_H

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

    Event(Events event_enum_val);

    virtual ~Event() {}
    virtual void act() = 0;
    virtual QString get_name() const;

    double get_priority() const;
    const Events event;

protected:
    double priority;
    QString name;
};

class Compare {
public:
    bool operator() (Event*&, Event*&);
};

#endif // EVENT_H
