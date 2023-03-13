#include <iostream>
#include <stdexcept>

namespace timelib {

class TimeInterface
{
   public:
    std::size_t time_;

   protected:
    explicit TimeInterface(std::size_t time) : time_(time)
    {
    }
};

class Time : public TimeInterface
{
   public:
    explicit Time(std::size_t time) : TimeInterface(time)
    {
    }
};

class TimeSpan : public TimeInterface
{
   public:
    explicit TimeSpan(std::size_t time) : TimeInterface(time)
    {
    }
};

inline TimeSpan operator-(const Time& lhs, const Time& rhs)
{
    if (lhs.time_ - rhs.time_ > lhs.time_)
    {
        throw std::overflow_error{"result time below zero"};
    }
    return TimeSpan(lhs.time_ - rhs.time_);
}

inline Time operator+(const Time& lhs, const TimeSpan& rhs)
{
    if (lhs.time_ - rhs.time_ < lhs.time_)
    {
        throw std::overflow_error{"overflow"};
    }
    return Time(lhs.time_ + rhs.time_);
}

inline Time operator-(const Time& lhs, const TimeSpan& rhs)
{
    if (lhs.time_ - rhs.time_ > lhs.time_)
    {
        throw std::overflow_error{"result time below zero"};
    }
    return Time(lhs.time_ - rhs.time_);
}

inline TimeSpan operator+(const TimeSpan& lhs, const TimeSpan& rhs)
{
    if (lhs.time_ - rhs.time_ < lhs.time_)
    {
        throw std::overflow_error{"overflow"};
    }
    return TimeSpan(lhs.time_ + rhs.time_);
}

inline TimeSpan operator-(const TimeSpan& lhs, const TimeSpan& rhs)
{
    if (lhs.time_ - rhs.time_ > lhs.time_)
    {
        throw std::overflow_error{"result time below zero"};
    }
    return TimeSpan(lhs.time_ - rhs.time_);
}

inline std::ostream& operator<<(std::ostream& os, const TimeInterface& val)
{
    std::size_t day = val.time_ / (86400);
    std::size_t hour = (val.time_ - day * 86400) / 3600;
    std::size_t min = (val.time_ - day * 86400 - hour * 3600) / 60;
    std::size_t sec = (val.time_ - day * 86400 - hour * 3600 - min * 60);
    return os << day << "d " << hour << "h " << min << "m " << sec << "s " << '\n';
}

}  // namespace timelib