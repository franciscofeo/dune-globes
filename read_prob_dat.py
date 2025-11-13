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

col1, col2 = osc_E[:, 0], osc_E[:, 1]
col3, col4 = osc_L[:, 0], osc_L[:, 1]
col5, col6 = osc_E_survival[:, 0], osc_E_survival[:, 1]
col7, col8 = osc_L_survival[:, 0], osc_L_survival[:, 1]
col9, col10 = osc_E_tau[:, 0], osc_E_tau[:, 1]
col11, col12 = osc_L_tau[:, 0], osc_L_tau[:, 1]
col13, col14 = osc_matter_E[:, 0], osc_matter_E[:, 1]
col15, col16 = osc_matter_E_survival[:, 0], osc_matter_E_survival[:, 1]

fig = plt.figure(figsize=(15, 8))
gs = fig.add_gridspec(2, 2, height_ratios=[1, 1])

ax1 = fig.add_subplot(gs[0, 0])
ax2 = fig.add_subplot(gs[0, 1])
ax3 = fig.add_subplot(gs[1, :])

ax1.plot(col1, col2, label=r'$\nu_e \rightarrow \nu_\mu$')
ax1.plot(col5, col6, label=r'$\nu_e \rightarrow \nu_e$', color='red')
ax1.plot(col9, col10, label=r'$\nu_e \rightarrow \nu_\tau$', linestyle=':', color='green')
ax1.set_xlabel('Energy (GeV)')
ax1.set_ylabel('Probability')
ax1.set_title('Vacuum Oscillation Probability (L = 20,000 km)')
ax1.legend(loc='best', fontsize=12)
ax1.grid(True)

ax2.plot(col3, col4, label=r'$\nu_e \rightarrow \nu_\mu$')
ax2.plot(col7, col8, label=r'$\nu_e \rightarrow \nu_e$', color='red')
ax2.plot(col11, col12, label=r'$\nu_e \rightarrow \nu_\tau$', linestyle=':', color='green')
ax2.set_xlabel('Distance (Km)')
ax2.set_ylabel('Probability')
ax2.set_title('Vacuum Oscillation Probability (E = 0.75 GeV)')
ax2.legend(loc='best', fontsize=12)
ax2.grid(True)

ax3.plot(col13, col14, label=r'$\nu_e \rightarrow \nu_\mu$')
ax3.plot(col15, col16, label=r'$\nu_e \rightarrow \nu_e$', color='red')
ax3.set_xlabel('Energy (GeV)')
ax3.set_ylabel('Probability')
ax3.set_title('Constant Matter Density Oscillation Probability (L given by DUNE experiment file)')
ax3.legend(loc='best', fontsize=12)
ax3.grid(True)

plt.rcParams['text.usetex'] = True
plt.tight_layout()
plt.show()
