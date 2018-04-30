#ifndef BUFFS_H
#define BUFFS_H

#include <QObject>
#include <QVector>

class Character;
class Buff;
class HolyStrength;

class Buffs: public QObject {
    Q_OBJECT

public:
    Buffs(Character* pchar, QObject* parent = 0);
    ~Buffs();

    void add_buff(Buff* buff);
    void reset();

    HolyStrength* get_holy_strength_mh() const;
    HolyStrength* get_holy_strength_oh() const;

private:
    Character* pchar;
    QVector<Buff*> buffs;

    HolyStrength* holy_strength_mh;
    HolyStrength* holy_strength_oh;
};

#endif // BUFFS_H
