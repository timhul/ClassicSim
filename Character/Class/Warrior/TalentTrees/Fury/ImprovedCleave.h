#ifndef IMPROVEDCLEAVE_H
#define IMPROVEDCLEAVE_H

#include "Talent.h"

class ImprovedCleave: public Talent {
    Q_OBJECT
public:
    ImprovedCleave(Character *pchar);
    virtual ~ImprovedCleave();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDCLEAVE_H
