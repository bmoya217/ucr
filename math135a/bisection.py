def bisection_rec(a , b):
	c = .5*(a+b)
	if round(c,4) == round(a,4) or round(c,4) == round(b,4):
		return c

	fa = exp(a) - 3*a
	fb = exp(b) - 3*b
	fc = exp(c) - 3*c

	if fc < 0:
		print "%.4f".rjust(6)%a + "%.4f".rjust(6)%b + "%.4f".rjust(6)%c + "  -"
	else: 
		print "%.4f".rjust(6)%a + "%.4f".rjust(6)%b + "%.4f".rjust(6)%c + "  +"

	if fc < 0:
		return bisection_rec(c, b)
	return bisection_rec(a, c)

def bisection(a, b):
	print "  a       b       c       fc"
	print " ----------------------------"

	fa = exp(a) - 3*a
	fb = exp(b) - 3*b
	
	if fa * fb > 0:
		return NaN

	if fa < 0:
		return bisection_rec(a, b)
	return bisection_rec(b, a)

from math import exp
from decimal import *
getcontext().prec = 4

print bisection(0, 1)

print ""

print bisection(1,2)
