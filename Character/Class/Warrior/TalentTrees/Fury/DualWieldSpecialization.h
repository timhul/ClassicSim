#ifndef DUALWIELDSPECIALIZATION_H
#define DUALWIELDSPECIALIZATION_H

#include "Talent.h"

class DualWieldSpecialization: public Talent {
    Q_OBJECT
public:
    DualWieldSpecialization(Character *pchar);
    virtual ~DualWieldSpecialization();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // DUALWIELDSPECIALIZATION_H
