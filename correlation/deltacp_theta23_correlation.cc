#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <globes/globes.h>
#include "../common/mixingParams.hpp"

using namespace std;

char AEDL_EXP[] = "DUNE_GLoBES.glb";
void computeChiSquare(glb_params g, string hierarchy);

int main(int args, char* argv[]){
    glbInit(argv[0]);
    glbInitExperiment(AEDL_EXP, &glb_experiment_list[0], &glb_num_of_exps);
    
    MixingParams mixingParams[2] = {
        MixingParams(Ordering::NO),
        MixingParams(Ordering::IO)
    };

    for (int i = 0; i < 2; i++) {
        MixingParams params = mixingParams[i];
        cout << "\nCalculating Correlation between delta_cp and theta_23 from " + params.label + " hierarchy." << endl;

        glb_params true_values, test_values;
        true_values = glbAllocParams();
        test_values = glbAllocParams();
    
        glbDefineParams(true_values, params.theta12, params.theta13, params.theta23, params.deltacp, params.sdm, params.ldm);
        glbSetDensityParams(true_values, 1.0, GLB_ALL);
    
        glbDefineParams(test_values, params.theta12, params.theta13, params.theta23, params.deltacp, params.sdm, params.ldm);
        glbSetDensityParams(test_values, 1.0, GLB_ALL);
    
        glbSetOscillationParameters(true_values);
        glbSetRates();
    
        computeChiSquare(test_values, params.label);
    
        glbFreeParams(true_values);
        glbFreeParams(test_values);
    }

    return 0;
}

void computeChiSquare(glb_params g, string hierarchy){
    ofstream output;
    output.open(hierarchy + "_correlation_dcp_t23.dat");

    double i, j, dcp, t23, result;
    double t23_initial = 0.300;
    double t23_final = 0.500;
    double dcp_initial = -2*M_PI;
    double dcp_final = 2*M_PI;
    double steps = 100;

    double min_chi2 = 1000;
    double best_t23 = 0;
    double best_dcp = 0;

    for(i = 1; i <= steps; i++){
        for(j = 1; j <= steps; j++){
            t23 = t23_initial + i*(t23_final - t23_initial)/100;
            dcp = dcp_initial +j*(dcp_final - dcp_initial)/100;

            glbSetOscParams(g, t23, GLB_THETA_23);
            glbSetOscParams(g, dcp, GLB_DELTA_CP);

            result = glbChiSys(g, GLB_ALL, GLB_ALL);
            if (result < min_chi2) {
                min_chi2 = result;
                best_t23 = t23;
                best_dcp = dcp;
            }
            output << t23 << "\t" << dcp << "\t" << result << endl;
        }
    }

    cout << "Min chi^2: " << min_chi2 << endl;
    cout << "Best theta_23: " << best_t23 << endl;
    cout << "Best delta_cp: " << best_dcp << endl;

    output.close();
}
