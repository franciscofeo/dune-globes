import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import os

# Obter o diretório do script e construir caminhos absolutos
script_dir = os.path.dirname(os.path.abspath(__file__))
root_dir = os.path.dirname(script_dir)  # Diretório raiz (um nível acima)

no_data = np.loadtxt(os.path.join(root_dir, 'NO_correlation_dcp_t23.dat'))
io_data = np.loadtxt(os.path.join(root_dir, 'IO_correlation_dcp_t23.dat'))

theta23 = no_data[:, 0]
deltacp = no_data[:, 1]
chi2 = no_data[:, 2]

theta23_io = io_data[:, 0]
deltacp_io = io_data[:, 1]
chi2_io = io_data[:, 2] 

theta23_unique_no = np.unique(theta23)
deltacp_unique_no = np.unique(deltacp)
chi2_grid_no = chi2.reshape(len(theta23_unique_no), len(deltacp_unique_no))

theta23_unique_io = np.unique(theta23_io)
deltacp_unique_io = np.unique(deltacp_io)
chi2_grid_io = chi2_io.reshape(len(theta23_unique_io), len(deltacp_unique_io))


fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7))

levels_no = np.linspace(chi2.min(), chi2.min() + 50, 15)
contourf_no = ax1.contourf(deltacp_unique_no, theta23_unique_no, chi2_grid_no, 
                           levels=levels_no, cmap='viridis', extend='max')

contour_no = ax1.contour(deltacp_unique_no, theta23_unique_no, chi2_grid_no, 
                         levels=levels_no, colors='black', linewidths=0.5, alpha=0.3)

chi2_min_no = chi2.min()
confidence_levels_no = [chi2_min_no + 2.30, chi2_min_no + 6.18, chi2_min_no + 11.83]
confidence_contours_no = ax1.contour(deltacp_unique_no, theta23_unique_no, chi2_grid_no,
                                     levels=confidence_levels_no, 
                                     colors=['red', 'orange', 'yellow'],
                                     linewidths=2)

ax1.clabel(confidence_contours_no, inline=True, fontsize=10, 
           fmt={confidence_levels_no[0]: r'1$\sigma$', 
                confidence_levels_no[1]: r'2$\sigma$', 
                confidence_levels_no[2]: r'3$\sigma$'})

ax1.set_xlabel(r'$\delta_{cp}$ [rad]', fontsize=12)
ax1.set_ylabel(r'$\theta_{23}$ [rad]', fontsize=12)
ax1.set_title(r'Normal Ordering (NO) - $\chi^2$', fontsize=14, fontweight='bold')
ax1.grid(True, alpha=0.3, linestyle='--', linewidth=0.5)

levels_io = np.linspace(chi2_io.min(), chi2_io.min() + 50, 15)
contourf_io = ax2.contourf(deltacp_unique_io, theta23_unique_io, chi2_grid_io, 
                           levels=levels_io, cmap='viridis', extend='max')

contour_io = ax2.contour(deltacp_unique_io, theta23_unique_io, chi2_grid_io, 
                         levels=levels_io, colors='black', linewidths=0.5, alpha=0.3)

chi2_min_io = chi2_io.min()
confidence_levels_io = [chi2_min_io + 2.30, chi2_min_io + 6.18, chi2_min_io + 11.83]
confidence_contours_io = ax2.contour(deltacp_unique_io, theta23_unique_io, chi2_grid_io,
                                     levels=confidence_levels_io, 
                                     colors=['red', 'orange', 'yellow'],
                                     linewidths=2)

ax2.clabel(confidence_contours_io, inline=True, fontsize=10, 
           fmt={confidence_levels_io[0]: r'1$\sigma$', 
                confidence_levels_io[1]: r'2$\sigma$', 
                confidence_levels_io[2]: r'3$\sigma$'})

ax2.set_xlabel(r'$\delta_{cp}$ [rad]', fontsize=12)
ax2.set_ylabel(r'$\theta_{23}$ [rad]', fontsize=12)
ax2.set_title(r'Inverted Ordering (IO) - $\chi^2$', fontsize=14, fontweight='bold')
ax2.grid(True, alpha=0.3, linestyle='--', linewidth=0.5)

fig.suptitle(r'DUNE: Neutrino Oscillation using GLoBES - Correlation between $\delta_{cp}$ and $\theta_{23}$', fontsize=14, fontweight='bold', y=1.00)


plt.tight_layout()

output_filename = os.path.join(script_dir, 'correlation_dcp_t23_contour.png')
plt.savefig(output_filename, dpi=300, bbox_inches='tight')
plt.show()

