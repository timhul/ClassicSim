#ifndef ORC_H
#define ORC_H

#include "Race.h"

class Orc: public Race {
public:
    std::string get_name() const override;
    int get_base_strength() const override;
    int get_base_agility() const override;
    int get_base_stamina() const override;
    int get_base_intellect() const override;
    int get_base_spirit() const override;
    float get_int_multiplier() const override;
    float get_spirit_multiplier() const override;
protected:
private:
};


#endif // ORC_H
