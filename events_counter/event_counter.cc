#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <globes/globes.h>
#include "../common/mixingParams.hpp"

using namespace std;

void countEventForNuEAppearance();
void countEventForNuMuDisappearance();

char AEDL_EXP[] = "DUNE_GLoBES.glb";
FILE * outNuEAppearance = NULL;
FILE * outNuMuDisappearance = NULL;

int main(int args, char *argv[]){
    glbInit(argv[0]);
    glbInitExperiment(AEDL_EXP, &glb_experiment_list[0], &glb_num_of_exps);

    MixingParams mixing_params = MixingParams(Ordering::NO);
    glb_params true_values = glbAllocParams();

    glbDefineParams(true_values, mixing_params.theta12, mixing_params.theta13, mixing_params.theta23, mixing_params.deltacp, mixing_params.sdm, mixing_params.ldm);
    glbSetDensityParams(true_values, 1.0, GLB_ALL);
    glbSetOscillationParameters(true_values);
    glbSetRates();

    countEventForNuEAppearance();
    countEventForNuMuDisappearance();

    return 0;
}

void countEventForNuEAppearance(){
    outNuEAppearance = fopen("num_events_nue_appearance.dat", "w");

    int rule = glbNameToValue(0, "rule", "#nue_app");
    glbShowRuleRates(outNuEAppearance, 0, rule, GLB_ALL, GLB_W_EFF, GLB_W_BG, GLB_W_COEFF, GLB_SIG);
    fclose(outNuEAppearance);
}

void countEventForNuMuDisappearance(){
    outNuMuDisappearance = fopen("num_events_numu_disappearance.dat", "w");

    int rule = glbNameToValue(0, "rule", "#numu_dis");
    glbShowRuleRates(outNuMuDisappearance, 0, rule, GLB_ALL, GLB_W_EFF, GLB_W_BG, GLB_W_COEFF, GLB_SIG);
    fclose(outNuMuDisappearance);
}