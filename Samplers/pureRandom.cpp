#include "pureRandom.h"

PureRandom::PureRandom() : Sampler(){}

PureRandom::~PureRandom(){}

Pair PureRandom::getSample(){
    return Pair(getRandomNumber(),getRandomNumber());
}