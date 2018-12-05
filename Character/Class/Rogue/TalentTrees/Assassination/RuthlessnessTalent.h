#ifndef RUTHLESSNESSTALENT_H
#define RUTHLESSNESSTALENT_H

#include "Talent.h"

class Ruthlessness;
class TalentTree;

class RuthlessnessTalent: public Talent {
public:
    RuthlessnessTalent(Character *pchar, TalentTree* tree);

private:
    Ruthlessness* ruthlessness;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // RUTHLESSNESSTALENT_H
