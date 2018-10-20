#ifndef AVAILABLEFACTIONS_H
#define AVAILABLEFACTIONS_H

#include <QObject>

class AvailableFactions : public QObject {
    Q_OBJECT

public:
    enum Name {
        Neutral = 0,
        Alliance,
        Horde
    };

    Q_ENUMS(Name)
};


#endif // AVAILABLEFACTIONS_H
