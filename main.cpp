// CMPE250_Proje3_1.cpp : Defines the entry point for the console application.
//
#include "Piggy_Bank.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <chrono>
using namespace std;


void strongconnect(Piggy_Bank*,int&,stack<int>&,vector<Piggy_Bank*>&, vector<Piggy_Bank*>&);
int min(int, int);
void func(Piggy_Bank* A);



int main(int argc, char* argv[]) {
    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

	ios_base::sync_with_stdio(false);

	ifstream infile(argv[1]);

	ofstream myfile;

	vector<Piggy_Bank*> Piggy_Banks;

	//vector<SCC*> SCC_List;

	vector<Piggy_Bank*> SCC_List;

	vector<int> roots;

	stack<int> S;

	// process first line
	int temp;
	infile >> temp;
	const int  nPB = temp;

	for (int i = 0; i < nPB; i++) {
		Piggy_Bank* A = new Piggy_Bank(i);
		Piggy_Banks.push_back(A);

	}

	for (int i = 0; i < nPB; i++) {
		infile >> temp;
		int nK = temp;
		Piggy_Banks[i]->KeyNum = temp;
		for (int j = 0; j < nK; j++) {

			infile >> temp;
			Piggy_Banks[i]->Keys.push_back(Piggy_Banks[temp-1]);
		}


	}


	int index = 0;


	   for (auto& v : Piggy_Banks) {
		   if (v->index<0) {

			   strongconnect(v,index,S,SCC_List,Piggy_Banks);
		   }

	   }




	   for (auto& v : SCC_List) {
		   if (!v->check) {
			   func(v);
		   }

	   }


	   for (auto& v : SCC_List) {
				
		   for (auto& w : v->Keys) {
			   if(v->lowlink==w->lowlink)
			   v->inDegree += w->inDegree;

		   }
	   }





	myfile.open(argv[2]);

	for (auto& v : SCC_List) {
		if (v->inDegree==0) {
			roots.push_back(v->id + 1);
		}

	}

	myfile << roots.size()<<" ";
	for (auto& v : roots) {
	
		myfile << v << " ";
	}


	return 0;
}



void strongconnect(Piggy_Bank* v,int& index,stack<int>& S,vector<Piggy_Bank*>& SCC_List, vector<Piggy_Bank*>& PiggyBanks) {

	v->index = index;
	v->lowlink = index;
	index++;
	S.push((v->id));
	v->onStack = true;
	for (auto& w : v->Keys) {
		if (w->index<0) {
			strongconnect(w,index,S,SCC_List,PiggyBanks);
			v->lowlink = min(v->lowlink, w->lowlink);	
		}
		else if (w->onStack) {
			v->lowlink = min(v->lowlink, w->index);
		}
	}

	if (v->lowlink == v->index) {
		int test = 1;
		Piggy_Bank* temp = v;
		while(test){
			if (PiggyBanks[S.top()] != v)
			temp->Keys.insert(temp->Keys.end(), PiggyBanks[S.top()]->Keys.begin(), PiggyBanks[S.top()]->Keys.end());
			PiggyBanks[S.top()]->onStack = false;
			if (PiggyBanks[S.top()] == v)  test--;
			S.pop();	
		}
		SCC_List.push_back(temp);
	}

}


int min(int a, int b) {
	if (a < b) return a;
	return b;
}

void func(Piggy_Bank* A) {

	A->check = true;

	if (A->KeyNum != 0) {

		for (auto& pKey : A->Keys) {
			if (pKey->lowlink == A->lowlink) continue;
			pKey->inDegree++;
			if (pKey->check) continue;
		

			func(pKey);


		}
	}
}













//auto end = chrono::steady_clock::now();

//auto diff = end - start;

//cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;








//end = chrono::steady_clock::now();
//
//diff = end - start;
//
//cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;












//void strongconnect(Piggy_Bank* v, int& index, stack<Piggy_Bank*>& S, vector<Piggy_Bank*>& SCC_List) {
//
//	v->index = index;
//	v->lowlink = index;
//	index++;
//	S.push(v);
//	v->onStack = true;
//	for (auto& w : v->Keys) {
//		if (w->index<0) {
//			strongconnect(w, index, S, SCC_List);
//			v->lowlink = min(v->lowlink, w->lowlink);
//		}
//		else if (w->onStack) {
//			v->lowlink = min(v->lowlink, w->index);
//		}
//	}
//
//	if (v->lowlink == v->index) {
//		int test = 1;
//		Piggy_Bank* temp = v;
//		while (test) {
//			if (S.top() != v)
//				temp->Keys.insert(temp->Keys.end(), S.top()->Keys.begin(), S.top()->Keys.end());
//			S.top()->onStack = false;
//			if (S.top() == v)  test--;
//			S.pop();
//		}
//		SCC_List.push_back(temp);
//	}
//
//}
