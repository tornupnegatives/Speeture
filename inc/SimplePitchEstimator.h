// Author: Joseph Bellahcen <joeclb@icloud.com>

#ifndef SPEETURE_SIMPLEPITCHESTIMATOR_H
#define SPEETURE_SIMPLEPITCHESTIMATOR_H

#include "FeatureExtractor.h"
#include "PitchEstimator.h"
#include <vector>

namespace Speeture {
    typedef enum {ACF, ACF_BIASED, ACF_UNBIASED, ACF_UNITY_AT_ZERO_LAG, AMDF, DF, CMNDF} SimplePitchAlgorithms;

    class SimplePitchEstimator: public PitchEstimator {
        public:
            SimplePitchEstimator(SimplePitchAlgorithms _algorithm, unsigned int sampleRate, unsigned int minPitchHz, unsigned int maxPitchHz);
            unsigned int estimatePeriod(const std::vector<float>& segment);

        private:
            SimplePitchAlgorithms algorithm;

            unsigned int findFirstLocalMax(const std::vector<float>& segment);
            unsigned int findFirstLocalMin(const std::vector<float>& segment);
    };
}

#endif //SPEETURE_SIMPLEPITCHESTIMATOR_H
