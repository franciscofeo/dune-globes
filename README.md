# DUNE GLoBES Configurations

This project provides configuration files and simulation tools for the DUNE (Deep Underground Neutrino Experiment) using the GLoBES (General Long Baseline Experiment Simulator) framework. It calculates neutrino oscillation probabilities as functions of energy and baseline distance, incorporating realistic detector properties, beam flux data, cross-sections, efficiencies, and systematic uncertainties for the DUNE liquid argon detector.

## Configuration Files Source

The DUNE GLoBES configuration files used in this project were obtained from the arXiv files repository at: https://arxiv.org/src/1606.09550v1/anc.

## Requirements

To run this project, you need the following dependencies:

- **C++ compiler** (g++)
- **GLoBES library** - General Long Baseline Experiment Simulator ([download here](https://www.mpi-hd.mpg.de/personalhomes/globes/))
- **GSL** (GNU Scientific Library) - Required for numerical computations
- **Python 3** - For data analysis and visualization

## How to Run

The project includes a `Makefile` with four available targets organized by simulation type:

### Oscillation Probability Simulations

#### `make prob-run`

Executes the oscillation probability simulation and Python analysis script, keeping the generated `.dat` files:

```bash
make prob-run
```

This target will:
1. Compile the C++ program (`oscilation_probability/prob.cc`)
2. Run the oscillation probability simulation
3. Execute the Python script to process and visualize the output data
4. Keep all generated `.dat` files in the working directory

#### `make prob-run-clean`

Executes the oscillation probability workflow and automatically cleans up the generated `.dat` files:

```bash
make prob-run-clean
```

This target will:
1. Compile the C++ program (`oscilation_probability/prob.cc`)
2. Run the oscillation probability simulation
3. Execute the Python script to process and visualize the output data
4. Remove all generated `.dat` files after processing

### Parameter Correlation Analysis

#### `make corr-run`

Executes the correlation analysis between θ₁₃ and δ_CP parameters, keeping the generated files:

```bash
make corr-run
```

This target will:
1. Compile the C++ program (`correlation/deltacp_theta13_correlation.cc`)
2. Run the χ² correlation analysis
3. Generate contour plots showing confidence regions
4. Keep all generated `.dat` and `.png` files in the working directory

#### `make corr-run-clean`

Executes the correlation analysis workflow and automatically cleans up the generated `.dat` files:

```bash
make corr-run-clean
```

This target will:
1. Compile the C++ program (`correlation/deltacp_theta13_correlation.cc`)
2. Run the χ² correlation analysis
3. Generate contour plots showing confidence regions
4. Remove all generated `.dat` files after processing (keeps `.png` plots)

## Output Files

### Oscillation Probability Simulations

The oscillation probability simulations generate the following data files (if not cleaned):

- `dune_oscillation_by_E.dat` - Oscillation probability vs. energy
- `dune_oscillation_by_E_survival.dat` - Survival probability vs. energy
- `dune_oscillation_by_E_tau.dat` - Tau appearance probability vs. energy
- `dune_oscillation_matter_by_E.dat` - Matter effects vs. energy
- `dune_oscillation_matter_by_E_survival.dat` - Matter survival probability vs. energy
- `dune_oscillation_by_L.dat` - Oscillation probability vs. baseline distance
- `dune_oscillation_by_L_survival.dat` - Survival probability vs. baseline distance
- `dune_oscillation_by_L_tau.dat` - Tau appearance probability vs. baseline distance

### Correlation Analysis

The correlation analysis generates:

- `correlation_dcp_t13.dat` - χ² map for θ₁₃ and δ_CP correlation

## Project Structure

```
.
├── DUNE_GLoBES.glb                 # Main GLoBES configuration file
├── Makefile                        # Build automation with multiple targets
├── definitions.inc                 # System definitions
├── syst_list.inc                   # Systematics list
│
├── common/                         # Shared code and headers
│   └── mixingParams.hpp            # Neutrino mixing parameters definitions
│
├── oscilation_probability/         # Oscillation probability simulations
│   ├── prob.cc                     # C++ simulation program
│   ├── prob_make.sh                # Build and run script
│   └── read_prob_dat.py            # Python visualization script
│
├── correlation/                    # Parameter correlation analysis
│   ├── deltacp_theta13_correlation.cc  # C++ correlation analysis
│   ├── correlation_make.sh         # Build and run script
│   └── plot_contour_correlation.py # Python contour plotting script
│
├── flux/                           # Neutrino flux data
│   ├── flux_optimized_FHC.txt      # Forward Horn Current flux
│   ├── flux_optimized_RHC.txt      # Reverse Horn Current flux
│   └── Optimized.inc               # Flux configuration
│
├── eff/                            # Detector efficiencies
│   ├── GLB_app_FHC_eff.dat         # Appearance efficiency (FHC)
│   ├── GLB_app_RHC_eff.dat         # Appearance efficiency (RHC)
│   ├── GLB_dis_FHC_eff.dat         # Disappearance efficiency (FHC)
│   ├── GLB_dis_RHC_eff.dat         # Disappearance efficiency (RHC)
│   └── Eff.inc                     # Efficiency configuration
│
├── smr/                            # Smearing matrices (energy resolution)
│   ├── DUNE_*_smear_*.dat          # Smearing matrices for all channels
│   └── Smear_nominal.inc           # Smearing configuration
│
├── xsec/                           # Cross-section data
│   ├── xsec_cc.dat                 # Charged current cross-sections
│   ├── xsec_nc.dat                 # Neutral current cross-sections
│   └── GENIE_2_8_4.inc             # GENIE cross-section configuration

```

