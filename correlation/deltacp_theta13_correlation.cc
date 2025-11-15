#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <globes/globes.h>
#include "../common/mixingParams.hpp"

using namespace std;

char AEDL_EXP[] = "DUNE_GLoBES.glb";
void computeChiSquare(glb_params g);

int main(int args, char* argv[]){
    glbInit(argv[0]);
    glbInitExperiment(AEDL_EXP, &glb_experiment_list[0], &glb_num_of_exps);
    
    MixingParams params(Ordering::NO);

    glb_params true_values, test_values;
    true_values = glbAllocParams();
    test_values = glbAllocParams();

    glbDefineParams(true_values, params.theta12, params.theta13, params.theta23, params.deltacp, params.sdm, params.ldm);
    glbSetDensityParams(true_values, 1.0, GLB_ALL);

    glbDefineParams(test_values, params.theta12, params.theta13, params.theta23, params.deltacp, params.sdm, params.ldm);
    glbSetDensityParams(test_values, 1.0, GLB_ALL);

    glbSetOscillationParameters(true_values);
    glbSetRates();

    computeChiSquare(test_values);

    glbFreeParams(true_values);
    glbFreeParams(test_values);

    return 0;
}

void computeChiSquare(glb_params g){
    ofstream output;
    output.open("correlation_dcp_t13.dat");

    double i, j, dcp, t13, result;
    double t13_initial = 0.122;
    double t13_final = 0.175;
    double dcp_initial = 0;
    double dcp_final = 2*M_PI;
    double steps = 100;

    double min_chi2 = 1000;
    double best_t13 = 0;
    double best_dcp = 0;

    for(i = 1; i <= steps; i++){
        for(j = 1; j <= steps; j++){
            t13 = t13_initial + i*(t13_final - t13_initial)/100;
            dcp = dcp_initial +j*(dcp_final - dcp_initial)/100;

            glbSetOscParams(g, t13, GLB_THETA_13);
            glbSetOscParams(g, dcp, GLB_DELTA_CP);

            result = glbChiSys(g, GLB_ALL, GLB_ALL);
            if (result < min_chi2) {
                min_chi2 = result;
                best_t13 = t13;
                best_dcp = dcp;
            }
            output << t13 << "\t" << dcp << "\t" << result << endl;
        }
    }

    cout << "Min chi^2: " << min_chi2 << endl;
    cout << "Best theta_13: " << best_t13 << endl;
    cout << "Best delta_cp: " << best_dcp << endl;

    output.close();
}
