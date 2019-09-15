# HW #2: Errors
Solution to *Numerical Methods for Engineers, 7th ed.*

### Environment
- Platform: x86_64-apple-darwin19.0.0
- Compiler: clang-1100.0.33.8
- C standard: C99

## Chapter 3: Approximations and Round-Off Errors

### Problem 3.6
```
Method #1
Approximate value: 6.706341e-03
Relative error:    4.690738e-03

Method #2
Approximate value: 6.737949e-03
Relative error:    -3.450780e-07
```
As shown above, second approach gives more precise value.

### Problem 3.7
**3-digits with chopping.**  
```
6x = 3.46
x^2 = 0.332, 3x^2 = 0.996, 1-3x^2 = 0.004.
f'(0.557) ≈ 3.46/0.004^2 = 216250
```
**4-digits with chopping.**
```
6x = 3.462
x^2 = 0.3329, 3x^2 = 0.9987, 1-3x^2=0.0013.
f'(0.557) ≈ 3.462/0.0013^2 = 2048520.710059172
```


## Chapter 4: Truncation errors and the Taylor series

### Problem 4.2
```
Step #1: estimated 4.516886e-01, relative err 10.695721%
Step #2: estimated 5.017962e-01, relative err 0.357954%
Step #3: estimated 4.999646e-01, relative err 0.007087%
Step #4: estimated 5.000004e-01, relative err 0.000087%
Step #5: estimated 5.000000e-01, relative err 0.000001%
Step #6: estimated 5.000000e-01, relative err 0.000000%
Step #7: estimated 5.000000e-01, relative err 0.000000%
Step #8: estimated 5.000000e-01, relative err 0.000000%
Step #9: estimated 5.000000e-01, relative err 0.000000%
```
It found the exact value whithin 9 steps.  
Note that the result of a line of code below 
```c
term *= -M_PI * M_PI / 9;
```
is more precise than
```c
term *= -(M_PI / 3) * (M_PI / 3);
```
because the former yields less roundoff error.

### Problem 4.5
```
True value: 554.000000
Step #1: estimated -62.000000, relative err 111.191336%
Step #2: estimated 78.000000, relative err 85.920578%
Step #3: estimated 354.000000, relative err 36.101083%
Step #4: estimated 554.000000, relative err 0.000000%
```