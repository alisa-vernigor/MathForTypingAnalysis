#include "TimeMeasurer.h"

std::chrono::microseconds CTimeAnchor::get_time() {
  using namespace std::chrono;
  auto time = duration_cast<microseconds>(steady_clock::now() - begin_);
  return time;
}

