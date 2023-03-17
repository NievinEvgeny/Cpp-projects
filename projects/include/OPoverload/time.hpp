#include <iostream>
#include <stdexcept>

namespace timelib {

constexpr static std::size_t DAY = 86400;
constexpr static std::size_t HOUR = 3600;
constexpr static std::size_t MIN = 60;

class TimeInterface
{
   private:
    std::size_t time_;

   public:
    auto time() const
    {
        return time_;
    }

    auto operator<=>(const TimeInterface&) const = default;

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
    return TimeSpan(lhs.time() - rhs.time());
}

inline Time operator+(const Time& lhs, const TimeSpan& rhs)
{
    return Time(lhs.time() + rhs.time());
}

inline Time operator-(const Time& lhs, const TimeSpan& rhs)
{
    return Time(lhs.time() - rhs.time());
}

inline TimeSpan operator+(const TimeSpan& lhs, const TimeSpan& rhs)
{
    return TimeSpan(lhs.time() + rhs.time());
}

inline TimeSpan operator-(const TimeSpan& lhs, const TimeSpan& rhs)
{
    return TimeSpan(lhs.time() - rhs.time());
}

inline std::ostream& operator<<(std::ostream& os, const TimeInterface& val)
{
    std::size_t day = val.time() / (DAY);
    std::size_t hour = (val.time() - day * DAY) / HOUR;
    std::size_t min = (val.time() - day * DAY - hour * HOUR) / MIN;
    std::size_t sec = (val.time() - day * DAY - hour * HOUR - min * MIN);
    return os << day << "d " << hour << "h " << min << "m " << sec << "s " << '\n';
}

namespace literals {

inline TimeSpan operator""_d(unsigned long long n)
{
    return TimeSpan{n * DAY};
}

inline TimeSpan operator""_h(unsigned long long n)
{
    return TimeSpan{n * HOUR};
}

inline TimeSpan operator""_m(unsigned long long n)
{
    return TimeSpan{n * MIN};
}

inline TimeSpan operator""_s(unsigned long long n)
{
    return TimeSpan{n};
}

}  // namespace literals

}  // namespace timelib