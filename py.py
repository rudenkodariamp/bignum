import bignumcpp as l

def GCD_Ex(a,b):
    zero=l.Long("0.txt")
    x1=l.Long("0.txt")
    x2=l.Long("1.txt")
    y1=l.Long("1.txt")
    y2=l.Long("0.txt")
    while b > zero:
        r=a%b
        q=a/b
        a=b
        b=r
        
        r=q*x1
        xx=x2-r
        r=q*y1
        yy=y2-r

        x2=x1
        x1=xx
        y2=y1
        y1=yy

    return x2,y2

a=l.Long("n1.txt")
b=l.Long("n2.txt")
z=l.Long("0.txt")
f1=l.Long("1.txt")
z=l.Long("0.txt")
f1=l.Long("1.txt")
f2=f1 + f1
f3=f2 + f1
f4=f2 + f2
f5=f4 + f1
f8=f4 + f4
t=z
c=z

x,y=GCD_Ex(a,b)

q=x*a
r=y*b
gcd=q+r
  
a1=l.Long("n1.txt")
b1=l.Long("n2.txt")
     
if gcd==z:
  gcd.outf("d2.txt")
r=f1
if a1<z:
	a1=z-a1
	if b1%f4==f3:
		r=z-r
a1.outf("d2.txt")
while a1 != z :
	if a1 == z:
		break
		print 'end11'

	while a1%f2 == z:
		t=t+f1
		a1=a1/f2

	if t%f2==f1:
		if b1%f8==f3 or b1%f8==f5:
			r=z-r
	if a1%f4==b1%f4==f3:
		r=z-r
	c = a1
	a1 = b1 % c
	b1 = c
r.outf("d2.txt")


print 'end'
