#ifndef IMPALE_H
#define IMPALE_H

#include "Talent.h"

class TalentTree;

class Impale: public Talent {
    Q_OBJECT
public:
    Impale(Character *pchar, TalentTree* tree);
    ~Impale() override;

    void apply_rank_effect() override;
    void remove_rank_effect() override;

private:
};

#endif // IMPALE_H
