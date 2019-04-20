#ifndef STATISTICSENGINE_H
#define STATISTICSENGINE_H

#include <QMap>

class StatisticsEngine;
enum class Events: int;

bool event_type(QPair<Events, unsigned> lhs, QPair<Events, unsigned> rhs);
bool total(QPair<Events, unsigned> lhs, QPair<Events, unsigned> rhs);

class StatisticsEngine {
public:
    void reset();

    void increment_event(Events event);

    void set_elapsed(const unsigned elapsed);
    unsigned get_elapsed() const;
    void add(const StatisticsEngine*);

    static QString get_name_for_event(const Events event);
    QList<QPair<Events, unsigned>> get_list_of_event_pairs() const;

private:
    unsigned elapsed {0};
    QMap<Events, unsigned> event_map;
};

#endif // STATISTICSENGINE_H
