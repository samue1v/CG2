#include "sampler.h"

class PureRandom : public Sampler{
    public:
    PureRandom();
    ~PureRandom();
    Pair getSample() override;

};