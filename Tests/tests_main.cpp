#include <gtest/gtest.h>

#include "testhelpers.h"

#include <QString>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    TestHelpers::initTestHelpers(QString(argv[0]));
    return RUN_ALL_TESTS();
}
