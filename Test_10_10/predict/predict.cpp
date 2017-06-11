#include <bits/stdc++.h> 

#define fi(a,b,c) for(int a=b; a<=c; a++) 
#define fd(a,b,c) for(int a=b; a>=c; a--) 
#define fii(a,b,c) for(int a=b; a<c; a++) 
#define pb push_back

using namespace std; 

const int N = 5001;

const double e = 2.7182818284590452353;

void DEBUG() { 
	cout <<"debug" <<endl; 
}

struct Kernel { 
	int n;  
	int beta[9][9]; 
	int gamma[9][9]; 
	Kernel(int x) { 
		if (x == 1) { 
			n = 1; 
			beta[0][0] = gamma[0][0] = 1; 
		} else 
		if (x == 3) {
			n = 3;  
			beta[0][0] = -1; beta[0][1] = 0; beta[0][2] = 1;  
			beta[1][0] = -3; beta[1][1] = 0; beta[1][2] = 3;
			beta[2][0] = -1; beta[2][1] = 0; beta[2][2] = 1;
			gamma[0][0] = -1; gamma[0][1] = -3; gamma[0][2] = -1;  
			gamma[1][0] = 0; gamma[1][1] = 0; gamma[1][2] = 0;
			gamma[2][0] = 1; gamma[2][1] = 3; gamma[2][2] = 1;
		} else 
		if (x == 5) {
			n = 5;  
			beta[0][0] = -2; beta[0][1] = -1; beta[0][2] = 0; beta[0][3] = 1; beta[0][4] = 2; 
			beta[1][0] = -2; beta[1][1] = -4; beta[1][2] = 0; beta[1][3] = 4; beta[1][4] = 2; 
			beta[2][0] = -2; beta[2][1] = -4; beta[2][2] = 0; beta[2][3] = 4; beta[2][4] = 2; 
			beta[3][0] = -2; beta[3][1] = -4; beta[3][2] = 0; beta[3][3] = 4; beta[3][4] = 2; 
			beta[4][0] = -2; beta[4][1] = -1; beta[4][2] = 0; beta[4][3] = 1; beta[4][4] = 2; 

			gamma[0][0] = -2; gamma[0][1] = -2; gamma[0][2] = -2; gamma[0][3] = -2; gamma[0][4] = -2; 
			gamma[1][0] = -1; gamma[1][1] = -4; gamma[1][2] = -4; gamma[1][3] = -4; gamma[1][4] = -1; 
			gamma[2][0] = 0; gamma[2][1] = 0; gamma[2][2] = 0; gamma[2][3] = 0; gamma[2][4] = 0; 
			gamma[3][0] = 1; gamma[3][1] = 4; gamma[3][2] = 4; gamma[3][3] = 4; gamma[3][4] = 1; 
			gamma[4][0] = 2; gamma[4][1] = 2; gamma[4][2] = 2; gamma[4][3] = 2; gamma[4][4] = 2; 
		}
	}
};

struct Image { 
	int rows, cols; 
	char a[N][N]; 
	int Gx[N][N]; 
	int Gy[N][N]; 
	int G[N][N];  
	double angle[N][N];  
}; 

bool check(const Image&M, int i, int j) { 
	return (i >= 0 && j >= 0 && i < M.rows && j < M.cols);
}

void Gradient(Image&M, int len) {
	Kernel K(len);  
	for (int i = 3 ; i < M.rows -3; i++) 
		for (int j = 3 ; j < M.cols -3; j++)  { 
			M.Gx[i][j] = 0 ;  
			M.Gy[i][j] = 0 ; 
			for (int ii = 0; ii < len; ii++) 
				for (int jj = 0; jj < len; jj++) { 
					int iii = i + ii - len/2; 
					int jjj = j + jj - len/2;  
					if (check(M, iii, jjj)) {
						M.Gx[i][j] += K.beta[ii][jj] * M.a[iii][jjj]; 
						M.Gy[i][j] += K.gamma[ii][jj] * M.a[iii][jjj]; 
					}
				}
			M.G[i][j] = abs(M.Gx[i][j]) + abs(M.Gy[i][j]);  
			M.angle[i][j] = atan ((double) M.Gy[i][j] / ((double) M.Gx[i][j] + 0.0000001) );
		}
}

Image M1, M2; 

int cnt[100];
double res[100]; 
double a[N], b[N]; 
int inBlock(double angle, int k) { 
	int block = (int)((angle+1.57) / (3.14/k)); 
	return block ; 
}
vector <double> ans;
vector <double> getResult(const Image&M, int block) { 
	int GradientPixel = 0 ;  
	vector <int> cnt(block + 1, 0); 
	for (int i = 0; i < M.rows; i++) 
			for (int j = 0;  j < M.cols; j++) 
				if (M.G[i][j]) {
					cnt[inBlock(M.angle[i][j], block)] ++; 
					GradientPixel ++;  
				}
	double value;  
	vector <double> res; 
	res.clear(); 
	for (int i = 0 ; i <= block ; i++) {
		value = ((double)cnt[i] / GradientPixel);
		res.push_back(value);  
	}
	return res; 
}

