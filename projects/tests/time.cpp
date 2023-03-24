#include <OPoverload/time.hpp>
#include <gtest/gtest.h>

TEST(timelib, overloads)
{
    using namespace timelib::literals;

    const std::size_t num1 = 432000;
    const std::size_t num2 = 86401;

    timelib::Time time(num1);
    timelib::TimeSpan time_span(num2);

    ASSERT_LT(time_span, time);                  // 86401 < 432000
    ASSERT_EQ(time, time);                       // 432000 == 432000
    ASSERT_EQ(time + 5_d, 10_d);                 // 432000 + 432000 = 864000
    ASSERT_EQ(time + time_span, 518401_s);       // 86401 + 432000 == 518401
    ASSERT_EQ(time - time_span, 345599_s);       // 432000 - 86401 = 345599
    ASSERT_EQ(time - time, 0_d);                 // 432000 - 432000 = 0
    ASSERT_EQ(time_span + time_span, 172802_s);  // 86401 + 86401 = 172802
    ASSERT_EQ(time_span - time_span, 0_m);       // 86401 - 86401 = 0
    ASSERT_NE(time, time_span);                  // 432000 != 86401
}