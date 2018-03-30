#ifndef TACTICALMASTERY_H
#define TACTICALMASTERY_H

#include "Talent.h"

class TacticalMastery: public Talent {
    Q_OBJECT
public:
    TacticalMastery(Character *pchar);
    virtual ~TacticalMastery();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // TACTICALMASTERY_H
