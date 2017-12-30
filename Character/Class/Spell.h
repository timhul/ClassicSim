#ifndef SPELL_H
#define SPELL_H

#include <string>
#include "Engine.h"
#include "Character.h"
#include "CooldownReady.h"
#include "assert.h"

class Spell {
public:
    Spell(std::string _name,
          Engine* _eng,
          Character* _pchar,
          float _cd,
          int _cost) :
        name(_name),
        engine(_eng),
        pchar(_pchar),
        cooldown(_cd),
        last_used(0 - _cd),
        resource_cost(_cost) {}

    virtual ~Spell() {}

    std::string get_name() const;
    float get_cooldown();
    float get_last_used();
    float get_next_use() const;
    bool is_ready() const;
    bool is_available(const int) const;
    bool cooldown_less_than(const float) const;
    bool cooldown_greater_than(const float) const;
    void add_spell_cd_event(void) const;
    void add_gcd_event(void) const;

    int perform(const int);

protected:
    virtual int spell_effect(const int) const = 0;
    const std::string name;
    Engine* engine;
    Character* pchar;
    float cooldown;
    float last_used;
    int resource_cost;
private:
};

#endif // SPELL_H
