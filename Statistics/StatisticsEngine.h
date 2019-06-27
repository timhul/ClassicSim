#ifndef STATISTICSENGINE_H
#define STATISTICSENGINE_H

#include <QMap>

class StatisticsEngine;
enum class EventType: int;

bool event_type(QPair<EventType, unsigned> lhs, QPair<EventType, unsigned> rhs);
bool total(QPair<EventType, unsigned> lhs, QPair<EventType, unsigned> rhs);

class StatisticsEngine {
public:
    void reset();

    void increment_event(EventType event);

    void set_elapsed(const unsigned elapsed);
    unsigned get_elapsed() const;
    void add(const StatisticsEngine*);

    QList<QPair<EventType, unsigned>> get_list_of_event_pairs() const;

private:
    unsigned elapsed {0};
    QMap<EventType, unsigned> event_map;
};

#endif // STATISTICSENGINE_H
