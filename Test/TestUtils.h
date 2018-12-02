#ifndef TESTUTILS_H
#define TESTUTILS_H

class TestUtils {
public:
    double delta(double lhs, double rhs) {
        return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
    }

    bool almost_equal(double lhs, double rhs) {
        return delta(lhs, rhs) < 0.0001;
    }
};

#endif // TESTUTILS_H
