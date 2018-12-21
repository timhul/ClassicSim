#ifndef HEMORRHAGETALENT_H
#define HEMORRHAGETALENT_H

#include "Talent.h"

class Hemorrhage;
class TalentTree;

class HemorrhageTalent: public Talent {
public:
    HemorrhageTalent(Character *pchar, TalentTree* tree);
    ~HemorrhageTalent() override;

private:
    Hemorrhage* hemorrhage;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // HEMORRHAGETALENT_H
