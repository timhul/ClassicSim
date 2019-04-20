#include "StatisticsEngine.h"

#include "Event.h"
#include "Utils/Check.h"

bool event_type(QPair<Events, unsigned> lhs, QPair<Events, unsigned> rhs) {
    return static_cast<int>(lhs.first) > static_cast<int>(rhs.first);
}

bool total(QPair<Events, unsigned> lhs, QPair<Events, unsigned> rhs) {
    return lhs.second > rhs.second;
}

void StatisticsEngine::reset() {
    event_map.clear();
}

void StatisticsEngine::increment_event(Events event) {
    if (!event_map.contains(event))
        event_map[event] = 0;

    ++event_map[event];
}

void StatisticsEngine::set_elapsed(const unsigned elapsed) {
    check((this->elapsed == 0), QString("Set elapsed when it was already set (%1)").arg(this->elapsed).toStdString());
    this->elapsed = elapsed;
}

unsigned StatisticsEngine::get_elapsed() const {
    return this->elapsed;
}

void StatisticsEngine::add(const StatisticsEngine* other) {
    this->elapsed += other->elapsed;

    QMap<Events, unsigned>::const_iterator it = other->event_map.constBegin();
    while (it != other->event_map.constEnd()) {
        if (!this->event_map.contains(it.key()))
            this->event_map[it.key()] = 0;

        this->event_map[it.key()] += other->event_map[it.key()];
        ++it;
    }
}

QString StatisticsEngine::get_name_for_event(const Events event) {
    switch (event) {
    case Events::BuffRemoval:
        return "BuffRemoval";
    case Events::CastComplete:
        return "CastComplete";
    case Events::DotTick:
        return "DotTick";
    case Events::EncounterEnd:
        return "EncounterEnd";
    case Events::EncounterStart:
        return "EncounterStart";
    case Events::MainhandMeleeHit:
        return "MainhandMeleeHit";
    case Events::OffhandMeleeHit:
        return "OffhandMeleeHit";
    case Events::PeriodicRefreshBuff:
        return "PeriodicRefreshBuff";
    case Events::PetAction:
        return "PetAction";
    case Events::PetMeleeHit:
        return "PetMeleeHit";
    case Events::PlayerAction:
        return "PlayerAction";
    case Events::RangedHit:
        return "RangedHit";
    case Events::ResourceGain:
        return "ResourceGain";
    }

    return "<missing name for event>";
}

QList<QPair<Events, unsigned> > StatisticsEngine::get_list_of_event_pairs() const {
    QMap<Events, unsigned>::const_iterator it = event_map.constBegin();

    QList<QPair<Events, unsigned>> event_list;
    while (it != event_map.constEnd()) {
        if (it.value() == 0)
            continue;

        event_list.append({it.key(), it.value()});
        ++it;
    }

    return event_list;
}
