// Author: Joseph Bellahcen <joeclb@icloud.com>

#include "SimplePitchEstimator.h"
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

TEST(SimplePitchEstimatorTests, AcfLocalMaxAtPeriod) {
    auto acfEst = Speeture::SimplePitchEstimator(Speeture::ACF, 2500, 1, 2500);
    auto period = acfEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(SimplePitchEstimatorTests, AcfBiasedLocalMaxAtPeriod) {
    auto acfEst = Speeture::SimplePitchEstimator(Speeture::ACF_BIASED, 2500, 1, 2500);
    auto period = acfEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(SimplePitchEstimatorTests, AcfUnbiasedLocalMaxAtPeriod) {
    auto acfEst = Speeture::SimplePitchEstimator(Speeture::ACF_UNBIASED, 2500, 1, 2500);
    auto period = acfEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(SimplePitchEstimatorTests, AcfUnityAtZeroLagLocalMaxAtPeriod) {
    auto acfEst = Speeture::SimplePitchEstimator(Speeture::ACF_UNITY_AT_ZERO_LAG, 2500, 1, 2500);
    auto period = acfEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(SimplePitchEstimatorTests, AmdfLocalMinAtPeriod) {
    auto amdffEst = Speeture::SimplePitchEstimator(Speeture::AMDF, 2500, 1, 2500);
    auto period = amdffEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(SimplePitchEstimatorTests, DfLocalMinAtPeriod) {
    auto amdffEst = Speeture::SimplePitchEstimator(Speeture::DF, 2500, 1, 2500);
    auto period = amdffEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}

TEST(SimplePitchEstimatorTests, CmndfLocalMinAtPeriod) {
    auto amdffEst = Speeture::SimplePitchEstimator(Speeture::CMNDF, 2500, 1, 2500);
    auto period = amdffEst.estimatePeriod(sineWave(50));

    EXPECT_NEAR(period, 50, 5);
}
