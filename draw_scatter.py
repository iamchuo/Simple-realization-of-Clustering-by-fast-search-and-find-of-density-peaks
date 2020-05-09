import matplotlib.pyplot as plt
import numpy as np
 
 
# 定义画散点图的函数
def draw_scatter(n, s):
	"""
	:param n: 点的数量，整数
	:param s:点的大小，整数
	:return: None
	"""
	# 加载数据
	data = np.loadtxt('result.txt', encoding='utf-8', delimiter=',')
	# 通过切片获取横坐标x1
	x1 = data[:, 0]
	# 通过切片获取纵坐标R
	y1 = data[:, 1]
	'''color = data[:, 2]
	colors = [i*10 for i in color]'''
	# 创建画图窗口
	fig = plt.figure()
	# 将画图窗口分成1行1列，选择第一块区域作子图
	ax1 = fig.add_subplot(1, 1, 1)
	# 设置标题
	ax1.set_title('Data Points')
	# 设置横坐标名称
	ax1.set_xlabel('x-value')
	# 设置纵坐标名称
	ax1.set_ylabel('y-value')
	# 画散点图
	ax1.scatter(x1, y1, s=s, c='k', marker='o')
	# 调整横坐标的上下界
	plt.xlim(xmax=5, xmin=0)
	# 显示
	plt.savefig(r'C:\Users\chuo\Documents\各种作业及资源\数据挖掘\initial.png', dpi=300)
	plt.show()
	 
# 主模块
if __name__ == "__main__":
	# 运行
	draw_scatter(n=28, s=50)
