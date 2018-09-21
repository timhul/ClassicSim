#ifndef ARMS_H
#define ARMS_H

#include "TalentTree.h"

class Arms: public TalentTree {
    Q_OBJECT
public:
    Arms(Character* pchar, QObject* parent = nullptr);
    ~Arms() override;

private:
};

#endif // ARMS_H
