#ifndef UNBRIDLEDWRATHTALENT_H
#define UNBRIDLEDWRATHTALENT_H

#include "Talent.h"

class TalentTree;

class UnbridledWrathTalent: public Talent {
    Q_OBJECT
public:
    UnbridledWrathTalent(Character *pchar, TalentTree* tree);
    virtual ~UnbridledWrathTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // UNBRIDLEDWRATHTALENT_H
