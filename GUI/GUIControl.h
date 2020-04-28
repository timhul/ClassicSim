#pragma once

#include "ClassicSimControl.h"

class GUIControl : public ClassicSimControl {
    Q_OBJECT
public:
    GUIControl(QObject* parent = nullptr);
    ~GUIControl();
};
