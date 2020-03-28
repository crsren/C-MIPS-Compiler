# Created on Sat Mar 28 15:35:22 2020

def f(a,b):
	c = -99

	if (((-(a + b) + c) < 0) and (a != -1)):
		return -(a - b)

	else:
		return c



def g(a):
	return ((2 * (a + 1)) + 1)


x = 0
y = 5
def main():
	global x
	global y
	c = y

	x = 	g(c)

	return (1 + 	f(x,c))



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
