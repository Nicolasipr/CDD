// correr con "g++ -std=c++11 programa.cpp -o programa && ./programa"
#include <bits/stdc++.h>

// creates a ld shorcut for long double
typedef long double ld;


// define maximum and minimum values values to Newton Raphson iterarions
#define N 1000000
#define MAX_ERROR 10e-15 // if error is less than 10^15 stop
#define MAX_ITERATOR 500  // I don't want to exceed a maximum of 20 itirations

using namespace std;

// GLOBAL VARIABLES
string coefNumber = "0",
       expNumber = "0";
vector< pair< ld, ld > > polynomium(N, pair<ld, ld>(0,0)); // first = coef and second = exp
vector< pair< ld, ld > > derivate(N, pair<ld, ld>(0,0)); // first = coef and second = exp
vector< ld > powers(N, 0); // first = coef and second = exp

ld fx = 0,  // p(x)
   dx = 0;  // p(x)' 

int pIndex = 0;

/*
Functions:
sortBySec
String to Long Double
Power Calculator
Function evaluation 
Derivattive Function Evaluation
*/

bool sortBySec(const pair<int,int> &a, 
              const pair<int,int> &b){ 
    return (a.second > b.second); // helps to sort by segment of pair (exponent)
} 

void stringToLongDouble( int argc, char** argv){
  cout << endl << endl; 

    bool exponent = false;
    int j = 0;

    if(!argv[1][0] || argc == 0){ // null case
      coefNumber = "0";
      expNumber = "0";
    }
    else{

      for(int i = 1; i < argc; ++i){ // if inputs more " " polynomial strings

        while(argv[i][j]){ // travels through " " input

            // cout << "String Coef Number: " << coefNumber << endl;
            // cout << "string Exp Number: " << expNumber << endl;
            // cout << "Current ARGV: " << argv[i][j] << endl;
            // cout << "Exponent state: " << exponent << endl << endl;


          if(argv[i][j] == 'x' || argv[i][j] == 'X'){ // checks for coef and exp changes

            exponent = true;
           

            if(coefNumber == "" || coefNumber == " " || coefNumber == "0"){
              polynomium[pIndex].first = 1;
            }
            else if(coefNumber == "-"){

              polynomium[pIndex].first = -1;
            }
            else{
              polynomium[pIndex].first = stold(coefNumber); // adds coef to pair
            }

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
                if(argv[i][j] != '+')
                  coefNumber += argv[i][j];
                expNumber = "0";
              }
          }
          else{
            if(argv[i][j] != ' ' && argv) // handles stold error with blank space
              coefNumber += argv[i][j];
            
          }
          j++;
        }
        
        exponent = false;

        if(pIndex >= 1){
          if(!polynomium[pIndex].first){
            polynomium[pIndex].first = stold(coefNumber); // last number of "input" exception
          }
          if(!polynomium[pIndex].second){
            polynomium[pIndex].second = stold(expNumber); // last number of "input" exception
          }
        }
        j = 0;
      }

    }

    
}

void derivating(){  // It derivates plynomium p(x)


	for(int i=0; i <= pIndex; i++){ 

      if(polynomium[i].second >= 1){
        derivate[i].second = polynomium[i].second;
        derivate[i].first = polynomium[i].first;

        if (derivate[i].second >= 1){   
          derivate[i].first *= derivate[i].second;
          derivate[i].second -= 1; 
        }
		
	  }
	}
	cout<<"la derivada es ";
		for(int i=0; i < pIndex;i++){
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

void fxCalc(){
  fx = 0;
  dx = 0;
  for(int i = 0; i < polynomium.size(); i++){
    fx += polynomium[i].first * powers[polynomium[i].second]; //it computes polynomial p(x)
    dx += derivate[i].first * powers[derivate[i].second];    // it computes derivative px/dx
  }

}


void NewtonRaphson(ld x_zero){
  ld x_one = 0,
     h = 0;
  
  powerCalc(x_zero);
  fxCalc();
  x_one = x_zero - fx/dx;

  h = x_one - x_zero;

  if(abs(dx) > MAX_ERROR){ //avoiding zero division
    int i = 0;
    while( abs(h) > MAX_ERROR && i < MAX_ITERATOR){
        // cout << "p("<< x_zero << ") = " << fx << endl;
        // cout << "p("<< x_zero << ")' = " << dx << endl;

        x_one = x_zero - fx/dx;
        powerCalc(x_one); // precomputes all powers again
        fxCalc(); // recalculates fx and dx
        h = x_one - x_zero;
        x_zero =  x_one; 
        i++;
        if(dx < MAX_ERROR)
          break;
    }
  }
  else{
    cout << "dx is near to zero, cannot divide it..." << endl;
  }

  cout << "X_zero root value is :" << x_zero << endl;

}

int main(int argc, char** argv){
  
  ios_base::sync_with_stdio(false);
  cout.precision(20); 

  if(argc > 1){

    stringToLongDouble(argc, argv);

    polynomium.resize(pIndex + 1); // it resizes vector to actual length 
    derivate.resize(pIndex + 1);

    sort(polynomium.begin(), polynomium.end(), sortBySec); // sorts polynomium by exponent desc

    derivating();

    ld x = 2;

    for(int i = 0; i < polynomium.size(); i++){
      cout << " Polinomio "<< i + 1 << " :" << endl
          << "\tcoef : " << polynomium[i].first << endl
          << "\texp  : " << polynomium[i].second << endl;
    }
    for(int i = 0; i < 10; i++){
      NewtonRaphson(i);

    }
  }
  else{
    cout << "Please, write a polynomial input..."<< endl;
  }
  return 0;
}
