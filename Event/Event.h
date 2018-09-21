#ifndef EVENT_H
#define EVENT_H

#include <QString>

class Event {
public:
    friend bool operator<(const Event&, const Event&);
    friend bool operator>(const Event&, const Event&);
    friend bool operator<=(const Event&, const Event&);
    friend bool operator>=(const Event&, const Event&);

    virtual ~Event() {}
    virtual void act(void) = 0;
    virtual QString get_name(void) const;

    double get_priority(void) const;
protected:
    double priority;
    QString name;
private:
};


class Compare {
public:
    bool operator() (Event*&, Event*&);
};


#endif // EVENT_H
