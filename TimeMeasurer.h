#ifndef TIMEMEASURER_H
#define TIMEMEASURER_H

#include <chrono>
#include <string>

class CTimeAnchor {
  using steady_clock = std::chrono::steady_clock;

public:
  CTimeAnchor(const char*);
  ~CTimeAnchor();

private:
  steady_clock::time_point begin_ = steady_clock::now();
  std::string message_;
};

class CTimeMeasurer {
public:
  static CTimeAnchor count(const char*);
};

#endif // TIMEMEASURER_H
