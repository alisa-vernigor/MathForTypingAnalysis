#include "TimeMeasurer.h"
#include <iostream>

CTimeAnchor::CTimeAnchor(const char* message) : message_(message) {
}

CTimeAnchor::~CTimeAnchor() {
  using namespace std::chrono;
  auto time = duration_cast<microseconds>(steady_clock::now() - begin_);
  std::cout << message_ << time.count() << std::endl;
}

CTimeAnchor CTimeMeasurer::count(const char* message) {
  return CTimeAnchor(message);
}
