#ifndef BESTIALWRATH_H
#define BESTIALWRATH_H

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class BestialWrathBuff;
class Pet;

class BestialWrath: public Spell, public TalentRequirer {
public:
    BestialWrath(Character *pchar, const QString& pet_name);
    ~BestialWrath() override;

private:
    BestialWrathBuff* bestial_wrath_buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // BESTIALWRATH_H
