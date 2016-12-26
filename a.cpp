#include <iostream>
#include <string>

using namespace std;
void permute(const string & str);
void permute(const string & str, int low, int high);

int main(){
 string str = "abc";
 permute(str, 0, 1);

	return 0;
}

void permute(const string & str) {
	int low =0;
	int high = 1;
	//permute(str, low=0, high)
}

void permute(const string & str, int low, int high) {
	if(low == 3)
		return;
	else if(low == high){}
		
	else {
		cout << str[low];
		cout << str[high];
		cout << str[str.size() - (low + high)] << endl;
	}
	high++;
	if(high == 3){
		high = 0;
		low++;
	}
	permute(str, low, high);
}