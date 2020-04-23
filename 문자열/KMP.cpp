//KMP
vector<int> kmp(const string& H, const string& N){	//HÁý´õ¹Ì, N¹Ù´Ã
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<pi> = getPartialMatch(N);
	int begin = 0, matched = 0;
	while(begin <= n-m){
		if(matched<m && H[begin+matched]==N[matched]){
			matched++;
			if(matched == m) ret.push_back(begin);
		}
		else{
			if(matched == 0) begin++;
			else{
				begin += matched-pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return ret;
}
