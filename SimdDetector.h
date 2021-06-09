#ifndef SIMDDETECTOR_H
#define SIMDDETECTOR_H

namespace NSSimd {

class СSimdDetector {
public:
  СSimdDetector();
  int level() const;

private:
  int InstructionLevel_;
};

} // namespace NSSimd

#endif // SIMDDETECTOR_H
