// Author: Joseph Bellahcen <joeclb@icloud.com>

#include "PitchPeriodEstimator.h"
#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

std::vector<float> sineWave(unsigned int freqHz, unsigned int length = 200) {
    auto signal = std::vector<float>();

    for (int i = 0; i < 200; i++) {
        float sample = 20.0f * cosf(2.0f * float(M_PI) * float(i) / float(freqHz));
        signal.push_back(sample);
    }

    return signal;
}

TEST(PitchPeriodEstimatorTests, AcfLocalMaxAtPeriod) {
    auto acfEst = Speeture::PitchPeriodEstimator(Speeture::ACF, 2500, 1, 2500);
    auto period = acfEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(PitchPeriodEstimatorTests, AcfBiasedLocalMaxAtPeriod) {
    auto acfEst = Speeture::PitchPeriodEstimator(Speeture::ACF_BIASED, 2500, 1, 2500);
    auto period = acfEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(PitchPeriodEstimatorTests, AcfUnbiasedLocalMaxAtPeriod) {
    auto acfEst = Speeture::PitchPeriodEstimator(Speeture::ACF_UNBIASED, 2500, 1, 2500);
    auto period = acfEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(PitchPeriodEstimatorTests, AcfUnityAtZeroLagLocalMaxAtPeriod) {
    auto acfEst = Speeture::PitchPeriodEstimator(Speeture::ACF_UNITY_AT_ZERO_LAG, 2500, 1, 2500);
    auto period = acfEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(PitchPeriodEstimatorTests, AmdfLocalMinAtPeriod) {
    auto amdffEst = Speeture::PitchPeriodEstimator(Speeture::AMDF, 2500, 1, 2500);
    auto period = amdffEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(PitchPeriodEstimatorTests, DfLocalMinAtPeriod) {
    auto amdffEst = Speeture::PitchPeriodEstimator(Speeture::DF, 2500, 1, 2500);
    auto period = amdffEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(PitchPeriodEstimatorTests, CmndfLocalMinAtPeriod) {
    auto amdffEst = Speeture::PitchPeriodEstimator(Speeture::CMNDF, 2500, 1, 2500);
    auto period = amdffEst.prediction(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}
