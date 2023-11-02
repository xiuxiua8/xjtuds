#include <stdio.h>
#include <string.h>

class fraction{
    private:
        /* data */
        int gcd(int a, int b);
    public:
        int u,d;
        fraction(int up,int down){
            u = up;
            d = down;
        }
        int add(fraction f1, fraction f2);
        void printfr(fraction f1, fraction f2);

};

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

fraction add(fraction f1, fraction f2){
    int down = f1.d*f2.d/gcd(f1.d,f2.d);
    int up = f1.u*down/down+f2.u*down/f2.d;
    fraction sumf = fraction(up, down);
    return sumf;
}

void printfr(fraction f1, fraction f2){
    printf("%d/%d", add(f1, f2).u, add(f1, f2).d);
}

int main( ){
    printf("Hello world! \nHello cpp! \n sum = ");
    fraction f1 =fraction(1,2);
    fraction f2 =fraction(2,2);
    printfr(f1, f2);
    return 0;
}

