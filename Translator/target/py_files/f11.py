# Created on Wed Mar 25 16:05:11 2020

def geo(n):
	acc = 0

	t = n

	while (t < n):
		acc = (acc + t)

		t = (t + 1)


	return acc


def main():
	return ((	geo(3) + 	geo(2)) + 	geo(1))



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
