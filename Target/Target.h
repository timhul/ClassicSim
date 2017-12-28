#ifndef TARGET_H
#define TARGET_H

class Target {
public:
    Target(const int _tlvl): tlvl(_tlvl) {}

    int get_lvl(void) const { return tlvl; }
    int get_defense(void) const { return tlvl * 5; }
protected:
private:
    const int tlvl;
};


#endif // TARGET_H
