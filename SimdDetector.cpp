#include "SimdDetector.h"
#include "vectorclass/instrset.h"

namespace NSSimd {

SimdDetector::SimdDetector() : InstructionLevel_(instrset_detect()) {
}

int SimdDetector::level() const {
  return InstructionLevel_;
}

} // namespace NSSimd
