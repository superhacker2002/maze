#ifndef SRC_MODEL_HELPERS_RANDOMIZER_GENERATOR_H_
#define SRC_MODEL_HELPERS_RANDOMIZER_GENERATOR_H_
#include "interface.h"

struct RandomGenerator : public IRandomizer {
  int GetRandomPercent() override;
  virtual ~RandomGenerator() {}
};

#endif  // SRC_MODEL_HELPERS_RANDOMIZER_GENERATOR_H_