#ifndef IMPROVEDSLAM_H
#define IMPROVEDSLAM_H

#include "Talent.h"

class ImprovedSlam: public Talent {
    Q_OBJECT
public:
    ImprovedSlam(Character *pchar);
    virtual ~ImprovedSlam();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDSLAM_H
