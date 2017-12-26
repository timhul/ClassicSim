#ifndef CLASS_H
#define CLASS_H

#include <string>
#include "Engine.h"

class Class {
public:
    virtual ~Class() {}

    Class(Engine* _engine): engine(_engine) {}

    virtual std::string get_name() const = 0;
    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;
    virtual void rotation() const = 0;
    virtual float global_cooldown() const = 0;
    Engine* get_engine(void) const { return this->engine; }

protected:
    Engine* engine;
private:
};

#endif // CLASS_H
