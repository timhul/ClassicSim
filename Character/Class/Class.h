#ifndef CLASS_H
#define CLASS_H

#include <string>
#include "Character.h"

class Class : public Character {
public:
    virtual ~Class() {}

    Class(Race* _race, Engine* _engine):
          Character(_race, _engine) {}

    virtual std::string get_name() const = 0;

protected:
private:
};

#endif // CLASS_H
