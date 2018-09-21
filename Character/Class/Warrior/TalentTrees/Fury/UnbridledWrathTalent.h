#ifndef UNBRIDLEDWRATHTALENT_H
#define UNBRIDLEDWRATHTALENT_H

#include "Talent.h"

class TalentTree;

class UnbridledWrathTalent: public Talent {
    Q_OBJECT
public:
    UnbridledWrathTalent(Character *pchar, TalentTree* tree);
    ~UnbridledWrathTalent() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // UNBRIDLEDWRATHTALENT_H
