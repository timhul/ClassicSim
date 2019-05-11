#ifndef EVISCERATE_H
#define EVISCERATE_H

#include <QVector>

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Random;
class Rogue;

class Eviscerate: public Spell, public TalentRequirer, public SetBonusRequirer {
public:
    Eviscerate(Character* pchar);
    ~Eviscerate() override;

private:
    Rogue* rogue;
    Random* evisc_range;
    QVector<QPair<unsigned, unsigned>> damage_ranges_per_combo_point;
    QVector<double> aggression_modifiers;
    QVector<double> imp_evisc_modifiers;

    double aggression_modifier;
    double imp_evisc_modifier;
    double deathdealer_modifier;
    double total_dmg_modifier;

    void set_evisc_range();
    void update_dmg_modifier();

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};

#endif // EVISCERATE_H
