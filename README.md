# DUNE GLoBES Configurations

This project provides configuration files and simulation tools for the DUNE (Deep Underground Neutrino Experiment) using the GLoBES (General Long Baseline Experiment Simulator) framework. It calculates neutrino oscillation probabilities as functions of energy, baseline distance, and matter density, and performs parameter correlation analyses (θ₂₃ vs δ_CP) using χ² statistics for both Normal and Inverted mass ordering scenarios and calculate event distribution for disappearance and appearance channels. The simulations incorporate realistic detector properties, beam flux data, cross-sections, efficiencies, and systematic uncertainties for the DUNE liquid argon detector.

## Configuration Files Source

The DUNE GLoBES configuration files used in this project were obtained from the arXiv files repository at: https://arxiv.org/src/1606.09550v1/anc.

## Requirements

To run this project, you need the following dependencies:

- **C++ compiler** (g++)
- **GLoBES library** - General Long Baseline Experiment Simulator ([download here](https://www.mpi-hd.mpg.de/personalhomes/globes/))
- **GSL** (GNU Scientific Library) - Required for numerical computations
- **Python 3** - For data analysis and visualization

## How to Run

The project includes a `Makefile` with six available targets organized by simulation type:

### Oscillation Probability Simulations

#### `make prob-run`

Executes the oscillation probability simulation and Python analysis script, keeping the generated `.dat` files:

```bash
make prob-run
```

This target will:
1. Compile the C++ program (`oscilation_probability/prob.cc`)
2. Run oscillation probability simulations for both NO and IO scenarios, calculating:
   - Probabilities vs energy (vacuum and matter effects)
   - Probabilities vs baseline distance
   - Probabilities vs matter density
3. Execute the Python script to process and visualize the output data
4. Keep all generated `.dat` files in the working directory

#### `make prob-run-clean`

Executes the oscillation probability workflow and automatically cleans up the generated `.dat` files:

```bash
make prob-run-clean
```

This target will:
1. Compile the C++ program (`oscilation_probability/prob.cc`)
2. Run oscillation probability simulations for both NO and IO scenarios
3. Execute the Python script to process and visualize the output data
4. Remove all generated `.dat` files after processing (keeps visualization plots)

### Parameter Correlation Analysis

#### `make corr-run`

Executes the correlation analysis between θ₂₃ and δ_CP parameters, keeping the generated files:

```bash
make corr-run
```

This target will:
1. Compile the C++ program (`correlation/deltacp_theta23_correlation.cc`)
2. Run the χ² correlation analysis
3. Generate contour plots showing confidence regions
4. Keep all generated `.dat` and `.png` files in the working directory

#### `make corr-run-clean`

Executes the correlation analysis workflow and automatically cleans up the generated `.dat` files:

```bash
make corr-run-clean
```

This target will:
1. Compile the C++ program (`correlation/deltacp_theta23_correlation.cc`)
2. Run the χ² correlation analysis
3. Generate contour plots showing confidence regions
4. Remove all generated `.dat` files after processing (keeps `.png` plots)

### Event Counter

#### `make ec-run`

Executes the event counter simulation for neutrino appearance and disappearance channels, keeping the generated files:

```bash
make ec-run
```

This target will:
1. Compile the C++ program (`events_counter/event_counter.cc`)
2. Calculate the expected number of events for νe appearance and νμ disappearance
3. Generate event distribution plots showing signal and background vs. energy
4. Keep all generated `.dat` and `.png` files in the working directory

#### `make ec-run-clean`

Executes the event counter workflow and automatically cleans up the generated `.dat` files:

```bash
make ec-run-clean
```

This target will:
1. Compile the C++ program (`events_counter/event_counter.cc`)
2. Calculate the expected number of events for νe appearance and νμ disappearance
3. Generate event distribution plots showing signal and background vs. energy
4. Remove all generated `.dat` files after processing (keeps visualization plots)

## Output Files

### Oscillation Probability Simulations

The oscillation probability simulations generate the following data files for both Normal Ordering (NO) and Inverted Ordering (IO) (if not cleaned):

**Energy-dependent oscillations:**
- `{NO,IO}_dune_oscillation_by_E.dat` - Vacuum oscillation probability vs. energy
- `{NO,IO}_dune_oscillation_by_E_survival.dat` - Vacuum survival probability vs. energy
- `{NO,IO}_dune_oscillation_by_E_tau.dat` - Vacuum tau appearance probability vs. energy
- `{NO,IO}_dune_oscillation_matter_by_E.dat` - Matter effects vs. energy
- `{NO,IO}_dune_oscillation_matter_by_E_survival.dat` - Matter survival probability vs. energy
- `{NO,IO}_dune_oscillation_matter_by_E_tau.dat` - Matter tau appearance probability vs. energy

**Baseline-dependent oscillations:**
- `{NO,IO}_dune_oscillation_by_L.dat` - Vacuum oscillation probability vs. baseline distance
- `{NO,IO}_dune_oscillation_by_L_survival.dat` - Vacuum survival probability vs. baseline distance
- `{NO,IO}_dune_oscillation_by_L_tau.dat` - Vacuum tau appearance probability vs. baseline distance

**Density-dependent oscillations:**
- `{NO,IO}_dune_oscillation_by_density.dat` - Oscillation probability vs. matter density
- `{NO,IO}_dune_oscillation_vacuum_by_density.dat` - Vacuum probability reference vs. matter density

### Correlation Analysis

The correlation analysis generates:

- `NO_correlation_dcp_t23.dat` - χ² map for θ₂₃ and δ_CP correlation (Normal Ordering)
- `IO_correlation_dcp_t23.dat` - χ² map for θ₂₃ and δ_CP correlation (Inverted Ordering)
- `correlation/correlation_dcp_t23_contour.png` - Side-by-side contour plots comparing NO and IO scenarios for θ₂₃ vs δ_CP

### Event Counter

The event counter simulation generates (if not cleaned):

- `num_events_nue_appearance.dat` - Energy distribution of signal and background events for νe appearance
- `num_events_numu_disappearance.dat` - Energy distribution of signal and background events for νμ disappearance
- `events_distribution.png` - Side-by-side bar plots showing event distributions for both channels with total event statistics

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
│   ├── prob.cc                     # C++ simulation program (E, L, and density scans)
│   ├── prob_make.sh                # Build and run script
│   └── read_prob_dat.py            # Python visualization script
│
├── correlation/                    # Parameter correlation analysis
│   ├── deltacp_theta23_correlation.cc  # C++ θ₂₃ vs δ_CP correlation analysis
│   ├── correlation_make.sh         # Build and run script
│   └── plot_contour_correlation.py # Python contour plotting script
│
├── events_counter/                 # Event counter simulations
│   ├── event_counter.cc            # C++ event counting program (νe appearance and νμ disappearance)
│   ├── ec_make.sh                  # Build and run script
│   └── plot_events.py              # Python event distribution plotting script
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

