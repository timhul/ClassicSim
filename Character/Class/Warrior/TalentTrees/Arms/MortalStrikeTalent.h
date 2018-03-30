#ifndef MORTALSTRIKETALENT_H
#define MORTALSTRIKETALENT_H

#include "Talent.h"

class TalentTree;

class MortalStrikeTalent: public Talent {
    Q_OBJECT
public:
    MortalStrikeTalent(Character *pchar, TalentTree* tree);
    virtual ~MortalStrikeTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // MORTALSTRIKETALENT_H
