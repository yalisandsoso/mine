#ifndef BASE64_TEST_H
#define BASE64_TEST_H

#include "src/base64.h"
#include "test.h"

namespace mine {

static TestData<std::string, std::string> Base64TestData = {
    // examples from https://en.wikipedia.org/wiki/Base64#Output_padding
    TestCase("YWJjZA==", "abcd"),
    TestCase("YW55IGNhcm5hbCBwbGVhc3VyZS4=", "any carnal pleasure."),
    TestCase("YW55IGNhcm5hbCBwbGVhc3VyZQ==", "any carnal pleasure"),
    TestCase("YW55IGNhcm5hbCBwbGVhc3Vy", "any carnal pleasur"),
    TestCase("YW55IGNhcm5hbCBwbGVhc3U=", "any carnal pleasu"),
    TestCase("YW55IGNhcm5hbCBwbGVhcw==", "any carnal pleas"),
    // some manual examples
    TestCase("cGxhaW4gdGV4dA==", "plain text"),
    TestCase("SGVsbG8=", "Hello"),
    // Some unicode examples
    TestCase("SGVsbG/nq5w=", "Hello竜"),
    TestCase("4oKsNTA=", "€50"),
    TestCase("dGhpcyBpcyByb2NrZXQg8J+agCBhbmQgaSBsb3ZlIGl0", "this is rocket 🚀 and i love it"),
};

static TestData<std::string, bool> IsBase64Data = {
    TestCase("da024686f7f2da49da6c98253b42fe1c:erezutlgudgbtwza:i3eclcagfnUbK1B==", false),
    TestCase("da024686f7f2da49da6c98253b42fe1c:i3eclcagfnUbK1B==", false),
    TestCase("erezutlgudgbtwza:i3eclcagfnUbK1B==", false),
    TestCase("dGhpcyBpcyByb2NrZXQg8J+agCBhbmQgaSBsb3ZlIGl0", true),
    TestCase("SGVsbG/nq5w=", true),
    TestCase("i3eclcagfnUbK1B==", true),
};

TEST(Base64Test, Encode)
{
    for (const auto& item : Base64TestData) {
        std::string encoded = Base64::base64Encode(PARAM(1));
        ASSERT_STREQ(PARAM(0).c_str(), encoded.c_str());
    }
}

TEST(Base64Test, Decode)
{
    for (const auto& item : Base64TestData) {
        std::string decoded = Base64::base64Decode(PARAM(0));
        //ASSERT_STREQ(PARAM(1), decoded);
    }
}

TEST(Base64Test, ExpectedSize)
{
    for (const auto& item : Base64TestData) {
        std::size_t s = Base64::expectedBase64Length(PARAM(1));
        ASSERT_EQ(PARAM(0).size(), s);
    }
}

TEST(Base64Test, IsBase64)
{
    for (const auto& item : IsBase64Data) {
        auto first = PARAM(0);
        auto second = PARAM(1);
        ASSERT_EQ(Base64::isBase64(first), second);
    }
}

}

#endif // BASE64_TEST_H
