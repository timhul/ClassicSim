#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"
#include "Statistics.h"

class Engine {
public:
    Engine(): current_prio(-1) {
        queue = new Queue();
        statistics = new Statistics();
    }

    ~Engine() {
        delete queue;
        delete statistics;
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
};


#endif // ENGINE_H
