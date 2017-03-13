#ifndef TESTHELPERS_H
#define TESTHELPERS_H

class QString;

class TestHelpers
{
private:
    TestHelpers();

public:
    static QString resolveFullPath(const QString &relFileName);

    static void initTestHelpers(const QString &testExePath);
private:

};

#endif // TESTHELPERS_H
