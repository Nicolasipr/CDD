#include <bits/stdc++.h>

// creates a ld shorcut for long double
typedef long double ld;


// define maximum and minimum values values to Newton Raphson iterarions
#define N 100
#define MAX_ERROR 10e-10 // if error is less than 10^10 stop
#define MAX_ITERATOR 20  // I don't want to exceed a maximum of 20 itirations

using namespace std;

// GLOBAL VARIABLES
string coefNumber = "",
       expNumber;
vector< pair< ld, ld > > polynomium(N, pair<ld, ld>(0,0)); // first = coef and second = exp
int pIndex = 0;

/*
Functions:
String to Long Double
Power Calculator
Function evaluation 
Derivattive Function Evaluation

*/

void stringToLongDouble( int argc, char** argv){
  cout << endl << endl; 

    bool exponent = false;
    int j = 0;

    for(int i = 1; i < argc; ++i){ // if inputs more " " polynomial strings

      while(argv[i][j]){ // travels through " " input

        if(argv[i][j] == 'x' || argv[i][j] == 'X'){ // checks for coef and exp changes
          exponent = true;
          // cout << "String Coef Number: " << coefNumber << endl;
          // cout << "string Exp Number: " << expNumber << endl;
          // num = stold(coefNumber);
          polynomium[pIndex].first = stold(coefNumber); // adds coef to pair
          coefNumber = ""; // reset string
        }
              

        if(exponent){ // while exponent == true
            if(argv[i][j] != '*' && argv[i][j] != 'x' && argv[i][j] != 'X'){
              expNumber += argv[i][j];
              // polynomium[pIndex].second = polynomium[pIndex].second; // add exponent to pair
            }
            if(argv[i][j] == '-' || argv[i][j] == '+'){
              exponent = false; 
              polynomium[pIndex].second = stold(expNumber); 
              pIndex++;
              expNumber = "";
            }
        }
        else{
          if(argv[i][j] ==  '-' ){ // if it finds a - multiply by -1
            polynomium[pIndex].first = -1;
            exponent = false;
          }
          else{
            polynomium[pIndex].first = 1;
            exponent = false;
          }


            coefNumber += argv[i][j];
  
        }
        j++;
      }
      
      exponent = false;
      polynomium[pIndex].second = stold(expNumber);
      j = 0;
    }
    
}

void powerCalc(){

}
void derivateCalc(){

}
void functionCalc(){

}

void NewtonRaphson(){

}

int main(int argc, char** argv){

  stringToLongDouble(argc, argv);
  polynomium.resize(pIndex + 1);
  for(int i = 0; i < polynomium.size(); i++){
    cout << " Polinomio "<< i + 1 << " :" << endl
         << "\tcoef : " << polynomium[i].first << endl
         << "\texp  : " << polynomium[i].second << endl;
  }
  return 0;
}