#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
public:
    friend bool operator<(const Event&, const Event&);
    friend bool operator>(const Event&, const Event&);
    friend bool operator<=(const Event&, const Event&);
    friend bool operator>=(const Event&, const Event&);

    virtual ~Event() {}
    virtual void act(void) = 0;
    virtual std::string get_name(void) const;

    float get_priority(void) const;
protected:
    float priority;
    std::string name;
private:
};


class Compare {
public:
    bool operator() (Event*&, Event*&);
};


#endif // EVENT_H
