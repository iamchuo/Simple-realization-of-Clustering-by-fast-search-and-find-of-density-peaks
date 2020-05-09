import matplotlib.pyplot as plt
import numpy as np

def draw_scatter(n, s):
	"""
	:param n: 点的数量，整数
	:param s:点的大小，整数
	:return: None
	"""
	data = np.loadtxt('result.txt', encoding='utf-8', delimiter=',')
	x1 = data[:, 0]
	y1 = data[:, 1]
	'''
	color = data[:, 2]
	colors = [i*10 for i in color]
	'''
	fig = plt.figure()
	ax1 = fig.add_subplot(1, 1, 1)
	ax1.set_title('Data Points')
	ax1.set_xlabel('x-value')
	ax1.set_ylabel('y-value')
	ax1.scatter(x1, y1, s=s, c='k', marker='o')
	plt.xlim(xmax=5, xmin=0)
	plt.savefig(r'C:\Users\chuo\Documents\各种作业及资源\数据挖掘\initial.png', dpi=300)
	plt.show()

if __name__ == "__main__":
	draw_scatter(n=28, s=50)
