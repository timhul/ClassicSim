#ifndef EVISCERATE_H
#define EVISCERATE_H

#include <QVector>

#include "Spell.h"
#include "TalentRequirer.h"

class Random;
class Rogue;

class Eviscerate: public Spell, public TalentRequirer {
public:
    Eviscerate(Character* pchar);
    ~Eviscerate() override;

private:
    friend class ImprovedEviscerate;

    Rogue* rogue;
    Random* evisc_range;
    QVector<QPair<unsigned, unsigned>> damage_ranges_per_combo_point;
    QVector<double> imp_evisc_modifiers;

    double total_dmg_modifier;
    double imp_evisc_modifier;

    void set_evisc_range();
    void update_dmg_modifier();

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // EVISCERATE_H
