#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;
typedef long long ll;
const int N = 110;
const int INF = 0x3f3f3f3f;
const double eps = 0.6;
const char read_path[] = { "./test_data.txt" };
const char write_path[] = { "./result.txt" };
struct Point{
	double x, y;
	int num;
};
struct GAMA{
	double y;
	int x, num;
};
Point p[N];
double dis[N][N];
double dc = 0.7; 
int n;
int rou[N], vis[N];
double delta[N];
GAMA gama[N];
vector<int> center;

double Dis(Point a, Point b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
void readfile(){//读文件 
	FILE *fp;
	fp = fopen(read_path, "rt");
	if (fp == NULL) {
		cout<<"input file open failed!"<<endl;
		exit(1);
	}else {
		int a, b, c;
		n = 0;
		while (~fscanf(fp, "%d %d", &a, &b)) {
			p[n].x = a*1.0/100;
			p[n].y = b*1.0/100;
			n++;
		}
	}
	fclose(fp);
}
void init(){//初始化，计算各点间距离 
	memset(vis, 0, sizeof(vis));
	memset(rou, 0, sizeof(rou));
	memset(delta, 0, sizeof(delta));
	memset(dis, 0, sizeof(dis));
	for(int i = 0; i < n; i++){
		p[i].num = -1;
		for(int j = i+1; j < n; j++){
			dis[i][j] = dis[j][i] = Dis(p[i], p[j]);
		}
	}
} 
void deal(){//计算每点的ρ和δ 
	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			if(dis[i][j] - dc < 0){
				rou[i]++;
			}
		}
		for(int j = i+1; j < n; j++){
			if(dis[i][j] - dc < 0){
				rou[i]++;
			}
		}
	}
	for(int i = 0; i < n; i++){
		delta[i] = INF;
		for(int j = 0; j < i; j++){
			if(rou[j] > rou[i]){
				delta[i] = min(delta[i], dis[i][j]);
			}
		}
		for(int j = i+1; j < n; j++){
			if(rou[j] > rou[i]){
				delta[i] = min(delta[i], dis[i][j]);
			}
		}
	}
}
bool cmp(GAMA a, GAMA b){
	return a.y > b.y;
}
void findcenter(){//根据ρ和δ以及给定标准找出聚类中心 
	memset(gama, 0, sizeof(gama));
	for(int i = 0; i < n; i++){
		gama[i].x = i;
		gama[i].y = rou[i]*delta[i];
	}
	
	sort(gama, gama+n, cmp);
	for(int i = 1; i < n; i++){
		if(gama[i-1].y - gama[i].y > eps || rou[i] == 0){
			p[gama[i].x].num = gama[i].x;
			center.push_back(gama[i].x);
			cout<<gama[i].x<<endl;
		}
	}
}

int assign(int num){
	int tmp = INF, no = 0;
	if(p[num].num != -1) return p[num].num;
	for(int j = 0; j < num; j++){
		if(dis[num][j] < tmp && !vis[j]){
			vis[j] = 1;
			tmp = dis[num][j];
			no = assign(j);
			vis[j] = 0;
		}
	}
	for(int j = num+1; j < n; j++){
		if(dis[num][j] < tmp && !vis[j]){
			vis[j] = 1;
			tmp = dis[num][j];
			no = assign(j);
			vis[j] = 0;
		}
	}
	return p[num].num = p[no].num;
}
void writefile(){
	FILE *fp;
	char ch;
	fp = fopen(write_path, "wt");
	if (fp == NULL) {
		cout<<"output file open failed!"<<endl;
		exit(1);
	}else{
		for (int i = 0; i < n; i++){
			fprintf(fp, "%.2f,%.2f,%d", p[i].x, p[i].y, p[i].num);
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
int main(){
	readfile();
	init();
	deal();
	findcenter();
	for(int i = 0; i < n; i++){
		assign(i);
	}
	writefile();
	return 0;
}