string toString(int x) { 
	string s = ""; 
	while (x> 0) { 
		s = (char)((x % 10) + '0') + s; 
		x/= 10;  
	}
	return s; 
}

char p[20];

double sigmoid(double x){ 
	return 1.0 / (1.0 + pow(e, -x)); 
}

double weight[10]; 

double shift(int block) {  
	double cost = 100000000.0; 
	fi(j, 0, block) 
		b[j] = ans[j];
	fi(sh, 0, block) { 
		double value = 0.0;  
		fi(j, 0, block) 
			value += sigmoid(abs(a[j] - b[j])) - 0.5;   
		if (value < cost) { 
			cost = value;  
			fi(j, 0, block) 
				ans[j] = b[j] ;
		}
		double temp = b[0];  
		b[0] = b[block];  
		fi(j, 1, block) { 
			double x = b[j]; 
			b[j] = temp;  
			temp = x; 
		}
	}
	fi(i, 0, block) 
	return cost ; 
}

vector <vector <double> > v[10][1000]; 
double confidence[10000];

double Error(vector <double> a, vector <double> b) { 
	double value = 0.0; 
	fii(j, 0, a.size()) { 
		value += sigmoid(abs(a[j] - b[j])) - 0.5; 
	}
	return value;
}

void computeConfidence(int label, int block) { 
	fii(i, 0, v[label][block].size()) { 
		confidence[i] = 0.0; 
		fii(j, 0, v[label][block].size()) 
			confidence[i] += Error(v[label][block][i] , v[label][block][j]); 
	}
	double sum = 0.0;  
	double vmax = 0.0; 
	double vmin = 100000000.0; 
	fii(i, 0, v[label][block].size()) {
		sum += confidence[i]; 
		vmax = max(vmax, confidence[i]); 
		vmin = min(vmin, confidence[i]); 
	}
	fii(i, 0, v[label][block].size()) {
		confidence[i] = (confidence[i] - vmin) / (vmax - vmin);  
		confidence[i] = 1.0 - confidence[i]; 	
	}
}


int predict(int block) { 
	freopen("training.txt", "r", stdin); 
	int number; 
	scanf("%d", &number); 
	double cost = 10000000000000000.0; 
	int predict_label, label, n_block; 
	weight[1] = weight[2] = weight[3] = weight[4] = 0; 
	fi(sample, 1, number){ 
		scanf("%d %d", &label, &n_block);  
		fi(i, 0, n_block) scanf("%lf", &a[i]); 
		if (n_block != block) continue; 
		if (sample % 25 == 1) {
			shift(block); 
			computeConfidence(label, block);  
		}
		double value = 0.0; 
		vector <double> set; 
		set.clear(); 
		fi(j, 0, n_block) { 
			set.pb((sigmoid(abs(ans[j] - a[j])) - 0.5) * abs(ans[j]) * confidence[(sample - 1) % 25]); 
		}   
		sort(set.begin(), set.end());
		fii(i, 0, 20) 
			value += set[i]; 
		weight[label] += value; 
	} 

	predict_label ;
	cost = 100000000000000.0;  
	fi(i, 1, 4){
		if (weight[i] < cost) { 
			cost = weight[i]; 
			predict_label = i; 
		}
		//printf("%0.5lf ", weight[i]);  
	}
	//printf("%d \n", predict_label); 
	return predict_label; 
}

int Count[10]; 

int main() { 

	freopen("training.txt", "r", stdin);  
	int number; 
	scanf("%d", &number); 
	fi(sample, 1, number) { 
		int label, block; 
		scanf("%d %d", &label, &block); 
		int k = v[label][block].size(); 
		v[label][block].resize(k + 1);
		fi(i, 0, block) { 
			double x;  scanf("%lf", &x); 
			v[label][block][k].pb(x); 
		} 
	}
	freopen("predict.txt", "w", stdout); 
	int right = 0 ; 
	fi(tcase, 1, 40) { 
		//if ((tcase-1)/5 + 1 == 1 || (tcase-1)/5 + 1 == 2) continue;  
		string s = toString(tcase) + ".txt"; 
		for (int j = 0; j < s.length() ; j++) 
			p[j] = s[j]; 

		p[s.length()] = '\0';
		freopen(p, "r", stdin); 

		int expect; 
		scanf("%d", &expect); 
		printf("Expect: %d ", expect);  
		int n, m;  
		scanf("%d %d", &n, &m); 

		M1.rows = n; 
		M1.cols = m;   
		for (int i = 0; i < M1.rows ; i++) 
			scanf("%s", (M1.a[i]) ); 
		Gradient(M1, 5);
		Count[1] = Count[2] = Count[3] = Count[4] = 0; 
		for (int block  = 5 ; block <= 60 ; block += 5) {
			ans = getResult(M1, block); 
			int predict_label = predict(block); 
			Count[predict_label] ++; 
		}  
		int predict_label ;  
		int vmax = 0; 
		fi(i, 1, 4)  
			 { 
				if (Count[i] > vmax) { 
					vmax = Count[i];  
					predict_label = i; 
				}
			}	
		if (predict_label == expect ) right ++; 	 
		printf("Predict %d\n", predict_label); 
	}
	printf("%d", right); 
	
}