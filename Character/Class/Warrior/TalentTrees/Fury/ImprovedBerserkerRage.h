#ifndef IMPROVEDBERSERKERRAGE_H
#define IMPROVEDBERSERKERRAGE_H

#include "Talent.h"

class BerserkerRage;
class TalentTree;

class ImprovedBerserkerRage: public Talent {
public:
    ImprovedBerserkerRage(Character *pchar, TalentTree* tree);
    ~ImprovedBerserkerRage() override;

private:
    BerserkerRage* berserker_rage;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDBERSERKERRAGE_H
