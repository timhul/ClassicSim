#ifndef FURY_H
#define FURY_H

#include "TalentTree.h"

class Fury: public TalentTree {
    Q_OBJECT
public:
    Fury(Character *pchar, QObject* parent = nullptr);
    ~Fury() override;

private:
};

#endif // FURY_H
