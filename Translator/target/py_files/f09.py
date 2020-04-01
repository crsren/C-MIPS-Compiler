# Created on Wed Apr  1 14:59:51 2020

def function(aa,b):
	if (aa < b):
		aa = (aa - 1)

		if (b < aa):
			b = (b + 3)

			if (aa == b):
				return (aa * b)



		return b


	return 13


def main():
	return (((	function(0,0) + 	function(1,2)) + 	function(4,3)) + 	function(6,7))



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
