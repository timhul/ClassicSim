#ifndef IMPROVEDOVERPOWER_H
#define IMPROVEDOVERPOWER_H

#include "Talent.h"

class Overpower;
class TalentTree;

class ImprovedOverpower: public Talent {
    Q_OBJECT
public:
    ImprovedOverpower(Character *pchar, TalentTree* tree);
    ~ImprovedOverpower() override;

private:
    Overpower* overpower;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDOVERPOWER_H
