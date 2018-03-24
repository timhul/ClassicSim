#ifndef TALENT_H
#define TALENT_H

#include <QObject>
#include <QString>
#include <QVector>
#include <assert.h>

class Talent: public QObject {
    Q_OBJECT
public:
    Talent(const QString& name_, const QString &icon_, const int max_points_);
    virtual ~Talent();

    Q_PROPERTY(QString icon READ get_icon NOTIFY iconChanged)

    QString get_name() const;
    QString get_icon() const;
    // TODO: Mark as abstract class when talents are fully implemented.
    virtual void effect() {} //= 0;
    int get_current_rank() const;
    int get_max_rank() const;
    bool increment_rank();
    bool decrement_rank();
    void set_rank(const int);

    bool is_active() const;
    bool is_maxed() const;

Q_SIGNALS:
    void iconChanged();

protected:
    const QString name;
    const QString icon; // do greyscale with Colorize or apply greyscale in Photoshop?
    const int max_points;
    int curr_points;

    Talent* parent;
    QVector<Talent*> children;

    bool children_active() const;

private:

};


#endif // TALENT_H
