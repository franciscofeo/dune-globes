#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <globes/globes.h>

using namespace std;

char AEDL_EXP[] = "DUNE_GLoBES.glb";
void calculateProbabilityByE();
void calculateProbabilityByL();

int main(int args, char *argv[]){
    
    glbInit(argv[0]);
    glbInitExperiment(AEDL_EXP, &glb_experiment_list[0], &glb_num_of_exps);

    /*
    // Valor padrão que tinha nos slides
    double theta12 = asin(sqrt(0.8))/2;
    double theta13 = asin(sqrt(0.001))/2;
    double theta23 = M_PI/4;
    double deltacp = M_PI/2;
    double sdm = 7e-5;
    double ldm = 2e-3;
    */

    // https://globalfit.astroparticles.es/2018/02/09/empty/ -> Estou usando os valores de NO
    double theta12 = asin(sqrt(0.318))/2;
    double theta13 = asin(sqrt(0.022))/2;
    double theta23 = asin(sqrt(0.574))/2;
    double deltacp = 1.08/M_PI;
    double sdm = 7.5e-5;
    double ldm = 2e-3;

    glb_params true_values = glbAllocParams();
    glbDefineParams(true_values, theta12, theta13, theta23, deltacp, sdm, ldm);
    glbSetDensityParams(true_values, 1.0, GLB_ALL);
    glbSetOscillationParameters(true_values);
    glbSetRates();

    calculateProbabilityByE();
    calculateProbabilityByL();

    glbFreeParams(true_values);
    return 0;
}

void calculateProbabilityByE(){
    ofstream output_by_E, output_by_E_survival, output_by_E_tau, output_matter_by_E, output_matter_by_E_survival;
    output_by_E.open("dune_oscillation_by_E.dat");
    output_by_E_survival.open("dune_oscillation_by_E_survival.dat");
    output_by_E_tau.open("dune_oscillation_by_E_tau.dat");
    output_matter_by_E.open("dune_oscillation_matter_by_E.dat");
    output_matter_by_E_survival.open("dune_oscillation_matter_by_E_survival.dat");

    double E, prob_by_E, prob_by_E_survival, prob_by_E_tau, prob_by_E_matter, prob_by_E_matter_survival;
    double E_start = 0.5;
    double E_end = 20;
    double step = 0.001;
    double fixed_L = 20000.0; //20k km

    for (E = E_start; E <= E_end + step; E += step) {
        prob_by_E = glbVacuumProbability(1, 2, +1, E, fixed_L);
        output_by_E<<E<<"\t"<<prob_by_E<<endl;

        prob_by_E_tau = glbVacuumProbability(1, 3, +1, E, fixed_L);
        output_by_E_tau<<E<<"\t"<<prob_by_E_tau<<endl;

        prob_by_E_survival = glbVacuumProbability(1, 1, +1, E, fixed_L);
        output_by_E_survival<<E<<"\t"<<prob_by_E_survival<<endl;
    }

    double E_matter;
    double E_matter_end = 5;

    for(E_matter = E_start; E_matter <= E_matter_end + step; E_matter += step ){
        prob_by_E_matter = glbFilteredConstantDensityProbability(0,1,2,+1, E_matter);
        output_matter_by_E<<E_matter<<"\t"<<prob_by_E_matter<<endl;

        prob_by_E_matter_survival = glbFilteredConstantDensityProbability(0,1,1,+1, E_matter);
        output_matter_by_E_survival<<E_matter<<"\t"<<prob_by_E_matter_survival<<endl;
    }

    output_by_E.close();
    output_by_E_survival.close();
    output_by_E_tau.close();
    output_matter_by_E.close();
    output_matter_by_E_survival.close();
}

void calculateProbabilityByL(){
    ofstream output_by_L, output_by_L_survival, output_by_L_tau;
    output_by_L.open("dune_oscillation_by_L.dat");
    output_by_L_survival.open("dune_oscillation_by_L_survival.dat");
    output_by_L_tau.open("dune_oscillation_by_L_tau.dat");

    double L, prob_by_L, prob_by_L_survival, prob_by_L_tau;
    double fixed_E = 0.75;
    double L_start = 0.0;
    double L_end = 20000.0;
    double big_step = 1;

    for (L = L_start; L <= L_end; L += big_step) {
        prob_by_L = glbVacuumProbability(1, 2, +1, fixed_E, L);
        output_by_L<<L<<"\t"<<prob_by_L<<endl;

        prob_by_L_tau = glbVacuumProbability(1, 3, +1, fixed_E, L);
        output_by_L_tau<<L<<"\t"<<prob_by_L_tau<<endl;

        prob_by_L_survival = glbVacuumProbability(1, 1, +1, fixed_E, L);
        output_by_L_survival<<L<<"\t"<<prob_by_L_survival<<endl;
    }

    output_by_L.close();
    output_by_L_survival.close();
    output_by_L_tau.close();
}
