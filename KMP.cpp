#include <bits/stdc++.h>
using namespace std;

//returns lps array;
//lps[j] stores the maximum proper prefix which is also a suffix in pattern[0...j]
vector<int> computeLps(string pattern){
	/*
		abcdabca
		00001234

		aaaabeaaaabx
		01230012345
		bxbxbxbx
		0012345

		abababab
		0012345
	*/

	vector<int> lps(pattern.size(), 0);
	lps[0] = 0;
	int k;
	for(int j=1; j<pattern.size(); j++){
		//lps[j-1] stores the maximum proper prefix which is also a suffix in pattern[0...j-1]
		//pattern[0....lps[j-1]-1] is that maximum proper prefix
		//k = lps[j-1]
		// (i)
		//if pattern[k] == pattern[j], then lps[j] = k + 1, continue;
		// if (k-1) < 0, lps[j] = 0, continue
		//else k = lps[k-1]
		//repeat from (i)
		//else go to k = lps[j-1] and check pattern[k+1] = pattern[j]
		k = lps[j-1];
		while(1){
			if(pattern[k]==pattern[j]){
				lps[j] = k+1;
				break;
			}
			if(k-1 < 0){
				lps[j] = 0;
				break;
			}
			else{
				k = lps[k-1];
			}
		}


	}
	return lps;
}

// returns array of indices where we find pattern in text
vector<int> KMPSearch(string text, string pattern){
	vector<int> lps = computeLps(pattern);
	vector<int> answer;
	int i=0, j=0;

	while(i <= text.size()){
		if(j==pattern.size()){
			answer.push_back(i-pattern.size());
			j = lps[j-1];
			continue;
		}
		if(i==text.size())	break;
		if(text[i] == pattern[j]){
			i++;
			j++;
		}
		else{
			if(j==0){
				i++;
				continue;
			}

			//it means that text[i-j....i-1] = pattern[0...j-1]
			j = lps[j-1];
		}

	}

	return answer;
}

int main(){
	string text = "AABR";
	string pattern = "AABA";

	//vector<int> matchingIndices = KMPSearch(text, pattern);
	vector<int> matchingIndices = KMPSearch(text, pattern);
	if(matchingIndices.empty()){
		cout << "Didn't find any match." << endl;
	}
	for(int &x: matchingIndices){
		cout << "Found pattern at index: " << x << endl;
	}
	return 0;
}