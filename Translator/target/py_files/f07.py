# Created on Wed Mar 25 21:08:30 2020

a = 0
def main():
	global a
	a = 12

	return a



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
