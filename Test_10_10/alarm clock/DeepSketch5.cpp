#include <bits/stdc++.h> 

#define fi(a,b,c) for(int a=b; a<=c; a++) 
#define fd(a,b,c) for(int a=b; a>=c; a--) 
#define fii(a,b,c) for(int a=b; a<c; a++) 

using namespace std; 

const int N = 5001;


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

const int k = 5; 
const int current_Block = 2; 

int cnt[10];
double res[10]; 

int inBlock(double angle, int k) { 
	int block = (int)((angle+1.57) / (3.14/k)); 
	return block ; 
}

void getResult(const Image&M, int block) { 
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
	printf("%d %d ", 2, block); 
	for (int i = 0 ; i <= block ; i++) {
		value = ((double)cnt[i] / GradientPixel);
		res.push_back(value);  
	}
	for (int i = 0 ; i < res.size(); i++) 
		printf("%0.5lf ", res[i]); 
	printf("\n"); 
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

int main() { 
	freopen("text.txt", "w", stdout); 
	for (int block = 5; block <= 60 ; block += 5) { 
		for (int i = 1; i <= 50; i++) { 
			string s = toString(i) + ".txt"; 
			s = "t" + s; 
			for (int j = 0; j < s.length() ; j++) 
				p[j] = s[j]; 

			p[s.length()] = '\0';
			freopen(p, "r", stdin); 
			int n, m;  
			scanf("%d %d", &n, &m); 

			M1.rows = n; 
			M1.cols = m;  
			for (int i = 0; i < M1.rows ; i++) 
				scanf("%s", (M1.a[i]) ); 
			Gradient(M1, 5);
			getResult(M1, block);   
		}
	}
	
}
