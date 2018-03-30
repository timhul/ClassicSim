#ifndef UNBRIDLEDWRATH_H
#define UNBRIDLEDWRATH_H

#include "Talent.h"

class TalentTree;

class UnbridledWrath: public Talent {
    Q_OBJECT
public:
    UnbridledWrath(Character *pchar, TalentTree* tree);
    virtual ~UnbridledWrath();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // UNBRIDLEDWRATH_H
