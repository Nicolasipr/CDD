# Newton Raphson method

This code will grab an argument from the command line and it will solve a polynomial of degree d ∈ ℕ. Or at least it will
 show an approximation of the current root of that polynomial f(x).

## Folder Organization

- [x] Getting arguments from Command line
- [x] parsing argv to useful data 
- [ ] Sorting polynomial function for better handling
- [x] parsing argv to useful data 
- [ ] Calculating power of k-th term
- [ ] Evaluating Function
- [ ] Calculating derivative
- [ ] Evaluating derivative
- [ ] Showing x i-th term
- [ ] parsing argv to useful data 

## How it works
We have divide the code in several functions to make it more easy to read and comprehend. 

    .
    ├── ...
    ├── StringtoLongDouble()           # Parse the command line argument to long double useful data in a vector of pairs.
    ├── PowerCalculator()               # pre-compute all the polynomial power of degree d, in order  to just calculate that once.
    ├── FunctionEvaluation()            # it uses pre-computed data to evaluate f(x)
    ├── DerivativeCalculator()          # Calculates it's  derivative
    ├── DerivativeEvaluation()          # Evaluates f(x)' function
    ├── NewtonRaphson()                 # Uses all functions from above to calculate its roots
    └── ...


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)