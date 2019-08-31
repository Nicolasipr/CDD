# Newton Raphson method

This code will grab an argument from the command line and it will solve a polynomial of degree d ∈ ℕ. Or at least it will
 show an approximation of the current root of that polynomial f(x).
 
We all know Newton Raphson or Newton Fourier iteration method of root finding, and it can easily solve non-linear equations



![equation](https://latex.codecogs.com/png.latex?x_1%20%3D%20x_0%20-%20%5Cfrac%7Bf%28x_0%29%7D%7Bf%27%28x_0%29%7D)



and given the value of x = xi at the end of the ith iteration, we obtain xi+1 as: 


![equation](https://latex.codecogs.com/png.latex?x_%7Bi&plus;1%7D%20%3D%20x_i%20-%20%5Cfrac%7Bf%28x_i%29%7D%7Bf%27%28x_i%29%7D)

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
 

## How it works
We have divide the code in several functions to make it more easy to read and comprehend. 

    .
    ├── ...
    ├── sortBySec(pair a, pair b)                      # Helps to selects the exponent side of pair vector and order it
    ├── StringtoLongDouble(argc, **argv)     # Parse the command line argument to long double useful data in a vector of pairs.
    ├── derivating()                                            # It derivatives polynomial p(x) into p(x)'
    ├── PowerCalc()                                            # pre-compute all the polynomial power of degree d, saves it into a vector.
    ├── fxCalc(x_0)                                             # Evaluates both p(x) and p(x)' with a value of x_0 given
    ├── NewtonRaphson()                                 # Uses all functions from above to calculate its roots
    └── ...

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