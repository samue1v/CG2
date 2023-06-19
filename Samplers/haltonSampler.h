#include "sampler.h"

class HaltonSampler : public Sampler{
    public:
    HaltonSampler();
    ~HaltonSampler()=default;
    HaltonSampler(int numSamples,int numChunks);
    Pair getSample();
    private:
    double genSamples(int chunkIndex,int base);
};