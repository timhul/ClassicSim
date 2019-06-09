#ifndef SANCTITYAURA_H
#define SANCTITYAURA_H

#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Paladin;
class SanctityAuraBuff;

class SanctityAura: public Spell, public TalentRequirer {
public:
    SanctityAura(Paladin* pchar, SanctityAuraBuff* buff);
    ~SanctityAura() override;

private:
    Buff* buff;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // SANCTITYAURA_H
