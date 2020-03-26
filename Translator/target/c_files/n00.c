int f(int a, int b)
{
    int c = -99;
    if ((-(a + b) + c) < 0 && a != -1)
    {
        return -(a - b);
    }
    else
    {
        return c;
    }
}

int g(int a) { return 2 * (a + 1) + 1; }

int x;
int y = 5;

int main()
{
    int c = y;
    x = g(c);

    return +1 + f(x, c);
}