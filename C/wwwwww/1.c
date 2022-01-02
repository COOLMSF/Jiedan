#include <stdio.h>

int main(int argc, char const* argv[])
{
    double total_money = 0.0;
    double distance = 0.0;
    double discount = 0.0;
    double price = 0.0;
    double weight = 0.0;
    
    // 输入信息
    puts("input distance:");
    scanf("%lf", &distance);
    puts("input price:");
    scanf("%lf", &price);
    puts("input weight:");
    scanf("%lf", &weight);

    // 判断距离, 小于250 折扣为0
    if (distance < 250) {
        discount = 0;
    } else if (distance >= 250 && distance < 500) {
        // 250 <= distance < 500, 折扣为0.02, 2%
        discount = 0.02;
    } else if (distance >= 500 && distance < 1000) {
        discount = 0.05;
    } else if (distance >= 1000 && distance < 2000) {
        discount = 0.08;
    } else if (distance >= 2000 && distance < 3000) {
        discount = 0.1;
    } else {
        discount = 0.15;
    }


    printf("freight = %10.2f\n", price * weight * distance * (1 - discount));
    return 0;
}
