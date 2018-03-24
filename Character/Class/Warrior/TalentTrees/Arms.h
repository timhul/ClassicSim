#ifndef ARMS_H
#define ARMS_H

#include "TalentTree.h"

class Arms: public TalentTree {
    Q_OBJECT
public:
    Arms(QObject* parent = 0);
    virtual ~Arms();

private:
};

#endif // ARMS_H
