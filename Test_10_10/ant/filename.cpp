#include <bits/stdc++.h> 

using namespace std ;  

string tostring(int x) { 
	string s = ""; 
	while (x> 0) { 
		s = (char)((x % 10) + '0') + s; 
		x/= 10;  
	}
	return s; 
}

char p[20]; 
char a[5009][5009];
int main() 
{
	int tcase = 50; 
	int i = 241 ;  
	for (int t = 1; t <= tcase ; t++) { 
		string s = tostring(i) + ".txt"; 
		for (int j = 0; j < s.length() ; j++) 
			p[j] = s[j]; 

		p[s.length()] = '\0';
		freopen(p, "r", stdin); 
		int n, m; 
		scanf("%d %d", &n, &m); 
		for (int x = 0 ; x < n ; x++) 
			scanf("%s", a[x]); 

		s = tostring(t) + ".txt"; 
		s = "t" + s; 
		for (int j = 0; j < s.length() ; j++) 
			p[j] = s[j]; 

		p[s.length()] = '\0';
		freopen(p, "w", stdout);  
		printf("%d %d\n", n, m);  
		for (int x = 0 ; x < n ; x++) 
			printf("%s\n", a[x]); 

		i++; 
	}

}