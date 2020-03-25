void fun1(int a)
{
    a = -a + 3;
    return;
}

int fun2(int a)
{
    a = -a + 2 * a;
    return a;
}

int x;
int y = 1;

int main()
{
    fun1(y);
    x = 5;
    return fun2(x);
}