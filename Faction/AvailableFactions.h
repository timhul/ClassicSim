#pragma once

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
