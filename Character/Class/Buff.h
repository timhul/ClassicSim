#ifndef BUFF_H
#define BUFF_H

#include <string>
#include <assert.h>

class Character;

class Buff {
public:
    Buff(Character*, const std::string, const int);

    std::string get_name() const;
    void apply_buff();
    void remove_buff();
    void use_charge();
    bool is_active() const;
    float time_left() const;

protected:
    Character* pchar;
    const std::string name;
    const int duration;
    float applied;
    float refreshed;
    float expired;
    const int base_charges;
    int current_charges;
    bool active;
private:
    virtual void buff_effect_when_applied() = 0;
    virtual void buff_effect_when_removed() = 0;
};

#endif // BUFF_H
