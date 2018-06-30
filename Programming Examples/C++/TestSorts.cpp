//
// Created by Karan Kumar on 5/26/2018.
//
#include <iostream>
#include <climits>
#include <ctime>
#include <random>
using namespace std;

void insertionSort(int[], int);
void quickSort(int[], int, int);
void exchange(int *, int *);
void mergeSort(int[], int, int);
void merge(int[], int, int, int);
void printArray(int[], int);

int main() {

    uniform_real_distribution<double> unif(100.00,1000.00);
    default_random_engine rand;

    int a[200000];
    int n = sizeof(a)/sizeof(a[0]);
    for (int i = 0; i < n; ++i) {
        double randomDouble = unif(rand);
        a[i] =  randomDouble;
    }

    clock_t t1,t2;
    t1 = clock();

    //insertionSort(a, n);
    //quickSort(a, 0, n - 1);
    mergeSort(a, 0, n - 1);

    t2 = clock();
    //printArray(a, n);

    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout<< "Total time it took to run (in seconds): " << seconds <<endl;
    return 0;
}

void insertionSort(int a[], int n) {

    int i, j, key;
    for(j = 2; j <= n-1; j++){
        key = a[j];
        i = j-1;

        while(((i >= 0)) && a[i] > key){
            a[i+1] = a[i];
            i = i-1;
        }
        a[i+1] = key;
    }
}

int partition (int a[], int p, int r){
    int x = a[r];
    int i = (p - 1);

    for (int j = p; j <= r - 1; j++){
        if (a[j] <= x)
        {
            i++;
            exchange(&a[i], &a[j]);
        }
    }
    exchange(&a[i + 1], &a[r]);

    return (i + 1);
}

void quickSort(int a[], int p, int r){

    if (p < r) {
        int q = partition(a, p, r);
        quickSort(a, p, q - 1);
        quickSort(a, q + 1, r);
    }
}

void exchange(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void mergeSort(int a[], int p, int r){

    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(a, p, q);
        mergeSort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

void merge(int a[], int p, int q, int r){

    int i, j;

    int n1 = q - p + 1;
    int n2 =  r - q;
    int L[n1 + 1], R[n2 + 1];

    for (i = 1; i <= n1; i++){
        L[i - 1] = a[p + i - 1];
    }
    for (j = 1; j <= n2; j++){
        R[j - 1] = a[q + j];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = 0;
    j = 0;

    for (int k = p; k <= r; k++) {

        if (L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
    }
}

void printArray(int a[], int n) {

    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}