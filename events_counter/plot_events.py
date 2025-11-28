import matplotlib.pyplot as plt
import numpy as np

def plot_event_distribution():
    data_nue = np.loadtxt('num_events_nue_appearance.dat', skiprows=1, max_rows=65)
    data_numu = np.loadtxt('num_events_numu_disappearance.dat', skiprows=1, max_rows=65)
    
    energy_nue = data_nue[:, 0]
    signal_nue = data_nue[:, 1]
    background_nue = data_nue[:, 2]
    
    energy_numu = data_numu[:, 0]
    signal_numu = data_numu[:, 1]
    background_numu = data_numu[:, 2]
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))
    
    width_nue = energy_nue[1] - energy_nue[0]
    ax1.bar(energy_nue, background_nue, width=width_nue, label='Background', color='red', alpha=0.7, edgecolor='darkred')
    ax1.bar(energy_nue, signal_nue, width=width_nue, bottom=background_nue, label=r'Signal ($\nu_\mu \rightarrow \nu_e$)', color='blue', alpha=0.7, edgecolor='darkblue')
    
    ax1.set_xlabel('Energy (GeV)', fontsize=12, fontweight='bold')
    ax1.set_ylabel('Number of Events', fontsize=12, fontweight='bold')
    ax1.set_title(r'$\nu_e$ Appearance', fontsize=13, fontweight='bold')
    ax1.legend(loc='best', fontsize=10)
    ax1.grid(True, alpha=0.3, axis='y')
    ax1.set_xlim([0, max(energy_nue)])
    
    total_signal_nue = np.sum(signal_nue)
    total_background_nue = np.sum(background_nue)
    
    stats_text_nue = f'Total Events:\n'
    stats_text_nue += f'Signal: {total_signal_nue:.2f}\n'
    stats_text_nue += f'Background: {total_background_nue:.2f}\n'
    
    ax1.text(0.98, 0.70, stats_text_nue, 
            transform=ax1.transAxes,
            fontsize=9, 
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8),
            verticalalignment='top',
            horizontalalignment='right',
            fontweight='bold')
    
    width_numu = energy_numu[1] - energy_numu[0]
    ax2.bar(energy_numu, background_numu, width=width_numu, label='Background', color='red', alpha=0.7, edgecolor='darkred')
    ax2.bar(energy_numu, signal_numu, width=width_numu, bottom=background_numu, label=r'Signal ($\nu_\mu \rightarrow \nu_\alpha$)', color='green', alpha=0.7, edgecolor='darkgreen')
    
    ax2.set_xlabel('Energy (GeV)', fontsize=12, fontweight='bold')
    ax2.set_ylabel('Number of Events', fontsize=12, fontweight='bold')
    ax2.set_title(r'$\nu_\mu$ Disappearance', fontsize=13, fontweight='bold')
    ax2.legend(loc='best', fontsize=10)
    ax2.grid(True, alpha=0.3, axis='y')
    ax2.set_xlim([0, max(energy_numu)])
    
    total_signal_numu = np.sum(signal_numu)
    total_background_numu = np.sum(background_numu)
    
    stats_text_numu = f'Total Events:\n'
    stats_text_numu += f'Signal: {total_signal_numu:.2f}\n'
    stats_text_numu += f'Background: {total_background_numu:.2f}\n'
    
    ax2.text(0.98, 0.70, stats_text_numu, 
            transform=ax2.transAxes,
            fontsize=9, 
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8),
            verticalalignment='top',
            horizontalalignment='right',
            fontweight='bold')
    
    fig.suptitle('DUNE: Event Distribution using GLoBES (L = 1300 km)', fontsize=16, fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('events_distribution.png', dpi=300, bbox_inches='tight')
    print(f"\n{'='*50}")
    print("Plot saved as: events_distribution.png")
    print(f"{'='*50}")
    print(f"\nStatistics - nu_e Appearance:")
    print(f"  Total Signal Events: {total_signal_nue:.2f}")
    print(f"  Total Background Events: {total_background_nue:.2f}")
    print(f"  Signal Peak at: {energy_nue[np.argmax(signal_nue)]:.3f} GeV")
    print(f"  Background Peak at: {energy_nue[np.argmax(background_nue)]:.3f} GeV")
    print(f"\nStatistics - nu_mu Disappearance:")
    print(f"  Total Signal Events: {total_signal_numu:.2f}")
    print(f"  Total Background Events: {total_background_numu:.2f}")
    print(f"  Signal Peak at: {energy_numu[np.argmax(signal_numu)]:.3f} GeV")
    print(f"  Background Peak at: {energy_numu[np.argmax(background_numu)]:.3f} GeV")
    print(f"{'='*50}\n")
    
    plt.show()


try:
    plot_event_distribution()
except Exception as e:
    print(f"Error creating plots: {e}")
    print("Check if the data files exist and are in the correct format.")
