Obtaining the machine epsilon of "float" and "double" in two ways.

Machine epsilon is the smallest floating-point number which, 
when added to the floating-point number 1.0, 
produces a floating-point result different from 1.0.

## Method 1: Using machar()
`machar()` is a function included in the book, *'Numerical analysis in C'*.
It determines and returns machine-specific parameters affecting floating-point arithmetic. 
Parameter `eps` is the machine epsilon, which is the value we need.
### Result
```
Machine epsilon by machar():
Epsilon of float:  1.19209e-07 (0.00000011920928955078125)
Epsilon of double: 2.22045e-16 (0.0000000000000002220446049250313080847263336181640625)
```

## Method 2: Using get_eps()
`get_eps()` is my own code finding machine epsilon. 
It finds smallest real number *eps* that satisfies *1+eps≠1*.
By the IEEE standard for floating-point number representation (IEEE 754), 
*eps* is in the form of *2^k*, where *k* is integer. 
### Result
```
Machine epsilon by get_eps():
Epsilon of float:  1.19209e-07 (0.00000011920928955078125)
Epsilon of double: 2.22045e-16 (0.0000000000000002220446049250313080847263336181640625)
```

# Conclusion
the machine epsilon of float is around 1.19209e-07, 
and that of double is around 2.22045e-16.
The values obtained by two different methods were identical. 