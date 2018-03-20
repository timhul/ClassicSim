#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"
#include "Statistics.h"
#include <QTime>

class Engine {
public:
    Engine():
        current_prio(-1),
        processed_events(0)
    {
        queue = new Queue();
        statistics = new Statistics();
        timer = new QTime();
    }

    ~Engine() {
        delete queue;
        delete statistics;
        delete timer;
    }

    void run(void);
    void end_combat(void);
    float get_current_priority(void) const;
    void set_current_priority(Event*);
    void add_event(Event*);

    Statistics* get_statistics(void);

protected:

private:
    Queue* queue;
    Statistics* statistics;
    float current_prio;

    unsigned processed_events;
    QTime *timer;
};


#endif // ENGINE_H
