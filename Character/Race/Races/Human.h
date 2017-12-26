#ifndef HUMAN_H
#define HUMAN_H

#include "Race.h"

class Human: public Race {
public:
    std::string get_name() const override;
    int get_base_strength() const override;
    int get_base_agility() const override;
    int get_base_stamina() const override;
    int get_base_intellect() const override;
    int get_base_spirit() const override;
protected:
private:
};

#endif // HUMAN_H
