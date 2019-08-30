
          // correr con "g++ -std=c++11 programa.cpp -o programa && ./programa"

          // cout << "String Coef Number: " << coefNumber << endl;
          // cout << "string Exp Number: " << expNumber << endl;
          // cout << "Current ARGV: " << argv[i][j] << endl;
          // cout << "Exponent state: " << exponent << endl << endl;
#include <bits/stdc++.h>

// creates a ld shorcut for long double
typedef long double ld;


// define maximum and minimum values values to Newton Raphson iterarions
#define N 1000000
#define MAX_ERROR 10e-10 // if error is less than 10^10 stop
#define MAX_ITERATOR 20  // I don't want to exceed a maximum of 20 itirations

using namespace std;

// GLOBAL VARIABLES
string coefNumber = "",
       expNumber = "0";
vector< pair< ld, ld > > polynomium(N, pair<ld, ld>(0,0)); // first = coef and second = exp
vector< pair< ld, ld > > derivate(N, pair<ld, ld>(0,0)); // first = coef and second = exp
vector< ld > powers(N, 0); // first = coef and second = exp


int pIndex = 0;

/*
Functions:
String to Long Double
Power Calculator
Function evaluation 
Derivattive Function Evaluation
*/

bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b){ 
    return (a.second > b.second); // helps to sort by segment of pair (exponent)
} 

void stringToLongDouble( int argc, char** argv){
  cout << endl << endl; 

    bool exponent = false;
    int j = 0;

    if(!argv[1][0]){ // null case
      coefNumber = "0";
      expNumber = "0";
    }

    for(int i = 1; i < argc; ++i){ // if inputs more " " polynomial strings

      while(argv[i][j]){ // travels through " " input

          // cout << "String Coef Number: " << coefNumber << endl;
          // cout << "string Exp Number: " << expNumber << endl;
          // cout << "Current ARGV: " << argv[i][j] << endl;
          // cout << "Exponent state: " << exponent << endl << endl;


        if(argv[i][j] == 'x' || argv[i][j] == 'X'){ // checks for coef and exp changes
          exponent = true;
          polynomium[pIndex].first = stold(coefNumber); // adds coef to pair
          coefNumber = ""; // reset string
          if(argv[i][j + 1] != '*')
            expNumber = "1";
        }
              

        if(exponent){ // while exponent == true
            if(argv[i][j] != '*' && argv[i][j] != 'x' && argv[i][j] != 'X'){
              expNumber += argv[i][j];
            }
            if(argv[i][j] == '-' || argv[i][j] == '+'){
              exponent = false; 
              polynomium[pIndex].second = stold(expNumber); 
              pIndex++;
              coefNumber += argv[i][j];
              expNumber = "0";
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

          if(argv[i][j] != ' ') // handles stold error with blank space
            coefNumber += argv[i][j];
  
        }
        j++;
      }
      
      exponent = false;
      if(pIndex >= 1){
      polynomium[pIndex].first = stold(coefNumber); // last number of "input"
      polynomium[pIndex].second = stold(expNumber); // last number of "input"

      }
      j = 0;
    }
    
}

void derivating(){  // It derivates plynomium p(x)

	// ld exp_aux[pIndex],
  //   coef_aux[pIndex],
  //   aux = 0;

	for(int i=0; i <= pIndex; i++){ 

      if(polynomium[i].second >= 1){
        derivate[i].second = polynomium[i].second;
        derivate[i].first = polynomium[i].first;

        if (derivate[i].second >= 1){   
          derivate[i].first *= derivate[i].second;
          // coef_aux[i]= aux;
          derivate[i].second -= 1; 
        }
		
	  }
	}
	cout<<"la derivada es ";
		for(int i=0;i< pIndex;i++){
		  cout<< derivate[i].first <<"x**" << derivate[i].second;

	    if( i + 1 < pIndex)
        cout << " + ";
      }
	  cout << endl << endl;
}

void powerCalc(ld xValue){
  powers.resize(polynomium[0].second + 1); // it resizes powers vector to maximun degree power
  powers[0] = 1;

  for(int i = 0; i <= polynomium[0].second; i++){
    powers[i + 1] = powers[i] * xValue; 
  }

}

void functionCalc(){

}

void NewtonRaphson(){

}

int main(int argc, char** argv){
  
  ios_base::sync_with_stdio(false);
  stringToLongDouble(argc, argv);

  polynomium.resize(pIndex + 1); // it resizes vector to actual length 
  derivate.resize(pIndex + 1);

  sort(polynomium.begin(), polynomium.end(), sortbysec);
  derivating();

  ld x = 2;
  powerCalc(x);
  for(int i = 0; i < powers.size(); i++) //works 
    cout << "Value of "<< x <<"^  " << i << " = "<< powers[i] << endl; // it shows all k-th powers of x


  for(int i = 0; i < polynomium.size(); i++){
    cout << " Polinomio "<< i + 1 << " :" << endl
         << "\tcoef : " << polynomium[i].first << endl
         << "\texp  : " << polynomium[i].second << endl;
  }
  return 0;
}
