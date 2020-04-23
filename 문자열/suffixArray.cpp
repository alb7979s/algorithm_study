//Suffix Array
bool cmp(int x, int y){
	if(g[x] == g[y]) return g[x+t] < g[y+t];
	return g[x] < g[y];
}
void getSA(const char* str){
	t = 1;
	n = (int)strlen(str);
	for(int i=0; i<n; i++){
		SA[i] = i;
		g[i] = str[i] - 'a'; 	//g[i] 상대적으로만 다르면됨, 소문자<대문자로 처리하려먼 대문자에 52 더해서 따로 처리 
	}
	while(t<=n){
		g[n] = -1;
		sort(SA, SA+n, cmp);
		tg[SA[0]]=0;
		for(int i=1; i<n; i++){
			if(cmp(SA[i-1], SA[i])) tg[SA[i]] = tg[SA[i-1]]+1;
			else tg[SA[i]] = tg[SA[i-1]];
		}
		for(int i=0; i<n; i++)
			g[i] = tg[i];
		t <<= 1; 		//t*=2와 같음 
	}
}
