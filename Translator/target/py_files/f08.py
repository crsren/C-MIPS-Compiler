# Created on Wed Apr  1 14:59:51 2020

x = 0
def gg():
	global x
	x = (x + 1)

	return x


def main():
	global x
	return (	gg() + 	gg())



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
