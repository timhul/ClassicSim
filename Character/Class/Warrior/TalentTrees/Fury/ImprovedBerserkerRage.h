#ifndef IMPROVEDBERSERKERRAGE_H
#define IMPROVEDBERSERKERRAGE_H

#include "Talent.h"

class ImprovedBerserkerRage: public Talent {
    Q_OBJECT
public:
    ImprovedBerserkerRage(Character *pchar);
    virtual ~ImprovedBerserkerRage();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDBERSERKERRAGE_H
