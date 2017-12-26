#ifndef RACE_H
#define RACE_H

#include <map>

class Race {
public:
    virtual ~Race() {}

    virtual std::string get_name() const = 0;
    virtual int get_base_strength() const = 0;
    virtual int get_base_agility() const = 0;
    virtual int get_base_stamina() const = 0;
    virtual int get_base_intellect() const = 0;
    virtual int get_base_spirit() const = 0;

protected:
    std::map<std::string, int> stats;
private:
};

#endif // RACE_H
