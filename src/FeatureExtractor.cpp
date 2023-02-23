// Author: Joseph Bellahcen <joeclb@icloud.com>

#include "FeatureExtractor.h"
#include <cmath>
#include <vector>

using namespace Speeture;

FeatureExtractor::FeatureExtractor(unsigned int _maxLength): maxLength(_maxLength) {}

// Compute the autocorrelation function (ACF) of the segment
//
// The autocorrelation function (ACF) measures a signal's similarity with itself at each of its time lags. For a roughly
// periodic signal, the ACF will also be periodic, with the global maximum at lag zero and subsequent local maxima at
// multiples of the likely fundamental period of the signal. The global maximum at zero lag may be interpreted as
// the power of the signal
//
// Box, George E. P., Gwilym M. Jenkins, and Gregory C. Reinsel. Time Series Analysis: Forecasting and Control. 3rd ed.
// Englewood Cliffs, NJ: Prentice Hall, 1994.
std::vector<float> FeatureExtractor::acf(const std::vector<float>& segment, ScalingMode scalingMode) {
    auto result = std::vector<float>(maxLength, 0.0f);

    for (int i = 0; i < maxLength; i++)
        for (int j = 0; j < maxLength - i; j++)
            result[i] += segment[j] * segment[j + i];

    scaleResult(result, scalingMode);
    return result;
}

// Compute the average magnitude difference function (AMDF) of the segment
//
// The average magnitude difference function (AMDF) measures a signal's similarity with itself at each of its time lags.
// For a roughly periodic signal, the AMDF will also be periodic, with the global minimum at lag zero and a subsequent
// local minima at multiples of the likely fundamental period of the signal
//
// Cohen, A., et al. “Average Magnitude Difference Function Pitch Extractor.” IEEE Transactions on Acoustics, Speech,
// and Signal Processing, vol. ASSP-22, no. 5, Jan. 1974.
std::vector<float> FeatureExtractor::amdf(const std::vector<float>& segment) {
    auto result = std::vector<float>(maxLength, 0.0);

    for (int i = 0; i < maxLength; i++) {
        for (int j = 0; j < maxLength - i; j++)
            result[i] += fabsf(segment[j] - segment[j + i]);

        result[i] /= float(maxLength);
    }

    return result;
}

// Compute the difference function (DF) of the segment
//
// The difference function (DF) approximates a signal's periodicity at each of its time lags. For a roughly periodic
// signal, the DF will also be periodic, with the global minimum at lag zero and a subsequent local minima at multiples
// of the likely fundamental period of the signal
//
// Cheveigné, Alain de, and Hideki Kawahara. “YIN, a Fundamental Frequency Estimator for Speech and Music.” Journal of
// the Acoustical Society of America, vol. 111, no. 4, Apr. 2002.
std::vector<float> FeatureExtractor::df(const std::vector<float>& segment) {
    auto result = std::vector<float>(maxLength, 0.0);

    for (int i = 0; i < maxLength; i++)
        for (int j = 0; j < maxLength - i; j++)
            result[i] += powf(segment[j] - segment[j + i], 2);

    return result;
}

// Compute the cumulative mean normalized difference function (CMNDF) of the segment
//
// The cumulative mean normalized difference function (CMNDF) is a modified DF which serves as the basis of the YIN
// pitch estimator. Unlike the DF, the CMNDF is defined as unity at zero-lag, and subsequent lags are scaled by the
// average of previous ones
//
// Cheveigné, Alain de, and Hideki Kawahara. “YIN, a Fundamental Frequency Estimator for Speech and Music.” Journal of
// the Acoustical Society of America, vol. 111, no. 4, Apr. 2002.
std::vector<float> FeatureExtractor::cmndf(const std::vector<float>& segment) {
    auto result = std::vector<float>(maxLength, 0.0);
    auto diff = df(segment);

    result[0] = 1;

    for (int i = 1; i < maxLength; i++) {
        float diffSum = 0;

        for (int j = 1; j <= i; j++)
            diffSum += diff[j];

        result[i] = diff[i] * float(i) / diffSum;
    }

    return result;
}

// Scale the feature by the ScalingMode
void FeatureExtractor::scaleResult(std::vector<float> &acf, ScalingMode scalingMode) {
    float scalingFactor;

    switch (scalingMode) {
        case NONE:
            return;
        case BIASED: case UNBIASED:
            scalingFactor = 1.0f / float(maxLength);
            break;
        case UNITY_AT_ZERO_LAG:
            scalingFactor = 1.0f / acf[0];
            break;
    }

    for (int i = 0; i < maxLength; i++) {
        if (scalingMode == UNBIASED)
            acf[i] *= 1.0f / float(maxLength - i);

        else
            acf[i] *= scalingFactor;
    }
}
