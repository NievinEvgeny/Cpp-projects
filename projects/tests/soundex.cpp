#include <soundex/soundex.hpp>
#include <gtest/gtest.h>
#include <string>

TEST(soundexhash, bad_symbol_in_name)
{
    EXPECT_ANY_THROW(soundex::soundex_hash("1Tim"));
    EXPECT_ANY_THROW(soundex::soundex_hash("Ti@m"));
    EXPECT_ANY_THROW(soundex::soundex_hash("Tim "));
    EXPECT_ANY_THROW(soundex::soundex_hash(" Tim"));
    EXPECT_ANY_THROW(soundex::soundex_hash("Тim"));  // Russian T
}

TEST(soundexhash, only_letters_to_be_removed)
{
    std::string res;
    res = soundex::soundex_hash("Aya");
    ASSERT_EQ(res, "A000");
    res = soundex::soundex_hash("hAya");
    ASSERT_EQ(res, "H000");
    res = soundex::soundex_hash("hhhwwAya");
    ASSERT_EQ(res, "H000");
    res = soundex::soundex_hash("whAya");
    ASSERT_EQ(res, "W000");
    res = soundex::soundex_hash("wWhAya");
    ASSERT_EQ(res, "W000");
}

TEST(soundexhash, sequential_first_letter)
{
    std::string res;
    res = soundex::soundex_hash("vvvvvvv");
    ASSERT_EQ(res, "V000");
    res = soundex::soundex_hash("vvvvvvvd");
    ASSERT_EQ(res, "V300");
    res = soundex::soundex_hash("aaaavdavd");
    ASSERT_EQ(res, "A131");
}

TEST(soundexhash, consonants_between_h_or_w)
{
    std::string res;
    res = soundex::soundex_hash("Rhbhrt");
    ASSERT_EQ(res, "R163");
    res = soundex::soundex_hash("Rhbhn");
    ASSERT_EQ(res, "R150");
    res = soundex::soundex_hash("Rhhbhn");
    ASSERT_EQ(res, "R150");
}

TEST(soundexhash, sequential_consonants_between_h_or_w)
{
    std::string res;
    res = soundex::soundex_hash("Rphprhrwdwt");
    ASSERT_EQ(res, "R163");
    res = soundex::soundex_hash("Rbhbrhrhthht");
    ASSERT_EQ(res, "R163");
    res = soundex::soundex_hash("Rhwfppwwbhhmmhnm");
    ASSERT_EQ(res, "R150");
    res = soundex::soundex_hash("Ashcraft");
    ASSERT_EQ(res, "A261");
    res = soundex::soundex_hash("Ashcroft");
    ASSERT_EQ(res, "A261");
}

TEST(soundexhash, consonants_between_vowels)
{
    std::string res;
    res = soundex::soundex_hash("Robert");
    ASSERT_EQ(res, "R163");
    res = soundex::soundex_hash("Rupert");
    ASSERT_EQ(res, "R163");
    res = soundex::soundex_hash("Rupin");
    ASSERT_EQ(res, "R150");
}

TEST(soundexhash, sequential_consonants_between_vowels)
{
    std::string res;
    res = soundex::soundex_hash("Rpapruredot");
    ASSERT_EQ(res, "R116");
    res = soundex::soundex_hash("Rbabraroteet");
    ASSERT_EQ(res, "R116");
    res = soundex::soundex_hash("Raofppeebaumminm");
    ASSERT_EQ(res, "R115");
}
