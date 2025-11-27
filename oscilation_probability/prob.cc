#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <globes/globes.h>
#include "../common/mixingParams.hpp"

using namespace std;

char AEDL_EXP[] = "DUNE_GLoBES.glb";
void calculateProbabilityByE(string hierarchy);
void calculateProbabilityByL(string hierarchy);
void calculateProbabilityByDensity(string hierarchy);

int main(int args, char *argv[]){
    
    glbInit(argv[0]);
    glbInitExperiment(AEDL_EXP, &glb_experiment_list[0], &glb_num_of_exps);

    MixingParams params[2] = {
        MixingParams(Ordering::NO),
        MixingParams(Ordering::IO)
    };

    for (int i = 0; i < 2; i++) {
        MixingParams mixing_params = params[i];
        cout << "\nCalculating Oscillation Probability from " + mixing_params.label + " hierarchy." << endl;

        glb_params true_values = glbAllocParams();
        glbDefineParams(true_values, mixing_params.theta12, mixing_params.theta13, mixing_params.theta23, mixing_params.deltacp, mixing_params.sdm, mixing_params.ldm);
        glbSetDensityParams(true_values, 1.0, GLB_ALL);
        glbSetOscillationParameters(true_values);
        glbSetRates();

        calculateProbabilityByE(mixing_params.label);
        calculateProbabilityByL(mixing_params.label);
        calculateProbabilityByDensity(mixing_params.label);

        glbFreeParams(true_values);
    }

    return 0;
}

void calculateProbabilityByE(string hierarchy){
    ofstream output_by_E, output_by_E_survival, output_by_E_tau, output_matter_by_E, output_matter_by_E_survival, output_matter_by_E_tau;
    output_by_E.open(hierarchy + "_dune_oscillation_by_E.dat");
    output_by_E_survival.open(hierarchy + "_dune_oscillation_by_E_survival.dat");
    output_by_E_tau.open(hierarchy + "_dune_oscillation_by_E_tau.dat");
    output_matter_by_E.open(hierarchy + "_dune_oscillation_matter_by_E.dat");
    output_matter_by_E_survival.open(hierarchy + "_dune_oscillation_matter_by_E_survival.dat");
    output_matter_by_E_tau.open(hierarchy + "_dune_oscillation_matter_by_E_tau.dat");

    double E, prob_by_E, prob_by_E_survival, prob_by_E_tau, prob_by_E_matter, prob_by_E_matter_survival, prob_by_E_matter_tau;
    double E_start = 0.5;
    double E_end = 2.5;
    double step = 0.001;
    double fixed_L = 1300.0;

    double max_electron_prob_l_fixed = 0;
    double max_muon_prob_l_fixed = 0;
    double max_tau_prob_l_fixed = 0;

    for (E = E_start; E <= E_end + step; E += step) {
        prob_by_E = glbVacuumProbability(2, 1, +1, E, fixed_L);
        if (prob_by_E > max_electron_prob_l_fixed) {
            max_electron_prob_l_fixed = prob_by_E;
        }
        output_by_E<<E<<"\t"<<prob_by_E<<endl;

        prob_by_E_tau = glbVacuumProbability(2, 3, +1, E, fixed_L);
        if (prob_by_E_tau > max_tau_prob_l_fixed) {
            max_tau_prob_l_fixed = prob_by_E_tau;
        }
        output_by_E_tau<<E<<"\t"<<prob_by_E_tau<<endl;

        prob_by_E_survival = glbVacuumProbability(2, 2, +1, E, fixed_L);
        if (prob_by_E_survival > max_muon_prob_l_fixed) {
            max_muon_prob_l_fixed = prob_by_E_survival;
        }
        output_by_E_survival<<E<<"\t"<<prob_by_E_survival<<endl;
    }

    double E_matter;
    double E_matter_end = 5;

    double max_electron_prob_l_fixed_matter = 0;
    double max_muon_prob_l_fixed_matter = 0;
    double max_tau_prob_l_fixed_matter = 0;

    for(E_matter = E_start; E_matter <= E_matter_end + step; E_matter += step ){
        prob_by_E_matter = glbFilteredConstantDensityProbability(0,2,1,+1, E_matter);
        if (prob_by_E_matter > max_electron_prob_l_fixed_matter) {
            max_electron_prob_l_fixed_matter = prob_by_E_matter;
        }
        output_matter_by_E<<E_matter<<"\t"<<prob_by_E_matter<<endl;

        prob_by_E_matter_survival = glbFilteredConstantDensityProbability(0,2,2,+1, E_matter);
        if (prob_by_E_matter_survival > max_muon_prob_l_fixed_matter) {
            max_muon_prob_l_fixed_matter = prob_by_E_matter_survival;
        }
        output_matter_by_E_survival<<E_matter<<"\t"<<prob_by_E_matter_survival<<endl;

        prob_by_E_matter_tau = glbFilteredConstantDensityProbability(0,2,3,+1, E_matter);
        if (prob_by_E_matter_tau > max_tau_prob_l_fixed_matter) {
            max_tau_prob_l_fixed_matter = prob_by_E_matter_tau;
        }
        output_matter_by_E_tau<<E_matter<<"\t"<<prob_by_E_matter_tau<<endl;
    }

    output_by_E.close();
    output_by_E_survival.close();
    output_by_E_tau.close();
    output_matter_by_E.close();
    output_matter_by_E_survival.close();
    output_matter_by_E_tau.close();

    cout << "================================================" << endl;
    cout << "Vacuum Oscillation Probabilities:" << endl;
    cout << "Max electron appearance probability (L fixed): " << max_electron_prob_l_fixed << endl;
    cout << "Max muon survival probability (L fixed): " << max_muon_prob_l_fixed << endl;
    cout << "Max tau appearance probability (L fixed): " << max_tau_prob_l_fixed << endl;

    cout << "================================================" << endl;
    cout << "Matter Oscillation Probabilities:" << endl;
    cout << "Max electron appearance probability (L fixed): " << max_electron_prob_l_fixed_matter << endl;
    cout << "Max muon survival probability (L fixed): " << max_muon_prob_l_fixed_matter << endl;
    cout << "Max tau appearance probability (L fixed): " << max_tau_prob_l_fixed_matter << endl;
    cout << "================================================" << endl;
}

