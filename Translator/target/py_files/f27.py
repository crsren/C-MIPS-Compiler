# Created on Wed Mar 25 16:05:13 2020

def f(x):
	return (x + 1)


def g(x):
	return 	f((x + 1))


def main():
	g = 0

	g = 4

	return 	f(2)



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
