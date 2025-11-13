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

The project includes a `Makefile` with two available targets:

### `make run`

Executes the C++ simulation program and Python analysis script, keeping the generated `.dat` files for further analysis:

```bash
make run
```

This target will:
1. Compile the C++ program (`prob.cc`)
2. Run the simulation using DUNE GLoBES configurations
3. Execute the Python script to process the output data
4. Keep all generated `.dat` files in the working directory

### `make run-clean`

Executes the complete workflow and automatically cleans up the generated `.dat` files:

```bash
make run-clean
```

This target will:
1. Compile the C++ program (`prob.cc`)
2. Run the simulation using DUNE GLoBES configurations
3. Execute the Python script to process the output data
4. Remove all generated `.dat` files after processing

## Output Files

The simulation generates the following data files (if not cleaned):

- `dune_oscillation_by_E.dat` - Oscillation probability vs. energy
- `dune_oscillation_by_E_survival.dat` - Survival probability vs. energy
- `dune_oscillation_by_E_tau.dat` - Tau appearance probability vs. energy
- `dune_oscillation_matter_by_E.dat` - Matter effects vs. energy
- `dune_oscillation_matter_by_E_survival.dat` - Matter survival probability vs. energy
- `dune_oscillation_by_L.dat` - Oscillation probability vs. baseline distance
- `dune_oscillation_by_L_survival.dat` - Survival probability vs. baseline distance
- `dune_oscillation_by_L_tau.dat` - Tau appearance probability vs. baseline distance

## Project Structure

```
.
├── DUNE_GLoBES.glb         # Main GLoBES configuration file
├── prob.cc                  # C++ simulation program
├── prob_make.sh            # Build and run script
├── read_prob_dat.py        # Python data processing script
├── Makefile                # Build automation
├── definitions.inc         # System definitions
├── syst_list.inc           # Systematics list
├── flux/                   # Neutrino flux data
├── eff/                    # Detector efficiencies
├── smr/                    # Smearing matrices (energy resolution)
└── xsec/                   # Cross-section data
```

