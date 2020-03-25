# Created on Wed Mar 25 16:51:27 2020

def main():
	xx = 0

	y = 0

	acc = 2

	xx = 0

	y = 0

	while (xx < 6):
		y = 0

		while (y != xx):
			acc = (acc + y)

			y = (y + 1)


		xx = (xx + 2)


	return ((acc - xx) - y)



if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)