void calculateProbabilityByL(string hierarchy){
    ofstream output_by_L, output_by_L_survival, output_by_L_tau;
    output_by_L.open(hierarchy + "_dune_oscillation_by_L.dat");
    output_by_L_survival.open(hierarchy + "_dune_oscillation_by_L_survival.dat");
    output_by_L_tau.open(hierarchy + "_dune_oscillation_by_L_tau.dat");

    double L, prob_by_L, prob_by_L_survival, prob_by_L_tau;
    double fixed_E = 2.5;
    double L_start = 0.0;
    double L_end = 2000.0;
    double big_step = 1;

    double max_electron_prob_e_fixed = 0;
    double max_muon_prob_e_fixed = 0;
    double max_tau_prob_e_fixed = 0;

    for (L = L_start; L <= L_end; L += big_step) {
        prob_by_L = glbVacuumProbability(2, 1, +1, fixed_E, L);
        if (prob_by_L > max_electron_prob_e_fixed) {
            max_electron_prob_e_fixed = prob_by_L;
        }
        output_by_L<<L<<"\t"<<prob_by_L<<endl;

        prob_by_L_tau = glbVacuumProbability(2, 3, +1, fixed_E, L);
        if (prob_by_L_tau > max_tau_prob_e_fixed) {
            max_tau_prob_e_fixed = prob_by_L_tau;
        }
        output_by_L_tau<<L<<"\t"<<prob_by_L_tau<<endl;

        prob_by_L_survival = glbVacuumProbability(2, 2, +1, fixed_E, L);
        if (prob_by_L_survival > max_muon_prob_e_fixed) {
            max_muon_prob_e_fixed = prob_by_L_survival;
        }
        output_by_L_survival<<L<<"\t"<<prob_by_L_survival<<endl;
    }

    output_by_L.close();
    output_by_L_survival.close();
    output_by_L_tau.close();

    cout << "Vacuum Oscillation Probabilities:" << endl;
    cout << "Max electron appearance probability (E fixed): " << max_electron_prob_e_fixed << endl;
    cout << "Max muon survival probability (E fixed): " << max_muon_prob_e_fixed << endl;
    cout << "Max tau appearance probability (E fixed): " << max_tau_prob_e_fixed << endl;
    cout << "================================================\n" << endl;
}

void calculateProbabilityByDensity(string hierarchy){
    ofstream output_by_density, output_vacuum_by_density;
    output_by_density.open(hierarchy + "_dune_oscillation_by_density.dat");
    output_vacuum_by_density.open(hierarchy + "_dune_oscillation_vacuum_by_density.dat");

    double density, prob_by_density, prob_vacuum;
    double E = 2.5;
    double L = 1300;
    double density_start = 0.0;
    double density_end = 100.0;
    double step = 0.01;

    for (density = density_start; density <= density_end; density += step) {
        prob_by_density = glbConstantDensityProbability(2, 1, +1, E, L, density);
        output_by_density << density << "\t" << prob_by_density << endl;
        
        prob_vacuum = glbVacuumProbability(2, 1, +1, E, L);
        output_vacuum_by_density << density << "\t" << prob_vacuum << endl;
    }

    output_by_density.close();
    output_vacuum_by_density.close();
}
