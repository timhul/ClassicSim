#ifndef COMBATLOG_H
#define COMBATLOG_H

#include <QVector>
#include <QMap>

class CombatLog {
public:
    void add_entry(const QString&);
    void dump(void);

protected:
private:
    QVector<QString> combatlog;
};

#endif // COMBATLOG_H
