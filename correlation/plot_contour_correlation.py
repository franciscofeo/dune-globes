import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

data = np.loadtxt('correlation_dcp_t13.dat')

theta13 = data[:, 0]
deltacp = data[:, 1]
chi2 = data[:, 2]

theta13_unique = np.unique(theta13)
deltacp_unique = np.unique(deltacp)

chi2_grid = chi2.reshape(len(theta13_unique), len(deltacp_unique))


fig, ax = plt.subplots(figsize=(10, 8))

levels = np.linspace(chi2.min(), chi2.min() + 50, 15)  # Níveis de contorno
contourf = ax.contourf(deltacp_unique, theta13_unique, chi2_grid, 
                       levels=levels, cmap='viridis', extend='max')

contour = ax.contour(deltacp_unique, theta13_unique, chi2_grid, 
                     levels=levels, colors='black', linewidths=0.5, alpha=0.3)

chi2_min = chi2.min()
confidence_levels = [chi2_min + 2.30, chi2_min + 6.18, chi2_min + 11.83]
confidence_contours = ax.contour(deltacp_unique, theta13_unique, chi2_grid,
                                 levels=confidence_levels, 
                                 colors=['red', 'orange', 'yellow'],
                                 linewidths=2)

ax.clabel(confidence_contours, inline=True, fontsize=10, 
          fmt={confidence_levels[0]: r'1$\sigma$', 
               confidence_levels[1]: r'2$\sigma$', 
               confidence_levels[2]: r'3$\sigma$'})

ax.set_xlabel(r'$\delta_{cp}$ [rad]', fontsize=12)
ax.set_ylabel(r'$\theta_{13}$ [rad]', fontsize=12)
ax.set_title(r'Contornos de $\chi^2$ - Correlação entre $\theta_{13}$ e $\delta_{cp}$', fontsize=14, fontweight='bold')

ax.grid(True, alpha=0.3, linestyle='--', linewidth=0.5)

plt.tight_layout()

output_filename = 'correlation_dcp_t13_contour.png'
plt.savefig(output_filename, dpi=300, bbox_inches='tight')
plt.show()

