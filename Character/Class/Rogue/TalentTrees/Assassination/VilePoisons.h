#ifndef VILEPOISONS_H
#define VILEPOISONS_H

#include "Talent.h"

class InstantPoison;
class TalentTree;

class VilePoisons: public Talent {
public:
    VilePoisons(Character *pchar, TalentTree* tree);

private:
    InstantPoison* mh_instant_poison;
    InstantPoison* oh_instant_poison;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // VILEPOISONS_H
