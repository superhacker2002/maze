#ifndef SRC_TESTS_CAVE_MOC_GENERATOR_H_
#define SRC_TESTS_CAVE_MOC_GENERATOR_H_
#include "../../src/model/helpers/randomizer/interface.h"

struct MocRandomGenerator : public IRandomizer {
  int GetRandomPercent() override;
  ~MocRandomGenerator() {}
};

#endif  // SRC_TESTS_CAVE_MOC_GENERATOR_H_
