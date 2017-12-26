#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"

class Engine {
public:
    void run(void);
    void test_queue(void);
    void test_character_creation(void);

protected:

private:
    Queue queue;
};


#endif // ENGINE_H
