#include "sampler.h"

class HaltonSampler : public Sampler{
    public:
    HaltonSampler();
    ~HaltonSampler()=default;
    HaltonSampler(int numSamples,int numChunks,bool fixed);
    Pair getSample();
    private:
    double genSamples(int chunkIndex,int base,int baseIndex);
    std::vector<std::vector<double>> perms;
};