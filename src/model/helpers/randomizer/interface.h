#ifndef SRC_MODEL_HELPERS_RANDOMIZER_INTERFACE_H_
#define SRC_MODEL_HELPERS_RANDOMIZER_INTERFACE_H_

struct IRandomizer {
  virtual int GetRandomPercent() = 0;
  virtual ~IRandomizer() {}
};

#endif  // SRC_MODEL_HELPERS_RANDOMIZER_INTERFACE_H_