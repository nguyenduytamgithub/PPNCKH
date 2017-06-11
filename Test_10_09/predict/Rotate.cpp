#include <bits/stdc++.h> 

#define fi(a,b,c) for(int a=b; a<=c; a++) 
#define fd(a,b,c) for(int a=b; a>=c; a--) 
#define fii(a,b,c) for(int a=b; a<c; a++) 
#define mp make_pair 
#define ft first 
#define sc second 
#define pb push_back 

using namespace std ; 


const int N = 1000 ; 
typedef long long  ll ; 

double a[50][N];  
double b[N]; 
int times; 
int label, block; 
const double e = 2.7182818284590452353;

double sigmoid(double x){ 
	return 1.0 / (1.0 + pow(e, -x)); 
}

void shift(int i, int block) { 
	double cost = 100000000.0; 
	fi(j, 0, block) 
		b[j] = a[i][j];
	fi(sh, 0, block) { 
		double value = 0.0;  
		fi(j, 0, block) 
			value += sigmoid(abs(a[1][j] - b[j])) - 0.5;   
		if (value < cost) { 
			cost = value;  
			fi(j, 0, block) 
				a[i][j] = b[j] ; 
		}
		double temp = b[0];  
		b[0] = b[block];  
		fi(j, 1, block) { 
			double x = b[j]; 
			b[j] = temp;  
			temp = x; 
		}
	}
}

int main() 
{
	freopen("text.txt", "r", stdin); 
	freopen("output.txt", "w", stdout); 
	times = 5; 
	while (times --){ 
		fi(i, 1, 25) { 
			scanf("%d %d", &label, &block); 
			fi(j, 0, block) scanf("%lf", &a[i][j]); 
			if (i == 1) continue;  
			shift(i, block);
		}
		fi(i, 1, 25) {
			printf("%d %d ", label, block); 
			fi(j, 0, block) printf("%0.5lf ", a[i][j]); 
			printf("\n");
		}
	}
	
}