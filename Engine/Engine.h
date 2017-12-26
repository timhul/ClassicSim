#ifndef ENGINE_H
#define ENGINE_H

#include "Queue.h"

class Engine {
public:
    void run(void);
    void test_queue(void);

protected:

private:
    Queue queue;
};


#endif // ENGINE_H
