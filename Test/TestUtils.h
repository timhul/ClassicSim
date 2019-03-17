#ifndef TESTUTILS_H
#define TESTUTILS_H

class TestUtils {
public:
    static double delta(double lhs, double rhs) {
        return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
    }

    static bool almost_equal(double lhs, double rhs) {
        return delta(lhs, rhs) < 0.0001;
    }

    enum Weapons {
        Test100Dmg = 1000000,
        Test100DmgDagger,
        Test3Speed,
        Test2Speed,
        Test100Dmg2h,
        TestAxe,
        Test5SwordSkill,
        Test10SwordSkill,
        Test15SwordSkill,
        Test100DmgRanged,
        Test3SpeedRanged,
        Test2SpeedRanged
    };
};

#endif // TESTUTILS_H
