#ifndef GENERICTALENT_H
#define GENERICTALENT_H

#include "Talent.h"

class GenericTalent: public Talent {
    Q_OBJECT
public:
    GenericTalent(Character *pchar,
                  const QString &name,
                  const QString &position,
                  const QString &icon,
                  const int max_points,
                  const QString &req_string_parent_,
                  const QString &req_string_base_,
                  const QString &rank_description,
                  const int base_val,
                  const int increment,
                  bool use_increment);
    virtual ~GenericTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
    const QString req_string_parent;
    const QString req_string_base;
};

#endif // GENERICTALENT_H
