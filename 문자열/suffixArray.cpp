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
		g[i] = str[i] - 'a'; 	//g[i] ��������θ� �ٸ����, �ҹ���<�빮�ڷ� ó���Ϸ��� �빮�ڿ� 52 ���ؼ� ���� ó�� 
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
		t <<= 1; 		//t*=2�� ���� 
	}
}
