#ifndef CLASS_H
#define CLASS_H

#include <string>

class Class {
public:
    virtual ~Class() {}

    virtual std::string get_name() const = 0;
    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;

protected:
private:
};

#endif // CLASS_H
