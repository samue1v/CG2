#include "sampler.h"

class PureRandom : public Sampler{
    public:
    PureRandom();
    PureRandom(int numSamples,int numChunks);
    ~PureRandom();
    Pair getSample() override;

};