#pragma once

#include <QVector>

#include "SpellPeriodic.h"
#include "TalentRequirer.h"

class Buff;
class IgniteBuff;
class Mage;
class MageSpells;

class Ignite : public SpellPeriodic, public TalentRequirer {
public:
    Ignite(Mage* pchar, IgniteBuff* ignite_buff);

    void inflict_ignite(const double original_dmg);

private:
    IgniteBuff* ignite_buff;

    int current_iteration {-1};
    double ignite_percentage {0.0};
    QVector<double> ignite_ranks {0.0, 0.08, 0.16, 0.24, 0.32, 0.40};

    bool is_current_owner() const;

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void tick_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
