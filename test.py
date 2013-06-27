#!/usr/bin/python
import sys
import bignumcpp as l

first = l.Long(sys.argv[1])
second = l.Long(sys.argv[3])

# Compute
op = sys.argv[2]
if op == "+":
	res = first + second
elif op == "-":
	res = first - second
elif op == "*":
	res = first * second
elif op == "/":
	res = first / second
elif op == "%":
	res = first % second


if len(sys.argv) > 5:
		mod = l.Long(sys.argv[5])
		res = res % mod


# Write to res file
res.outf(sys.argv[4])
