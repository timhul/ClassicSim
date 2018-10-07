#ifndef MORTALSTRIKETALENT_H
#define MORTALSTRIKETALENT_H

#include "Talent.h"

class TalentTree;

class MortalStrikeTalent: public Talent {
    Q_OBJECT
public:
    MortalStrikeTalent(Character *pchar, TalentTree* tree);
    ~MortalStrikeTalent() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // MORTALSTRIKETALENT_H
