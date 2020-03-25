void f(int x) { x = x + 1;  return; }

int s = -3;

int main()
{
    f(s);
    int r = 2;
    if (s < r && s == -3)
        return 9;

    if (1 == 0) return 11;
    return s;
}