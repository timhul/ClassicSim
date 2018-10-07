#ifndef TESTUTILS_H
#define TESTUTILS_H

class TestUtils {
public:
    double delta(double lhs, double rhs) {
        return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
    }
};

#endif // TESTUTILS_H
