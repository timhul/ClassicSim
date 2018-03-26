#ifndef PROTECTION_H
#define PROTECTION_H

#include "TalentTree.h"

class Protection: public TalentTree {
    Q_OBJECT
public:
    Protection(Character *pchar, QObject* parent = 0);
    virtual ~Protection();

private:
};

#endif // PROTECTION_H
