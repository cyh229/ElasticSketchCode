import pandas as pd
import matplotlib.pyplot as plt

# 读取CSV文件
df = pd.read_csv('exp.csv')

# 确认列名
print(df.columns)

# 选择正确的列名，替换 'idx' 为实际的列名
# 假设实际的列名为 'your_actual_idx_column_name'
df_filtered = df[(df['memory(KB)'] == 600) & (df['idx'].between(0, 9))]

# 以 sketch 列进行分组
grouped_data = df_filtered.groupby('sketch')

# 准备数据
sketches = list(grouped_data.groups.keys())
means = [group['ARE'].mean() for name, group in grouped_data]
std_devs = [group['ARE'].std() for name, group in grouped_data]

# 绘制条形图
plt.bar(sketches, means, yerr=std_devs, capsize=5, color=['blue', 'green', 'red', 'purple', 'orange'])

# 设置图表标题和坐标轴标签
plt.title('Bar Chart with Error Bars for Memory Usage = 600(KB)')
plt.xlabel('Sketch')
plt.ylabel('ARE')

# 显示图表
plt.show()

plt.savefig('fig2.png')