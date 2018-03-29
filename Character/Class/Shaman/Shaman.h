#ifndef SHAMAN_H
#define SHAMAN_H

#include "Character.h"
#include "CombatRoll.h"

class Shaman: public Character {
    Q_OBJECT
public:
    Shaman(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, QObject *parent = 0) :
        Character(race, engine, _eq, parent) {
        this->STR += get_strength_modifier();
        this->AGI += get_agility_modifier();
        this->STAM += get_stamina_modifier();
        this->INT += get_intellect_modifier();
        this->SPI += get_spirit_modifier();
        this->roll = _roll;
    }

    virtual ~Shaman() {}

    QString get_name() const override;
    QString get_class_color() const override;
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

#endif // SHAMAN_H
