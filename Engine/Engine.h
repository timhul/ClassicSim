#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"

class Engine {
public:
    Engine(): current_prio(-1) {}
    void run(void);
    void test_queue(void);
    void test_character_creation(void);
    void end_combat(void);
    float get_current_priority(void) const;
    void set_current_priority(Event*);
    void add_action_event(Event*);
    void add_mh_event(Event*);
    void add_oh_event(Event*);

protected:

private:
    Queue queue;
    float current_prio;
};


#endif // ENGINE_H
