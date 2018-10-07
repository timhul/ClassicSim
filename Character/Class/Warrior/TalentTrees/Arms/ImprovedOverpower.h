#ifndef IMPROVEDOVERPOWER_H
#define IMPROVEDOVERPOWER_H

#include "Talent.h"

class TalentTree;

class ImprovedOverpower: public Talent {
    Q_OBJECT
public:
    ImprovedOverpower(Character *pchar, TalentTree* tree);
    ~ImprovedOverpower() override;

private:
    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDOVERPOWER_H
