#pragma once
#include <cmath>
#include <string>

enum class Ordering {
    NO,
    IO
};

class MixingParams {
public:
    std::string label;
    double theta12;
    double theta13;
    double theta23;
    double deltacp;
    double sdm;
    double ldm;

    MixingParams(Ordering ordering) {
        sdm = 7.5e-5;
        theta12 = asin(sqrt(0.318));

        if (ordering == Ordering::NO) {
            label = "NO";
            theta13 = asin(sqrt(0.022));
            theta23 = asin(sqrt(0.574));
            deltacp = 1.08*M_PI;
            ldm = 2.55e-3;
        } else {
            label = "IO";
            theta13 = asin(sqrt(0.02225));
            theta23 = asin(sqrt(0.578));
            deltacp = 1.58*M_PI;
            ldm = 2.45e-3;
        }
    }
};
