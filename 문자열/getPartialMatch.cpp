vector<int> getPartialMatch(const string& N){
	int m = N.size();
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;
	while(begin+matched < m){
		if(N[begin+matched] == N[matched]){
			matched++;
			pi[begin+matched-1] = matched;
		}
		else{
			if(matched == 0) begin++;
			else{
				begin += matched-pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}
