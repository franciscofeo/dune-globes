import matplotlib.pyplot as plt
import numpy as np

osc_E = np.loadtxt('dune_oscillation_by_E.dat')
osc_L = np.loadtxt('dune_oscillation_by_L.dat')
osc_E_survival = np.loadtxt("dune_oscillation_by_E_survival.dat")
osc_L_survival = np.loadtxt("dune_oscillation_by_L_survival.dat")
osc_E_tau = np.loadtxt("dune_oscillation_by_E_tau.dat")
osc_L_tau = np.loadtxt("dune_oscillation_by_L_tau.dat")
osc_matter_E = np.loadtxt("dune_oscillation_matter_by_E.dat")
osc_matter_E_survival = np.loadtxt("dune_oscillation_matter_by_E_survival.dat")
osc_matter_E_tau = np.loadtxt("dune_oscillation_matter_by_E_tau.dat")

col1, col2 = osc_E[:, 0], osc_E[:, 1]
col3, col4 = osc_L[:, 0], osc_L[:, 1]
col5, col6 = osc_E_survival[:, 0], osc_E_survival[:, 1]
col7, col8 = osc_L_survival[:, 0], osc_L_survival[:, 1]
col9, col10 = osc_E_tau[:, 0], osc_E_tau[:, 1]
col11, col12 = osc_L_tau[:, 0], osc_L_tau[:, 1]
col13, col14 = osc_matter_E[:, 0], osc_matter_E[:, 1]
col15, col16 = osc_matter_E_survival[:, 0], osc_matter_E_survival[:, 1]
col17, col18 = osc_matter_E_tau[:, 0], osc_matter_E_tau[:, 1]

fig = plt.figure(figsize=(15, 8))
gs = fig.add_gridspec(2, 2, height_ratios=[1, 1])

ax1 = fig.add_subplot(gs[0, 0])
ax2 = fig.add_subplot(gs[0, 1])
ax3 = fig.add_subplot(gs[1, :])

ax1.plot(col1, col2, label=r'$\nu_\mu \rightarrow \nu_e$')
ax1.plot(col5, col6, label=r'$\nu_\mu \rightarrow \nu_e$', color='red')
ax1.plot(col9, col10, label=r'$\nu_\mu \rightarrow \nu_\tau$', linestyle='--', color='green')
ax1.set_xlabel('Energy (GeV)')
ax1.set_ylabel(r'Probability $\nu_\mu \rightarrow \nu_\alpha$')
ax1.set_title('Vacuum Oscillation Probability (L = 1300 km)')
ax1.legend(loc='best', fontsize=12)
ax1.grid(True)

ax2.plot(col3, col4, label=r'$\nu_\mu \rightarrow \nu_e$')
ax2.plot(col7, col8, label=r'$\nu_\mu \rightarrow \nu_\mu$', color='red')
ax2.plot(col11, col12, label=r'$\nu_\mu \rightarrow \nu_\tau$', linestyle='--', color='green')
ax2.set_xlabel('Distance (Km)')
ax1.set_ylabel(r'Probability $\nu_\mu \rightarrow \nu_\alpha$')
ax2.set_title('Vacuum Oscillation Probability (E = 2.5 GeV)')
ax2.legend(loc='best', fontsize=12)
ax2.axvline(x=1300, color='black', linestyle=':', linewidth=1.5, alpha=0.7, label='DUNE (1300 km)')
ax2.legend(loc='best', fontsize=11)
ax2.grid(True)

ax3.plot(col13, col14, label=r'$\nu_\mu \rightarrow \nu_e$')
ax3.plot(col15, col16, label=r'$\nu_\mu \rightarrow \nu_\mu$', color='red')
ax3.plot(col17, col18, label=r'$\nu_\mu \rightarrow \nu_\tau$', linestyle='--', color='green')
ax3.set_xlabel('Energy (GeV)')
ax1.set_ylabel(r'Probability $\nu_\mu \rightarrow \nu_\alpha$')
ax3.set_title('Constant Matter Density Oscillation Probability (L given by DUNE experiment file)')
ax3.legend(loc='best', fontsize=12)
ax3.grid(True)

fig.suptitle('DUNE: Neutrino Oscillation using GLoBES', fontsize=14, fontweight='bold', y=1.00)

plt.subplots_adjust(top=0.93)

plt.rcParams['text.usetex'] = True
plt.tight_layout()
plt.show()
