#ifndef VIGOR_H
#define VIGOR_H

#include "Talent.h"

class Rogue;
class TalentTree;

class Vigor: public Talent {
public:
    Vigor(Character *pchar, TalentTree* tree);
    ~Vigor() override;

private:
    Rogue* rogue;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // VIGOR_H
