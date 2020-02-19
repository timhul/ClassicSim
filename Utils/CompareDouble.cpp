#include "CompareDouble.h"

double delta(double lhs, double rhs) {
    return (lhs - rhs) < 0 ? (lhs - rhs) * -1 : (lhs - rhs);
}

bool almost_equal(double lhs, double rhs) {
    return delta(lhs, rhs) < 0.0001;
}

bool lhs_almost_equal_or_less(double lhs, double rhs) {
    return almost_equal(lhs, rhs) || lhs < rhs;
}
