#include <bits/stdc++.h> 

#define fi(a,b,c) for(int a=b; a<=c; a++) 
#define fd(a,b,c) for(int a=b; a>=c; a--) 
#define fii(a,b,c) for(int a=b; a<c; a++) 
#define pb push_back

using namespace std; 

const double e = 2.7182818284590452353;

vector <vector <double> > v[10][1000]; 
double confidence[10000]; 

double sigmoid(double x){ 
	return 1.0 / (1.0 + pow(e, -x)); 
}

double Error(vector <double> a, vector <double> b) { 
	double value = 0.0; 
	fii(j, 0, a.size()) { 
		value += sigmoid(abs(a[j] - b[j])) - 0.5; 
	}
	return value;
}

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
	fi(label, 1, 2) 
		for (int block = 5 ; block <= 25 ; block += 5) { 
			fii(i, 0, v[label][block].size()) { 
				confidence[i] = 0.0; 
				fii(j, 0, v[label][block].size()) 
					confidence[i] += Error(v[label][block][i] , v[label][block][j]); 
			}
			double sum = 0.0;  
			fii(i, 0, v[label][block].size()) 
				sum += confidence[i]; 
			fii(i, 0, v[label][block].size()) 
				confidence[i] /= sum; 
		}
		
}