import os
import pandas as pd
import matplotlib.pyplot as plt

# Dossier contenant les données
data_folder = 'data'

# Options de compilation disponibles
compilation_options = ['vanilla', 'O2', 'O3', 'O3_MarchNative', 'Ofast']

# Lecture des fichiers CSV pour chaque option de compilation
def read_data(option):
    simd_file = os.path.join(data_folder, option, 'SIMD.csv')
    no_simd_file = os.path.join(data_folder, option, 'No_SIMD.csv')
    
    simd_df = pd.read_csv(simd_file)
    no_simd_df = pd.read_csv(no_simd_file)
    
    return simd_df, no_simd_df

# Graphique comparant les Total_Time pour toutes les options de compilation et SIMD vs NO SIMD
def plot_total_time():
    plt.figure(figsize=(12, 8))
    
    for option in compilation_options:
        simd_df, no_simd_df = read_data(option)
        
        # Conversion des temps en millisecondes pour une échelle plus lisible
        plt.plot(simd_df['Size'], simd_df['Total_Time'] * 1000, label=f'{option} SIMD', marker='o')
        plt.plot(no_simd_df['Size'], no_simd_df['Total_Time'] * 1000, label=f'{option} NO SIMD', marker='x')
    
    plt.xlabel('Array Size')
    plt.ylabel('Total Time (ms)')
    plt.title('Comparison of Total Time (All Compilation Modes)')
    plt.legend()
    plt.grid(True)
    plt.savefig('graphs/total_time_comparison.png')
    plt.show()

# Graphique comparant les No_MultAdd_Operation_Time et MultAdd_Operation_Time pour toutes les options de compilation et SIMD vs NO SIMD
def plot_multadd_times():
    plt.figure(figsize=(12, 8))
    
    for option in compilation_options:
        simd_df, no_simd_df = read_data(option)
        
        # Conversion des temps en millisecondes pour une échelle plus lisible
        plt.plot(simd_df['Size'], simd_df['No_MultAdd_Operation_Time'] * 1000, label=f'{option} SIMD No MultAdd', marker='o')
        plt.plot(simd_df['Size'], simd_df['MultAdd_Operation_Time'] * 1000, label=f'{option} SIMD MultAdd', marker='x')
        plt.plot(no_simd_df['Size'], no_simd_df['No_MultAdd_Operation_Time'] * 1000, label=f'{option} NO SIMD No MultAdd', linestyle='--', marker='o')
        plt.plot(no_simd_df['Size'], no_simd_df['MultAdd_Operation_Time'] * 1000, label=f'{option} NO SIMD MultAdd', linestyle='--', marker='x')
    
    plt.xlabel('Array Size')
    plt.ylabel('Operation Time (ms)')
    plt.title('Comparison of MultAdd Operation Time (All Compilation Modes)')
    plt.legend()
    plt.grid(True)
    plt.savefig('graphs/multadd_time_comparison.png')
    plt.show()

# Graphique comparant les Creation_Fill_Time pour toutes les options de compilation et SIMD vs NO SIMD
def plot_creation_fill_time():
    plt.figure(figsize=(12, 8))
    
    for option in compilation_options:
        simd_df, no_simd_df = read_data(option)
        
        # Conversion des temps en millisecondes pour une échelle plus lisible
        plt.plot(simd_df['Size'], simd_df['Creation_Fill_Time'] * 1000, label=f'{option} SIMD', marker='o')
        plt.plot(no_simd_df['Size'], no_simd_df['Creation_Fill_Time'] * 1000, label=f'{option} NO SIMD', marker='x')
    
    plt.xlabel('Array Size')
    plt.ylabel('Creation Fill Time (ms)')
    plt.title('Comparison of Creation Fill Time (All Compilation Modes)')
    plt.legend()
    plt.grid(True)
    plt.savefig('graphs/creation_fill_time_comparison.png')
    plt.show()

if __name__ == "__main__":
    if not os.path.exists('graphs'):
        os.makedirs('graphs')

    plot_total_time()
    plot_multadd_times()
    plot_creation_fill_time()
