#ifndef UNBRIDLEDWRATH_H
#define UNBRIDLEDWRATH_H

#include "Talent.h"

class UnbridledWrath: public Talent {
    Q_OBJECT
public:
    UnbridledWrath(Character *pchar);
    virtual ~UnbridledWrath();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // UNBRIDLEDWRATH_H
