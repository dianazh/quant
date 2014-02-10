#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct tuple_cmp_t{
	bool operator() (const vector<string>& i, const vector<string>& j){
		if (i[0] != j[0]){
			return (i[0] < j[0]);
		} else if (i[1] != j[1]){
			return (i[1] < j[1]);
		} else {
			return (i[2] < j[2]);
		}
	}
};

int main(){
	set<string> catlist;
	//vector<vector<string> > result;
	set<vector<string>, tuple_cmp_t> result;
	vector<string> tuple(3);
	int select[4][2] = {0};
	//int diff1[4] = {0,1,2,3};
	int diff2[2][6] = {{0,0,0,1,1,2},{1,2,3,2,3,3}};
	int diff3[3][4] = {{0,0,0,1},{1,1,2,2},{2,3,3,3}};
	char type[4][3] = {{'1','2','3'},{'b','w','t'},{'t','s','r'},{'g','b','r'}};
	string haul;
	getline(cin, haul);
	stringstream haul_s;
	haul_s.str(haul);
	char ch = haul_s.peek();
	//cout<<"1st ch "<<(int)ch<<endl; //test
	//cout<<"haul: "<<haul<<endl; //test
	//if empty file:
	if (ch == -1){
		cout<<endl;
	}
	while (ch != -1){  //new haul, clear catlist
		string temp;
		catlist.clear();  //cleared catlist
		int count = 0;
		do {
			haul_s>>temp;
			count++;
			//cout<<"temp: "<<temp<<endl; //test
			catlist.insert(temp);
			ch = haul_s.peek();
			//cout<<"ch: "<<(int)ch<<endl; //test
		} while (ch != -1);
		if (!((count==12)||(count==15))){
			cerr<<"Wrong number of cats in one haul!"<<endl; 
			haul_s.clear();
			getline(cin, haul);
			haul_s.str(haul);
			ch = haul_s.peek();
			continue;
		}
		//cout<<"catlist: "<<endl; //test
		/*for(auto it=catlist.begin(); it!=catlist.end();it++){
			cout<<(*it)<<endl; //test
		}*/
		{
			for (set<string>::iterator it = catlist.begin(); it!=catlist.end(); it++){
				string cat = *it;
				//cout<<"cat: "<<cat<<endl; //test
				if (cat[0]==type[0][0]){
					//select[0][] = {1,2};
					select[0][0] = 1;select[0][1] = 2;
				} else if (cat[0]==type[0][1]){
					select[0][0] = 0;select[0][1] = 2;
				} else {
					select[0][0] = 0;select[0][1] = 1;
				}
				if (cat[1]==type[1][0]){
					//select[1] = {1,2};
					select[1][0] = 1;select[1][1] = 2;
				} else if (cat[1]==type[1][1]){
					select[1][0] = 0;select[1][1] = 2;
				} else {
					select[1][0] = 0;select[1][1] = 1;
				}
				if (cat[2]==type[2][0]){
					select[2][0] = 1;select[2][1] = 2;
				} else if (cat[2]==type[2][1]){
					select[2][0] = 0;select[2][1] = 2;
				} else {
					select[2][0] = 0;select[2][1] = 1;
				}
				if (cat[3]==type[3][0]){
					select[3][0] = 1;select[3][1] = 2;
				} else if (cat[3]==type[3][1]){
					select[3][0] = 0;select[3][1] = 2;
				} else {
					select[3][0] = 0;select[3][1] = 1;
				}
				/*for (int i=0; i<4; i++){
					for (int j=0; j<2; j++){
						cout<<select[i][j]<<" "; //test
					}	
					cout<<endl; //test
				}*/
				//diff1
				//cout<<"diff1: "<<endl; //test
				for (int i=0;i<4;i++){
					string temp1 = cat;
					temp1[i] = type[i][select[i][0]];
					//cout<<"temp1: "<<temp1<<endl; //test
					if (catlist.find(temp1)!=catlist.end()){
						string temp2 = temp1;
						//cout<<select[i][1]<<" ch: "<<type[i][select[i][1]]<<endl; //test
						temp2[i] = type[i][select[i][1]];
						//cout<<"temp2: "<<temp2<<endl; //test
						if (catlist.find(temp2)!=catlist.end()){
							tuple = {cat,temp1,temp2};
							sort(tuple.begin(),tuple.end());
							result.insert(tuple); //add new tuple to result
						}
					}
				}
				//diff2
				//cout<<"diff2: "<<endl; //test
				for (int i=0; i<6; i++){
					string temp1 = cat;
					//cout<<"pos: "<<diff2[0][i]<<" sel: "<<select[diff2[0][i]][0]<<" ch: "<<type[diff2[0][i]][select[diff2[0][i]][0]]<<" "<<type[0][1]<<endl; //test
					temp1[diff2[0][i]] = type[diff2[0][i]][select[diff2[0][i]][0]];
					for (int j=0; j<2;j++){
						temp1[diff2[1][i]] = type[diff2[1][i]][select[diff2[1][i]][j]];
						//cout<<"temp1: "<<temp1<<endl; //test
						if (catlist.find(temp1)!=catlist.end()){
							string temp2 = temp1;
							temp2[diff2[0][i]] = type[diff2[0][i]][select[diff2[0][i]][1]];
							temp2[diff2[1][i]] = type[diff2[1][i]][select[diff2[1][i]][abs(j-1)]];  //j0-1,j1-0
							//cout<<"temp2: "<<temp2<<endl; //test
							if (catlist.find(temp2)!=catlist.end()){
								tuple = {cat,temp1,temp2};
								sort(tuple.begin(),tuple.end());
								result.insert(tuple); //add new tuple to result
							}
						}
					}
				}
				//diff3
				//cout<<"diff3: "<<endl; //test
				for(int i=0; i<4; i++){
					string temp1 = cat;
					temp1[diff3[0][i]] = type[diff3[0][i]][select[diff3[0][i]][0]];
					for (int j=0; j<2; j++){
						 temp1[diff3[1][i]] = type[diff3[1][i]][select[diff3[1][i]][j]];
						for (int k=0; k<2; k++){
							temp1[diff3[2][i]] = type[diff3[2][i]][select[diff3[2][i]][k]];
							//cout<<"temp1: "<<temp1<<endl; //test
							if (catlist.find(temp1)!=catlist.end()){
								string temp2 = temp1;
								temp2[diff3[0][i]] = type[diff3[0][i]][select[diff3[0][i]][1]];
								temp2[diff3[1][i]] = type[diff3[1][i]][select[diff3[1][i]][abs(j-1)]];  //j0-1,j1-0
								temp2[diff3[2][i]] = type[diff3[2][i]][select[diff3[2][i]][abs(k-1)]];
								//cout<<"temp2: "<<temp2<<endl; //test
								if (catlist.find(temp2)!=catlist.end()){
									tuple = {cat,temp1,temp2};
									sort(tuple.begin(),tuple.end());
									result.insert(tuple); //add new tuple to result
								}
							}
						}
					}
				}
				//diff4
				//cout<<"diff4: "<<endl; //test
				string temp1 = cat;
				temp1[0] = type[0][select[0][0]];
				//cout<<"ch: "<<type[0][select[0][0]]<<endl; //test
				for (int i=0;i<2;i++){
					temp1[1] = type[1][select[1][i]];
					for (int j=0; j<2; j++){
						temp1[2] = type[2][select[2][j]];
						for (int k=0; k<2; k++){
							temp1[3] = type[3][select[3][k]];
							//cout<<"temp1: "<<temp1<<endl; //test
							if (catlist.find(temp1)!=catlist.end()){
								string temp2 = temp1;
								temp2[0] = type[0][select[0][1]];
								temp2[1] = type[1][select[1][abs(i-1)]];
								temp2[2] = type[2][select[2][abs(j-1)]];  //j0-1,j1-0
								temp2[3] = type[3][select[3][abs(k-1)]];
								//cout<<"temp2: "<<temp2<<endl; //test
								if (catlist.find(temp2)!=catlist.end()){
									tuple = {cat,temp1,temp2};
									sort(tuple.begin(),tuple.end());
									result.insert(tuple); //add new tuple to result
								}
							}
						}
					}
				}
			}
			//sort(result.begin(),result.end(),tuple_cmp);
			int i = result.size();
			for (set<vector<string> >::iterator it = result.begin(); it!=result.end(); it++,i--){
				if (i!=1){
					cout<<(*it)[0]<<","<<(*it)[1]<<","<<(*it)[2]<<" "<<flush;
				} else {
					cout<<(*it)[0]<<","<<(*it)[1]<<","<<(*it)[2]<<flush;
				}
			}	
			cout<<endl; 
		}
		result.clear(); //clear result
		haul_s.clear();
		getline(cin, haul);
		//cout<<"haul: "<<haul<<endl; //test
		haul_s.str(haul);
		ch = haul_s.peek();
		//cout<<"1st ch "<<(int)ch<<endl; //test
	}
	return 0;
}


