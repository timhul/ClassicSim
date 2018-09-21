#ifndef IMPROVEDOVERPOWER_H
#define IMPROVEDOVERPOWER_H

#include "Talent.h"

class TalentTree;

class ImprovedOverpower: public Talent {
    Q_OBJECT
public:
    ImprovedOverpower(Character *pchar, TalentTree* tree);
    ~ImprovedOverpower() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPROVEDOVERPOWER_H
