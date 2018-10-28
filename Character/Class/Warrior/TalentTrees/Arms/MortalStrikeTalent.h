#ifndef MORTALSTRIKETALENT_H
#define MORTALSTRIKETALENT_H

#include "Talent.h"

class MortalStrike;
class TalentTree;

class MortalStrikeTalent: public Talent {
public:
    MortalStrikeTalent(Character *pchar, TalentTree* tree);
    ~MortalStrikeTalent() override;

private:
    MortalStrike* mortal_strike;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // MORTALSTRIKETALENT_H
