#ifndef EXECUTE_H
#define EXECUTE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class Execute: public Spell, public TalentRequirer {
public:
    Execute(Character* pchar);

    void set_execute_threshold(const double);
    void reset_execute_threshold();

protected:
private:
    friend class ImprovedExecute;

    Warrior* warr;
    QVector<QPair<int, int>> spell_ranks;
    QVector<int> talent_ranks;
    int initial_dmg;
    int dmg_per_rage_converted;
    double execute_threshold;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // EXECUTE_H
