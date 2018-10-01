
#include "TestProc.h"

#include <utility>

TestProc::TestProc(QString proc_under_test) :
    TestSpell(std::move(proc_under_test))
{}
