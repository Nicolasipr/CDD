#include <bits/stdc++.h>

typedef long double ld;
#define N 100
#define MAX_ERROR 0.001

using namespace std;

// vector < vector <float>> Matrix(N, vector<float>(N, 0));
vector< pair< ld, ld > > polynomium(N, pair<ld, ld>(0,0)); // first = coef and second = exp

void powerCalc(){

}
void derivateCalc(){

}
void functionCalc(){

}

int main(int argc, char** argv){

    
    cout << endl << endl; 

    int j = 0;
    for(int i = 1; i < argc; ++i){
        while(argv[i][j]){

            cout << argv[i][j];

            // argv[i][j] == '-' ? polynomium[i].first = -1: polynomium[i].first = 1;
            if(argv[i][j] ==  '-' )
                polynomium[i].first = -1;

            cout << polynomium[i].first << endl;

             if(argv[i][j] >= 48 && argv[i][j] <= 57){

                if(argv[i][j - 1] != '*'){
                       polynomium[i].first = argv[i][j] - '0';
                }
                else{
                    polynomium[i].second = argv[i][j] - '0';
                }
                
             

            }
        

            j++;
        }

        
       

        cout << endl;
        j = 0;
    }


     return 0;
}