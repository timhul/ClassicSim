#ifndef UNBRIDLEDWRATHTALENT_H
#define UNBRIDLEDWRATHTALENT_H

#include "Talent.h"

class TalentTree;
class UnbridledWrath;

class UnbridledWrathTalent: public Talent {
    Q_OBJECT
public:
    UnbridledWrathTalent(Character *pchar, TalentTree* tree);
    ~UnbridledWrathTalent() override;

private:
    UnbridledWrath* unbridled_wrath;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // UNBRIDLEDWRATHTALENT_H
