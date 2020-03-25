# Created on Wed Mar 25 16:51:26 2020

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
