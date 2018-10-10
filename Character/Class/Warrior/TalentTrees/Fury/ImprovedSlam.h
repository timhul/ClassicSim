#ifndef IMPROVEDSLAM_H
#define IMPROVEDSLAM_H

#include "Talent.h"

class Slam;
class TalentTree;

class ImprovedSlam: public Talent {
    Q_OBJECT
public:
    ImprovedSlam(Character *pchar, TalentTree* tree);
    ~ImprovedSlam() override;

private:
    Slam* slam;

    void apply_rank_effect() override;
    void remove_rank_effect() override;
};

#endif // IMPROVEDSLAM_H
