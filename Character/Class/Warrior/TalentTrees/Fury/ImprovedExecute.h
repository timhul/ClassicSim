#ifndef IMPROVEDEXECUTE_H
#define IMPROVEDEXECUTE_H

#include "Talent.h"

class ImprovedExecute: public Talent {
    Q_OBJECT
public:
    ImprovedExecute(Character *pchar);
    virtual ~ImprovedExecute();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDEXECUTE_H
