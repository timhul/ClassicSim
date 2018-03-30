#ifndef IMPROVEDSLAM_H
#define IMPROVEDSLAM_H

#include "Talent.h"

class TalentTree;

class ImprovedSlam: public Talent {
    Q_OBJECT
public:
    ImprovedSlam(Character *pchar, TalentTree* tree);
    virtual ~ImprovedSlam();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

private:
};

#endif // IMPROVEDSLAM_H
