#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

//To compile: g++ --std=c++11 -pedantic -Wall p4.cpp
mutex writeMutex;

const int ROWS = 5;
const int COLS = 5;

int matrix[ROWS][COLS];
int colSum[COLS];
int ii, jj;


void count_columns() {
	
    unique_lock<mutex> lock(writeMutex);
 
	for (ii=0;ii<ROWS;ii++) {
      colSum[ii] += matrix[ROWS][COLS];
	  
	  cout << ii << endl;
	}
}

int main(){

   srand(time(NULL));

   for (ii=0;ii<ROWS;ii++) {

      for (jj=0;jj<COLS;jj++) {

	   matrix[ii][jj] = rand() % 10;
      }
   }
   
   
   
  //Begin Threading
  thread colThreads[COLS];
 
  for(int ii=0;ii<COLS;ii++) {
    colThreads[ii] = thread(count_columns);
  }

  // Wait for each thread to return
  for(int ii=0;ii<COLS;ii++) {
    colThreads[ii].join();
  }

   return 0;
}

