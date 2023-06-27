#include "pureRandom.h"

PureRandom::PureRandom() : Sampler(){}

PureRandom::PureRandom(int numSamples,int numChunks) : Sampler(numSamples,numChunks){}

PureRandom::~PureRandom(){}

Pair PureRandom::getSample(){
    return getRandomSample();
}