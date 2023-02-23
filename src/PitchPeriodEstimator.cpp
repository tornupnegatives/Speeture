// Author: Joseph Bellahcen <joeclb@icloud.com>

#include "FeatureExtractor.h"
#include "PitchPeriodEstimator.h"
#include <algorithm>
#include <vector>

using namespace Speeture;

PitchPeriodEstimator::PitchPeriodEstimator(PitchPeriodEstimators _algorithm, unsigned int sampleRate,
                                           unsigned int minPitchHz, unsigned int maxPitchHz) {
    algorithm = _algorithm;
    maxPitchPeriod = sampleRate / minPitchHz;
    minPitchPeriod = sampleRate / maxPitchHz;
}

unsigned int PitchPeriodEstimator::prediction(const std::vector<float> &segment) {
    auto featureExtractor = FeatureExtractor(segment.size());
    unsigned int pitchPeriod;

    switch (algorithm) {
        case ACF: {
            auto acf = featureExtractor.acf(segment, NONE);
            pitchPeriod = findFirstLocalMax(acf);
        }

        case ACF_BIASED: {
            auto acf = featureExtractor.acf(segment, BIASED);
            pitchPeriod = findFirstLocalMax(acf);
        }

        case ACF_UNBIASED: {
            auto acf = featureExtractor.acf(segment, UNBIASED);
            pitchPeriod = findFirstLocalMax(acf);
        }

        case ACF_UNITY_AT_ZERO_LAG: {
            auto acf = featureExtractor.acf(segment, UNITY_AT_ZERO_LAG);
            pitchPeriod = findFirstLocalMax(acf);
        }

        case AMDF: {
            auto amdf = featureExtractor.amdf(segment);
            pitchPeriod = findFirstLocalMin(amdf);
        }

        case DF: {
            auto df = featureExtractor.df(segment);
            pitchPeriod = findFirstLocalMin(df);
        }

        case CMNDF: {
            auto cmndf = featureExtractor.cmndf(segment);
            pitchPeriod = findFirstLocalMin(cmndf);
        }
    }

    return pitchPeriod;
}

unsigned int PitchPeriodEstimator::findFirstLocalMax(const std::vector<float> &segment) {
    // Place the search head at the first local minimum
    auto localMin = std::min_element(segment.begin(), segment.end());
    auto localMaxIdx = int(std::distance(segment.begin(), std::max_element(localMin, segment.end())));

    return localMaxIdx;
}

unsigned int PitchPeriodEstimator::findFirstLocalMin(const std::vector<float> &segment) {
    // Place the search head at the first local maximum
    auto localMax = std::max_element(segment.begin(), segment.end());
    auto localMaxIdx = int(std::distance(segment.begin(), localMax));

    // Traverse array until it is no longer decreasing
    auto localMinIdx = localMaxIdx;
    for (int i = localMinIdx + 1; i < segment.size() - 1; i++) {
        localMinIdx = i;

        if (segment[i] < segment[i - 1] && segment[i] < segment[i + 1])
            break;
    }


    return localMinIdx;
}
