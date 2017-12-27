#ifndef CLASS_H
#define CLASS_H

#include <string>
#include "Engine.h"
#include "Character.h"

class Class : public Character {
public:
    virtual ~Class() {}

    Class(Race* _race, Engine* _engine):
          Character(_race), engine(_engine) {}

    virtual std::string get_name() const = 0;
    virtual void rotation() const = 0;
    virtual float global_cooldown() const = 0;
    Engine* get_engine(void) const { return this->engine; }

protected:
    Engine* engine;
private:
};

#endif // CLASS_H
