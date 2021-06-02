#ifndef TIMEMEASURER_H
#define TIMEMEASURER_H

#include <chrono>
#include <string>

namespace NSTimeMeasurer {

class CTimeAnchor {
  using steady_clock = std::chrono::steady_clock;

public:
  std::chrono::microseconds get_time();
private:
  steady_clock::time_point begin_ = steady_clock::now();
};
}

#endif // TIMEMEASURER_H
