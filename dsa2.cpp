// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2013
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>


using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);
void merge(int,int,int);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
list<Data *> countA[100000];
list<Data *>::iterator ipC, ipF, ipD;
list<Data *> l2;
Data *A[1000000];
char  B[1000000];
int i,j,decimalP,finalP,bucket,num1,num2;
unsigned int n1,n2;
float tmp;

inline bool compare(const Data* x, const Data* y) {
        num1=20;
        num2=20;
        while ((x->data)[num1] != '.')
                num1--;
        while ((y->data)[num2] != '.')
                num2--;
        if (num1 == num2){
                return (x->data).compare((y->data)) < 0;
        }
        else
                return (num1 < num2);
}


/*
bool compare(const Data* item1, const Data* item2) {   // returns true if 
	num1=20;
	num2=20;
	while ((item1 -> data)[num1] != '.') 
		num1--;	
	while ((item2 -> data)[num2] != '.') 
		num2--;
	if ((num1 == num2) && ((item1 -> data) ){
		return (item1 -> data).compare((item2 -> data)) < 0;
	}
	else 
		return (num1 < num2);
}

inline bool compare2(const Data* x, const Data* y) {
	return (x->data).compare((y->data)) < 0;
}
*/
void insertion_sort(list<Data *> &l){
   string temp;
   for (list<Data *>::iterator ipD = l.begin(); ipD != l.end(); ++ipD){
      ipC = ipD;
      ipF = ipC;
      ipF--;
      while (ipC!=l.begin() && (*ipC)->data < (*ipF)->data) {
         temp = (*ipC)->data;
	 (*ipC)->data = (*ipF)->data;
         (*ipF)->data = temp;
	 ipC--;
	 ipF--;
      }
   }
}

void bucket_sort(list<Data *> &l, int bucketNum, int shift) {
	for (ipC=l.begin(); ipC!=l.end(); ++ipC) {
		decimalP=20;
		while (((*ipC)->data)[decimalP] != '.') 
			decimalP--;
		finalP = decimalP-shift;
		if (finalP<=0) 
			countA[0].push_back(*ipC);
		else {
			bucket = atoi(((*ipC)->data).substr(0,finalP).c_str());
			countA[bucket].push_back(*ipC);
		}
	}
	countA[0].sort(compare);
	l2.splice(l2.end(),countA[0]);
	for (j=1; j<=bucketNum; j++) {
		countA[j].sort(compare2);
		l2.splice(l2.end(),countA[j]);
	}
	l.swap(l2);
}

void counting_sort(list<Data *> &l) {
	for (ipD=l.begin(); ipD!=l.end(); ++ipD) {
		tmp = (1000*atof(((*ipD)->data).c_str()));
		A[(int)tmp]=*ipD;
		B[(int)tmp]++;	
	}
	for (i=0; i<=999999; i++) {
		while(B[i]--) 
			l2.push_back(A[i]);
	}
	l.swap(l2);
}
	
void sortDataList(list<Data *> &l) {
	int size = l.size();
	if(lengthList<110001)
		bucket_sort(l,1000,17);
	else if((*l.begin())->data.length() < 10)
		counting_sort(l);
	else if(((*l.begin())->data).substr(0, 9) == ((*++l.begin())->data).substr(0, 9))
		insertion_sort(l);
	else
		bucket_sort(l,10000,16);
}
