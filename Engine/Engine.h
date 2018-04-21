#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"
#include "Statistics.h"
#include <QTime>

class Engine {
public:
    Engine():
        current_prio(0),
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
    void dump(void);
    void reset(void);
    void prepare(void);
    void end_combat(void);
    float get_current_priority(void) const;
    void set_current_priority(Event*);
    void add_event(Event*);

    Queue *get_queue() const;

    Statistics* get_statistics(void);
    void save_event_history(Event*);

protected:

private:
    Queue* queue;
    Statistics* statistics;
    float current_prio;

    unsigned processed_events;
    QTime *timer;
    QMap<QString, int> processed_events_of_type;
};


#endif // ENGINE_H
