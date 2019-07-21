#pragma once

class Buff;
class Proc;
class Spell;

#include <QMap>
#include <QString>

namespace DisabledAtZero {
    static const bool Yes = true;
    static const bool No = false;
}


class TalentRequirerInfo {
public:
    TalentRequirerInfo(const QString& name, const int max_talent_rank, const bool disabled_at_zero) :
        name(name),
        max(max_talent_rank),
        disabled_at_zero(disabled_at_zero),
        curr(0)
    {}

    const QString name;
    const int max;
    const bool disabled_at_zero;
    int curr;
};


class TalentRequirer {
public:
    TalentRequirer(const QVector<TalentRequirerInfo*>& talent_info);
    virtual ~TalentRequirer();

protected:
    friend class Talent;
    QMap<QString, TalentRequirerInfo*> talent_info;

    void increase_talent_rank(Buff* buff, const QString& talent);
    void decrease_talent_rank(Buff* buff, const QString& talent);

    void increase_talent_rank(Spell* spell, const QString& talent);
    void decrease_talent_rank(Spell* spell, const QString& talent);

    void increase_talent_rank(Proc* proc, const QString& talent);
    void decrease_talent_rank(Proc* proc, const QString& talent);

    virtual void increase_talent_rank_effect(const QString& talent_name, const int curr) = 0;
    virtual void decrease_talent_rank_effect(const QString& talent_name, const int curr) = 0;
};
