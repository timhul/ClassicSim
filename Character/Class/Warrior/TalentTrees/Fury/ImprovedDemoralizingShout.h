#ifndef IMPROVEDDEMORALIZINGSHOUT_H
#define IMPROVEDDEMORALIZINGSHOUT_H

#include "Talent.h"

class TalentTree;

class ImprovedDemoralizingShout: public Talent {
    Q_OBJECT
public:
    ImprovedDemoralizingShout(Character *pchar, TalentTree* tree);
    ~ImprovedDemoralizingShout() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPROVEDDEMORALIZINGSHOUT_H
