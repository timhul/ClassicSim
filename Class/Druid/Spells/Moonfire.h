#pragma once

#include <QVector>

#include "ItemModificationRequirer.h"
#include "SpellPeriodic.h"
#include "TalentRequirer.h"

class Buff;
class Druid;
class DruidSpells;
class Random;

class Moonfire : public SpellPeriodic, public TalentRequirer, public ItemModificationRequirer {
public:
    Moonfire(Druid* pchar, DruidSpells* druid_spells, const int spell_rank);
    ~Moonfire() override;

    bool is_rank_learned() const override;

    static int duration_for_spell_rank(const unsigned spell_rank);

private:
    DruidSpells* druid_spells;
    Random* instant_dmg;

    double instant_spell_dmg_coefficient;
    double dot_spell_dmg_coefficient;
    unsigned base_resource_cost;
    unsigned base_instant_damage_min;
    unsigned base_instant_damage_max;
    unsigned full_duration_damage;
    int duration;

    double num_ticks;
    double reported_resource_cost;
    double reported_execution_time;
    double tick_rest {0.0};

    double imp_moonfire_damage_bonus {1.0};
    unsigned imp_moonfire_crit_bonus {0};
    const QVector<QPair<double, unsigned>> improved_moonfire_ranks {
        {1.0, 0}, {1.02, 200}, {1.04, 400}, {1.06, 600}, {1.08, 800}, {1.10, 1000},
    };

    double vengeance_crit_damage_bonus {1.0};
    const QVector<double> vengeance_ranks {1.0, 1.2, 1.4, 1.6, 1.8, 2.0};

    const QVector<double> moonglow_ranks {1.0, 0.97, 0.94, 0.91};

    double moonfury_damage_bonus {1.0};
    const QVector<double> moonfury_ranks {1.0, 1.02, 1.04, 1.06, 1.08, 1.10};

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void reset_effect() override;
    void tick_effect() override;

    void set_base_damage_range();

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};
