# Created on Wed Mar 25 16:51:31 2020

def fun1(a):
	a = (-a + 3)

	return 


def fun2(a):
	a = (-a + (2 * a))

	return a


x = 0
y = 1
def main():
	global x
	global y
	fun1(y)
	x = 5

	return 	fun2(x)



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
