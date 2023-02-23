// Author: Joseph Bellahcen <joeclb@icloud.com>

#include "PitchEstimator.h"

using namespace Speeture;

PitchEstimator::PitchEstimator(unsigned int sampleRate, unsigned int minPitchHz, unsigned int maxPitchHz) {
    maxPitchPeriod = sampleRate / minPitchHz;
    minPitchPeriod = sampleRate / maxPitchHz;
}
