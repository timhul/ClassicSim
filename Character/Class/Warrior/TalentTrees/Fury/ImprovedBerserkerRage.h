#ifndef IMPROVEDBERSERKERRAGE_H
#define IMPROVEDBERSERKERRAGE_H

#include "Talent.h"

class TalentTree;

class ImprovedBerserkerRage: public Talent {
    Q_OBJECT
public:
    ImprovedBerserkerRage(Character *pchar, TalentTree* tree);
    ~ImprovedBerserkerRage() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPROVEDBERSERKERRAGE_H
