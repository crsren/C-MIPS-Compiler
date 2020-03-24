# Created on Tue Mar 24 21:33:30 2020

x=0

def gg():
	global x
	global x
	x = (x + 1)

	return x



def main():
	global x
	global x
	return (gg() + gg())




if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
