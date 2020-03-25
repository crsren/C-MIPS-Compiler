void f(int x) { x = x + 1;  return; }

int s = -3;

int main()
{
    int r = 2;
    f(s);

    if (s < r && s == -3) { s = r; r = 4; }

    if (r || 0 ) {
	r = -2*4-1;
    }

    if (1 == 0) return 11;
    return s;
}