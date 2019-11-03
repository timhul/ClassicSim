#pragma once

#include "ItemModificationRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class Druid;
class StatisticsResource;

class CatForm: public Spell, public TalentRequirer, public ItemModificationRequirer {
public:
    CatForm(Druid* druid, Buff* cat_form);
    ~CatForm() override;

private:
    friend class Druid;

    Druid* druid;
    Buff* buff;
    StatisticsResource* statistics_resource {nullptr};

    unsigned base_resource_cost;
    unsigned wolfshead_bonus {0};

    const QVector<double> natural_shapeshifter_ranks {1.0, 0.9, 0.8, 0.7};

    void prepare_set_of_combat_iterations_spell_specific() override;
    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;
    void gain_energy(const unsigned energy);

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};
