// Author: Joseph Bellahcen <joeclb@icloud.com>

#ifndef SPEETURE_PITCHPERIODESTIMATOR_H
#define SPEETURE_PITCHPERIODESTIMATOR_H

#include "FeatureExtractor.h"
#include <vector>

namespace Speeture {
    typedef enum {ACF, ACF_BIASED, ACF_UNBIASED, ACF_UNITY_AT_ZERO_LAG, AMDF, DF, CMNDF} PitchPeriodEstimators;

    class PitchPeriodEstimator {
        public:
            PitchPeriodEstimator(PitchPeriodEstimators _algorithm, unsigned int sampleRate, unsigned int minPitchHz, unsigned int maxPitchHz);
            unsigned int prediction(const std::vector<float>& segment);

        private:
            unsigned int minPitchPeriod, maxPitchPeriod;
            PitchPeriodEstimators algorithm;

            unsigned int findFirstLocalMax(const std::vector<float>& segment);
            unsigned int findFirstLocalMin(const std::vector<float>& segment);
    };
}

#endif //SPEETURE_PITCHPERIODESTIMATOR_H
