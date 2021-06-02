#include "SimdDetector.h"
#include "vectorclass/instrset.h"

namespace NSSimd {

СSimdDetector::СSimdDetector() : InstructionLevel_(instrset_detect()) {
}

int СSimdDetector::level() const {
  return InstructionLevel_;
}

} // namespace NSSimd
