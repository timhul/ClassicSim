#ifndef CRUELTY_H
#define CRUELTY_H

#include "Talent.h"

class TalentTree;

class Cruelty: public Talent {
public:
    Cruelty(Character *pchar, TalentTree* tree);
    ~Cruelty() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // CRUELTY_H
