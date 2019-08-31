# Newton Raphson method

This code will grab an argument from the command line and it will solve a polynomial of degree d ∈ ℕ. Or at least it will
show an approximation of the current root of that polynomial f(x).
 
We all know Newton Raphson or Newton Fourier iteration method of root finding, and it can easily solve non-linear equations



![equation](https://latex.codecogs.com/png.latex?x_1%20%3D%20x_0%20-%20%5Cfrac%7Bf%28x_0%29%7D%7Bf%27%28x_0%29%7D)



and given the value of x = xi at the end of the ith iteration, we obtain xi+1 as: 


![equation](https://latex.codecogs.com/png.latex?x_%7Bi&plus;1%7D%20%3D%20x_i%20-%20%5Cfrac%7Bf%28x_i%29%7D%7Bf%27%28x_i%29%7D)


As far as our code does, it shows some of the real roots, since part of the complex roots were not part of this assigment. 
If some polynomial has k same roots, it's going to display a single root value. 

## To be completed

- [x] Getting arguments from Command line
- [x] parsing argv to useful data 
- [x] Sorting polynomial function for better handling
- [x] parsing argv to useful data 
- [x] Calculating power of k-th term
- [x] Evaluating Function
- [x] Calculating derivative
- [x] Evaluating derivative
- [x] Showing x i-th term
- [ ] Checking issues with  negatives roots
- [ ] multiple  roots
- [ ] complex roots
- [ ] Completing README.md
 

## How it works
We have divide the code in several functions to make it more easy to read and comprehend. And we've work with goblal variables
in order to make life more easier, because... Why not? :dog:
### Functions
    .
    ├── ...
    ├── sortBySec(pair a, pair b)                      # Helps to selects the exponent side of pair vector and order it
    ├── StringtoLongDouble(argc, **argv)     # Parse the command line argument to long double useful data in a vector of pairs.
    ├── derivating()                                            # It derivatives polynomial p(x) into p(x)'
    ├── PowerCalc()                                            # pre-compute all the polynomial power of degree d, saves it into a vector.
    ├── fxCalc(x_0)                                             # Evaluates both p(x) and p(x)' with a value of x_0 given
    ├── NewtonRaphson()                                 # Uses all functions from above to calculate its roots
    └── ...

#### SortBySec(pair a, pair b): Sort by Exponent
This piece of code right here returns the comparison of pairs by its second attribute. In order to sort the polynomial entity 
we had to sort it to dislay it effectively. It is now completely necessary but we did it in order to comprehend or data better.

```cpp
bool sortBySec(const pair<int,int> &a, 
              const pair<int,int> &b){ 
    return (a.second > b.second); // helps to sort by segment of pair (exponent)
} 
```
This segment of code it's used in this specific part of our work, right here: 
```cpp 
 sort(polynomium.begin(), polynomium.end(), sortBySec); 
```

#### StringtoLongDouble(argc, **argv): String to Long Double 
This function what basically does is to collect all the string inputs given as parameters in main() section and work it as 
a long double vector of pairs. 

```cpp 
 int main(int argc, char** argv){
 
  // some code
  ...
  
 }
```

And we use StringtoLongDouble  (Actually pointer of pointer of char) to divide the coefficient and exponent as pair.first and
pair.second, as shown before.


#### derivating():   
Since it's just a simple polynomial, its derivative it's considerably easy.
```cpp
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
}
``` 
Add that derivate to a vector of pairs called "derivate" containing those coefficient and exponent as first and second.
 

#### PowerCalc(): Computes all Powers of X P
It pre-computes all k powers of x up to max polynomial degree d, then we seek those values and we don't have to calculate them every them we look 
for the k value of x.

```cpp
void powerCalc(ld xValue){
  powers.resize(polynomium[0].second + 1);      // it resizes powers vector to maximun degree power
  powers[0] = 1;                                                        // sets something to the power of zero equals to 1
  
  for(int i = 0; i <= polynomium[0].second; i++){
    powers[i + 1] = powers[i] * xValue; 
  }
}
``` 
### fxCalc():  Function evaluation of a given x
What it does it's simple multiply the value of the coefficient with the assigned power k and look it into the precomputed k powers vector

```cpp

void fxCalc(){
  fx = 0;
  dx = 0;
  for(int i = 0; i < polynomium.size(); i++){
    fx += polynomium[i].first * powers[polynomium[i].second]; //it computes polynomial p(x)
    dx += derivate[i].first * powers[derivate[i].second];    // it computes derivative px/dx
  }

}
```

#### NewtonRaphson(): 
Here's where everything comes together. We iterate under a maximum of 50 steps or until it reach the maximum error tolerance that we had fixed
earlier (10^-15). Once that's done, checks if the answer given it's already on the roots unordered map, if already exist, do not save it and keep going.


```cpp
void NewtonRaphson(ld x_zero, int &sol){
  ld x_one = 0,
     h = 0;
  
  powerCalc(x_zero);
  fxCalc();

  x_one = x_zero - fx/dx;
  h = x_one - x_zero;

  if(abs(dx) > MAX_ERROR){ //avoiding zero division
    int i = 0;

    while( abs(h) > MAX_ERROR && i < MAX_ITERATOR){

        x_one = x_zero - fx/dx;
        powerCalc(x_one); // precomputes all powers again
        fxCalc(); // recalculates fx and dx
        h = x_one - x_zero;
        x_zero =  x_one; 
        i++;
        if(dx < MAX_ERROR)
          break;
    }

    if(fx == 0.0 || abs(fx) < 10e-15){
      if(!roots[x_zero]){
        roots[x_zero] = x_zero;
        sol++;
      }

    }
  }
  else{
    // cout << "dx is near to zero, cannot divide it..." << endl;
  }

  cout << "X root value is : " << x_zero << endl;

}
``` 

It's meant to work under this command line input: 

```
$ ./programa "some polynomial input"
```

If you haven't compile it you can still do it by running this line of code under your command line:

```
$ g++ -std=c++11 programa.cpp -o programa
```
 That creates and executable that can be used as shown above.


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)