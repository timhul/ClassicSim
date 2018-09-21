#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"
#include <QTime>
#include <QMap>

class Engine {
public:
    Engine();
    ~Engine();

    void run(void);
    void dump(void);
    void reset(void);
    void prepare(void);
    void end_combat(void);
    double get_current_priority(void) const;
    void set_current_priority(Event*);
    void add_event(Event*);

    Queue *get_queue() const;

    void save_event_history(Event*);

protected:

private:
    Queue* queue;
    QTime *timer;
    double current_prio;
    unsigned processed_events;
    QMap<QString, int> processed_events_of_type;
};


#endif // ENGINE_H
