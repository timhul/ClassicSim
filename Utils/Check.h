#ifndef UTILSCHECK_H
#define UTILSCHECK_H

#include <stdexcept>

#define check(p, msg) if (p == false) throw std::logic_error(msg)

#endif // UTILSCHECK_H
