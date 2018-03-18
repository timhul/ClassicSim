#ifndef BUFF_H
#define BUFF_H

#include <string>
#include <assert.h>
#include "Character.h"

class Buff {
public:
    Buff(const std::string _name, const int _dur):
        name(_name), duration(_dur),
        applied(_dur - 1), refreshed(_dur - 1), expired(_dur - 1), charges(0), active(false) {}

    std::string get_name() const;
    void apply_buff(const float, const int);
    void remove_buff(const float);
    void use_charge(const float);
    bool is_active() const;
    float time_left(const float) const;

    virtual void buff_effect(Character*) = 0;

protected:
    const std::string name;
    const int duration;
    float applied;
    float refreshed;
    float expired;
    int charges;
    bool active;
private:
};

#endif // BUFF_H
