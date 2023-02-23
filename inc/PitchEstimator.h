// Author: Joseph Bellahcen <joeclb@icloud.com>
#ifndef SPEETURE_ABSTRACTPITCHESTIMATOR_H
#define SPEETURE_ABSTRACTPITCHESTIMATOR_H

#include <vector>

namespace Speeture {
    class PitchEstimator {
    public:
        PitchEstimator(unsigned int sampleRate, unsigned int minPitchHz, unsigned int maxPitchHz);
        virtual unsigned int estimatePeriod(const std::vector<float>& segment) = 0;

    protected:
        unsigned int minPitchPeriod, maxPitchPeriod;
    };
}

#endif //SPEETURE_ABSTRACTPITCHESTIMATOR_H
