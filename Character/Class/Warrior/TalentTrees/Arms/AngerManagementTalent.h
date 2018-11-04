#ifndef ANGERMANAGEMENTTALENT_H
#define ANGERMANAGEMENTTALENT_H

#include "Talent.h"

class TalentTree;
class Warrior;

class AngerManagementTalent: public Talent {
public:
    AngerManagementTalent(Character *pchar, TalentTree* tree);
    ~AngerManagementTalent() override;

private:
    Warrior* warr;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // ANGERMANAGEMENTTALENT_H
