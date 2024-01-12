import pandas as pd
import matplotlib.pyplot as plt

# 读取CSV文件
df = pd.read_csv('exp.csv')
print("columns", df.columns)

# 过滤出 idx 值为 0 的数据
df_idx_0 = df[df['idx'] == 0]

# 筛选 memory(KB) 列值在 200-1000 之间，间隔为100的数据
df_filtered = df_idx_0[df_idx_0['memory(KB)'].between(200, 1000, inclusive='both') & (df_idx_0['memory(KB)'] % 100 == 0)]

# 以 sketch 列进行分组
grouped_data = df_filtered.groupby('sketch')

# 绘制折线图
markers = ['o', 's', '^', 'D', 'v']  # 可以根据需要添加更多的标记
for i, (name, group) in enumerate(grouped_data):
    plt.plot(group['memory(KB)'], group['ARE'], marker=markers[i], label=name)


# 设置图表标题和坐标轴标签
plt.title('Flow Size ARE in Different Memory Usage')
plt.xlabel('Memory Usage(KB)')
plt.ylabel('ARE')

# 显示图例
plt.legend()

# 添加虚线网格
plt.grid(True, linestyle='--', alpha=0.7)

# 指定纵坐标范围
y_max = int(max(df['ARE'])) + 1
plt.axis([200, 1001, 0, y_max])

# 为横纵坐标轴添加刻度线
plt.xticks(range(200, 1001, 100))
plt.yticks(range(0, y_max + 1))

# 去掉图片上方和右方的线
ax = plt.gca()
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

# 显示图表
plt.show()

plt.savefig('fig1.png')