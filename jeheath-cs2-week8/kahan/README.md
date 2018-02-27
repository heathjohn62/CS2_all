The naive summation does not understand how floating point numbers are stored. 
In each floating point number, there is a sign bit, a set of exponent bits, and a set of 
mantissa bits. The sum begins with 1, and then proceeds to add increments of 10^-8.
However, the smallest increment you can make to the floating point number 1 is to 
add a bit to the (empty) mantissa, and this amounts to an increase of roughly 10^-7. 
Since the program knows this increase is too much, it will keep the value at 1 rather 
than actually increase the number at each addition. This will prevent each of the 10^8 
additions from changing the number, leaving the program to return the first number in
the vector, 1. 

Try  as I have, I can't get the pairwise summation to work. I think the implemetation, or
at least the idea behind it, is correct, but I get nothing but errors unless I make the 
bound for just doing naive summation so small that it only divides the vector into two,
using the recursive call only once. Furthermore, this result is 1.25, which is a low quality 
approximation for 2 at best. It makes sense that the smaller groups that could be 
made, the more similar the final numbers  added would be, and thus accuracy would
increase. However, there is also probably a peak in accuracy midway, because dividing 
the sum into groups of 1 is somewhat  equivalent to the naive sum algorithm, although 
the recursive implementation of the pairwise algorithm should make it a little better
due to the order in which numbers are added. I don't really know why you might use this
algorithm in comparison to the kahan algorthm. that one works, and isn't nearly as 
much trouble. 


