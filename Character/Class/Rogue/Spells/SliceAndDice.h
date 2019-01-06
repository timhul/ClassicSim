#ifndef SLICEANDDICE_H
#define SLICEANDDICE_H

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Rogue;
class SliceAndDiceBuff;

class SliceAndDice: public Spell, public TalentRequirer, public SetBonusRequirer {
public:
    SliceAndDice(Character* pchar);
    ~SliceAndDice() override;

protected:
private:
    friend class ImprovedSliceAndDice;

    Rogue* rogue;
    SliceAndDiceBuff* buff;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};

#endif // SLICEANDDICE_H
