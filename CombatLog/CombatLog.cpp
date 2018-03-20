
#include "CombatLog.h"
#include <QDebug>

void CombatLog::add_entry(QString entry) {
    combatlog.append(entry);
}

void CombatLog::dump(void) {
    for (int i = 0; i < combatlog.size(); ++i) {
        qDebug() << combatlog[i];
    }
}
