int f() {
	int y, x = 5;

	y = 2 + 2* x++;
	y -= ++x * 2;
	x--;
	return y + --x;
}