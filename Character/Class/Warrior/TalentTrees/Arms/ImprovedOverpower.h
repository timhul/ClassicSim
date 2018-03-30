#ifndef IMPROVEDOVERPOWER_H
#define IMPROVEDOVERPOWER_H

#include "Talent.h"

class ImprovedOverpower: public Talent {
    Q_OBJECT
public:
    ImprovedOverpower(Character *pchar);
    virtual ~ImprovedOverpower();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDOVERPOWER_H
