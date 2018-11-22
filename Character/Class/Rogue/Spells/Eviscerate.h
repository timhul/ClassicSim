#ifndef EVISCERATE_H
#define EVISCERATE_H

#include <QVector>

#include "Spell.h"

class Random;
class Rogue;

class Eviscerate: public Spell {
public:
    Eviscerate(Character* pchar);
    ~Eviscerate() override;

protected:
private:
    Rogue* rogue;
    Random* evisc_range;
    QVector<QPair<unsigned, unsigned>> damage_ranges_per_combo_point;

    void set_evisc_range();

    void spell_effect() override;
    bool is_ready_spell_specific() const override;
};

#endif // EVISCERATE_H
