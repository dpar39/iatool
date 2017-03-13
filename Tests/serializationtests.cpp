#include "Tests/testhelpers.h"

#include <QString>
#include <gtest/gtest.h>

#include "Model/annotatedimage.h"

class SerializationTests : public ::testing::Test
{
public:
};


TEST_F(SerializationTests, deserializationWorks)
{
    QString imgFullPath = TestHelpers::resolveFullPath("Tests/images/000.jpg");

    auto img = AnnotatedImage::fromFile(imgFullPath);

    auto numAnnotations = img->annotations()->size();

    EXPECT_EQ(numAnnotations, 0);
}
