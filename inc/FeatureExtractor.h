// Author: Joseph Bellahcen <joeclb@icloud.com>

#ifndef SPEETURE_FEATUREEXTRACTOR_H
#define SPEETURE_FEATUREEXTRACTOR_H

#include <vector>

namespace Speeture {
    typedef enum {NONE, BIASED, UNBIASED, UNITY_AT_ZERO_LAG} ScalingMode;

    class FeatureExtractor {
        public:
            explicit FeatureExtractor(unsigned int _maxLength);
            std::vector<float> acf(const std::vector<float>& segment, ScalingMode scalingMode = BIASED);
            std::vector<float> amdf(const std::vector<float>& segment);
            std::vector<float> df(const std::vector<float>& segment);
            std::vector<float> cmndf(const std::vector<float>& segment);

        private:
            unsigned int maxLength;

            void scaleResult(std::vector<float>& acf, ScalingMode scalingMode);
    };
}

#endif //SPEETURE_FEATUREEXTRACTOR_H
