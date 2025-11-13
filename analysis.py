import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def setup_seaborn_style():
    """Настройка стиля seaborn для профессиональных графиков"""
    sns.set_theme(style="whitegrid")  # Сетка и чистый стиль
    sns.set_palette("husl")  # Цветовая палитра
    plt.rcParams['figure.figsize'] = (12, 8)

def plot_performance_seaborn():
    # Настраиваем стиль
    setup_seaborn_style()
    
    # Читаем данные из CSV
    csv_path = "data/performance_data.csv"
    
    if not os.path.exists(csv_path):
        print(f"Error: File {csv_path} not found!")
        return
    
    df = pd.read_csv(csv_path)
    
    # Создаем фигуру с двумя subplots
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))
    
    # Фильтруем данные
    add_data = df[df['operation'] == 'add']
    commit_data = df[df['operation'] == 'commit']
    
    # График 1: Add operation с seaborn
    sns.lineplot(data=add_data, x='file_count', y='time_microseconds', 
                 marker='o', markersize=8, linewidth=2.5, ax=ax1, 
                 label='Add Operation', color='#2E86AB')
    sns.scatterplot(data=add_data, x='file_count', y='time_microseconds', 
                   s=100, ax=ax1, color='#2E86AB')
    
    ax1.set_xlabel('Number of Files', fontsize=12, fontweight='bold')
    ax1.set_ylabel('Time (microseconds)', fontsize=12, fontweight='bold')
    ax1.set_title('Add Operation Performance', fontsize=14, fontweight='bold')
    
    # График 2: Commit operation с seaborn
    sns.lineplot(data=commit_data, x='file_count', y='time_microseconds', 
                 marker='s', markersize=8, linewidth=2.5, ax=ax2,
                 label='Commit Operation', color='#A23B72')
    sns.scatterplot(data=commit_data, x='file_count', y='time_microseconds', 
                   s=100, ax=ax2, color='#A23B72')
    
    ax2.set_xlabel('Number of Files', fontsize=12, fontweight='bold')
    ax2.set_ylabel('Time (microseconds)', fontsize=12, fontweight='bold')
    ax2.set_title('Commit Operation Performance', fontsize=14, fontweight='bold')
    
    plt.suptitle('Version Control System Performance Analysis', fontsize=16, fontweight='bold')
    plt.tight_layout()
    plt.savefig('data/performance_seaborn.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_regression_analysis():
    """Регрессионный анализ с seaborn"""
    setup_seaborn_style()
    
    csv_path = "data/performance_data.csv"
    if not os.path.exists(csv_path):
        return
    
    df = pd.read_csv(csv_path)
    
    # Создаем регрессионные графики
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))
    
    add_data = df[df['operation'] == 'add']
    commit_data = df[df['operation'] == 'commit']
    
    # Регрессия для Add
    sns.regplot(data=add_data, x='file_count', y='time_microseconds', 
                ax=ax1, scatter_kws={'s': 80, 'alpha': 0.7}, 
                line_kws={'color': 'red', 'linewidth': 2})
    ax1.set_title('Add Operation: Linear Regression', fontweight='bold')
    ax1.set_xlabel('Number of Files')
    ax1.set_ylabel('Time (microseconds)')
    
    # Регрессия для Commit
    sns.regplot(data=commit_data, x='file_count', y='time_microseconds', 
                ax=ax2, scatter_kws={'s': 80, 'alpha': 0.7}, 
                line_kws={'color': 'red', 'linewidth': 2})
    ax2.set_title('Commit Operation: Linear Regression', fontweight='bold')
    ax2.set_xlabel('Number of Files')
    ax2.set_ylabel('Time (microseconds)')
    
    plt.suptitle('Regression Analysis: Time vs Number of Files', fontsize=16, fontweight='bold')
    plt.tight_layout()
    plt.savefig('data/regression_analysis.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_comparison_seaborn():
    """Сравнительный график с seaborn"""
    setup_seaborn_style()
    
    csv_path = "data/performance_data.csv"
    if not os.path.exists(csv_path):
        return
    
    df = pd.read_csv(csv_path)
    
    plt.figure(figsize=(12, 8))
    
    # Используем seaborn для красивого сравнения
    sns.lineplot(data=df, x='file_count', y='time_microseconds', 
                 hue='operation', style='operation', markers=True, 
                 dashes=False, markersize=10, linewidth=3)
    
    plt.xlabel('Number of Files', fontsize=12, fontweight='bold')
    plt.ylabel('Time (microseconds)', fontsize=12, fontweight='bold')
    plt.title('Performance Comparison: Add vs Commit Operations', 
              fontsize=14, fontweight='bold')
    plt.legend(title='Operation', title_fontsize=12, fontsize=11)
    
    plt.savefig('data/comparison_seaborn.png', dpi=300, bbox_inches='tight')
    plt.show()

def statistical_analysis():
    """Статистический анализ с seaborn"""
    csv_path = "data/performance_data.csv"
    if not os.path.exists(csv_path):
        return
    
    df = pd.read_csv(csv_path)
    
    # Boxplot для сравнения распределений
    plt.figure(figsize=(10, 6))
    sns.boxplot(data=df, x='operation', y='time_microseconds', 
                palette=['#2E86AB', '#A23B72'])
    plt.title('Distribution of Execution Times by Operation', fontweight='bold')
    plt.xlabel('Operation')
    plt.ylabel('Time (microseconds)')
    plt.savefig('data/boxplot_seaborn.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    # Violin plot для более детального view распределения
    plt.figure(figsize=(10, 6))
    sns.violinplot(data=df, x='operation', y='time_microseconds', 
                   palette=['#2E86AB', '#A23B72'])
    plt.title('Violin Plot: Execution Times Distribution', fontweight='bold')
    plt.xlabel('Operation')
    plt.ylabel('Time (microseconds)')
    plt.savefig('data/violinplot_seaborn.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    os.makedirs("data", exist_ok=True)
    
    # Создаем различные типы графиков с seaborn
    plot_performance_seaborn()
    plot_regression_analysis()
    plot_comparison_seaborn()
    statistical_analysis()
    
    print("Seaborn graphs created:")
    print("- performance_seaborn.png: Основные графики")
    print("- regression_analysis.png: Регрессионный анализ")
    print("- comparison_seaborn.png: Сравнительный график")
    print("- boxplot_seaborn.png: Boxplot распределений")
    print("- violinplot_seaborn.png: Violin plot распределений")