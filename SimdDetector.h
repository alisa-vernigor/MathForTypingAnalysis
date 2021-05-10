#ifndef SIMDDETECTOR_H
#define SIMDDETECTOR_H

namespace NSSimd {

class SimdDetector {
public:
  SimdDetector();
  int level() const;

private:
  int InstructionLevel_;
};

} // namespace NSSimd

#endif // SIMDDETECTOR_H
