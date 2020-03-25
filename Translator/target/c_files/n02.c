int y = 5;

int main()
{
    int a = 2;
    {
        a = 2 * y;
    }
    return a + y;
}