#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <ctime>

class Random {
public:
    Random() {
        gen = new std::mt19937(std::time(0));
        distr = new std::uniform_int_distribution<>(0, 9999);
    }

    ~Random() {
        delete gen;
        delete distr;
    }

    int get_roll(void) {
        return (*distr)((*gen));
    }
protected:
private:
    std::mt19937* gen;
    std::uniform_int_distribution<>* distr;
};

#endif // RANDOM_H
