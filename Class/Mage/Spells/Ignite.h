#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class IgniteBuff;
class Mage;
class MageSpells;

class Ignite: public Spell, public TalentRequirer {
public:
    Ignite(Mage* pchar, IgniteBuff* ignite_buff);
    ~Ignite() override;

    void inflict_ignite(const double original_dmg);
    void perform_periodic() override;

private:
    IgniteBuff* ignite_buff;

    int current_iteration {-1};
    double ignite_percentage {0.0};
    QVector<double> ignite_ranks {0.0, 0.08, 0.16, 0.24, 0.32, 0.40};

    void spell_effect() override;
    bool is_current_owner() const;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
