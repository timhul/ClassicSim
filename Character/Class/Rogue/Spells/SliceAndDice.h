#ifndef SLICEANDDICE_H
#define SLICEANDDICE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Rogue;
class SliceAndDiceBuff;

class SliceAndDice: public Spell, public TalentRequirer {
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

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // SLICEANDDICE_H
