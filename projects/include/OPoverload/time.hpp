#include <iostream>

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

}  // namespace timelib