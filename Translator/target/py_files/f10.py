# Created on Wed Apr  1 14:59:52 2020

def factorial(n):
	if (n < (1 + 1)):
		return 1

	else:
		return (		factorial((n - 1)) + 		factorial((n - 2)))



def main():
	return (((	factorial(4) - 	factorial(2)) - 	factorial(1)) - 	factorial(0))



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
