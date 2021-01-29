#include <iostream>
#include <cstdlib>
using namespace std;


struct TDataType { 
    unsigned long long number;
    char *value;
    char *key;
};


struct TTable {
    TDataType *dt;
    size_t size;
    size_t m_ln;
};


TTable *Resize(TTable *hesh,size_t size) {
    TTable *new_hesh = new TTable;
    new_hesh->size = size;
    new_hesh->m_ln = hesh->m_ln;
    new_hesh->dt = new TDataType[size];
    for(unsigned long long i = 0;i < size / 2;i++) {
        new_hesh->dt[i] = hesh->dt[i];
    }
    delete [] hesh->dt;
    delete hesh;
    return new_hesh;  
}


void ToFull(TTable *hesh,unsigned long long n,char *c) {
    unsigned long long b = 0; 
    unsigned long long a;
    unsigned long long i = 1;
    unsigned long long st = 0;
    while(c[i] != '\0') {
        if(c[i] != '+' && c[i] != '-' && c[i] != ' ') {
            a = c[i] - '0';
            b = b*10 + a;
            st++;
        }
        i++;   
    }
    if(hesh->m_ln < st) {
        hesh->m_ln = st;
    }
    hesh->dt[n].number = b;    
}


TTable *CountingSort(TTable *hesh,unsigned long long a[],unsigned long long max) {
    unsigned long long *c = new unsigned long long[max + 1];
    for(size_t i = 0; i < max + 1;i++) {
        c[i] = 0;
    }
    for(size_t i = 0;i < hesh->size; i++) {
        ++c[a[i]];
    }
    for(size_t i = 1;i < max + 1; i++) {
        c[i] = c[i] + c[i - 1]; 
    }
    TTable *new_hesh = new TTable;
    new_hesh->size = hesh->size;
    new_hesh->m_ln = hesh->m_ln;
    new_hesh->dt = new TDataType[new_hesh->size];
    for(long long i = hesh->size - 1; i >= 0; i--) {
        new_hesh->dt[c[a[i]] - 1] = hesh->dt[i];
        c[a[i]]--;
    }
    delete [] hesh->dt;
    delete hesh;
    delete [] c;
    return new_hesh;
}


TTable *RadixSort(TTable *hesh) {
    unsigned long long *a = new  unsigned long long[hesh->size];
    unsigned long long max = 0;
    for(size_t i = 0;i < hesh->m_ln; i++) {
        for(size_t j = 0; j < hesh->size; j++) {
            a[j] = hesh->dt[j].number % 10;
            if(max < a[j]) {
                max = a[j];
            }
            hesh->dt[j].number = hesh->dt[j].number / 10;
        }
        hesh = CountingSort(hesh,a,max);
        max = 0;
    }
    delete [] a;
    return hesh;
}


void InitTable(TTable *hesh) {
    hesh->size = 100;
    hesh->dt = new TDataType[100];
    hesh->m_ln = 0;
}


int main() {
    ios::sync_with_stdio(false);
    TTable *hesh = new TTable;
    InitTable(hesh);
    unsigned long long i = 0;
    hesh->dt[0].value = new char[2049];
    hesh->dt[0].key = new char[65];
    while(scanf("%s %s",hesh->dt[i].key, hesh->dt[i].value) != EOF) {
        ToFull(hesh,i,hesh->dt[i].key);
        i++;
        if(i != hesh->size) {
            hesh->dt[i].value = new char[2049];
            hesh->dt[i].key = new char[65];
        } else {
            hesh = Resize(hesh,hesh->size * 2);
            hesh->dt[i].value = new char[2049];
            hesh->dt[i].key = new char[65];
        }
    }
    delete [] hesh->dt[i].key;
    delete [] hesh->dt[i].value;
    hesh->size = i;
    hesh = RadixSort(hesh);
    for(size_t j = 0;j < hesh->size;j++) {
        cout << hesh->dt[j].key << "\t" << hesh->dt[j].value << endl;
        delete [] hesh->dt[j].key;
        delete [] hesh->dt[j].value;
    }
    delete [] hesh->dt;
    delete hesh;
    return 0;
}
