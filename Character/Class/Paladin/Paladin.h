#ifndef PALADIN_H
#define PALADIN_H

#include "Character.h"
#include "CombatRoll.h"

class Paladin: public Character {
    Q_OBJECT
public:
    Paladin(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, QObject *parent = 0) :
        Character(race, engine, _eq, parent) {
        this->STR += get_strength_modifier();
        this->AGI += get_agility_modifier();
        this->STAM += get_stamina_modifier();
        this->INT += get_intellect_modifier();
        this->SPI += get_spirit_modifier();
        this->roll = _roll;
    }

    virtual ~Paladin() {}

    QString get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() override;
    void mh_auto_attack(const int) override;
    void oh_auto_attack(const int) override;
    float global_cooldown() const override;

    int get_melee_ap() override;

protected:
private:
    CombatRoll* roll;

    void initialize_talents() override;
};

#endif // PALADIN_H
