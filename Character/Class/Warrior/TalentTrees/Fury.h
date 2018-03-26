#ifndef FURY_H
#define FURY_H

#include "TalentTree.h"

class Fury: public TalentTree {
    Q_OBJECT
public:
    Fury(Character *pchar, QObject* parent = 0);
    virtual ~Fury();

private:
};

#endif // FURY_H
