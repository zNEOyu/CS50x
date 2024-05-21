#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // checar se é um numero de cartão de crédito ENG check if its a credit card number
    long credit;
    do
    {
        credit = get_long("Number: ");
    }
    while (credit < 1000000000 || credit > 9999999999999999);
    // checar se o numero é válido ENG check if its a valid number

    int check1 = (((credit % 10000000000000000) / 1000000000000000) * 2);
    int check2 = (((credit % 100000000000000) / 10000000000000) * 2);
    int check3 = (((credit % 1000000000000) / 100000000000) * 2);
    int check4 = (((credit % 10000000000) / 1000000000) * 2);
    int check5 = (((credit % 100000000) / 10000000) * 2);
    int check6 = (((credit % 1000000) / 100000) * 2);
    int check7 = (((credit % 10000) / 1000) * 2);
    int check8 = (((credit % 100) / 10) * 2);

    int check = (((check1 % 100) / 10) + (check1 % 10)) + (((check2 % 100) / 10) + (check2 % 10)) +
                (((check3 % 100) / 10) + (check3 % 10)) + (((check4 % 100) / 10) + (check4 % 10)) +
                (((check5 % 100) / 10) + (check5 % 10)) + (((check6 % 100) / 10) + (check6 % 10)) +
                (((check7 % 100) / 10) + (check7 % 10)) + (((check8 % 100) / 10) + (check8 % 10));

    int realcheck = check + ((credit % 1000000000000000) / 100000000000000) + ((credit % 10000000000000) / 1000000000000) +
                    ((credit % 100000000000) / 10000000000) + ((credit % 1000000000) / 100000000) +
                    ((credit % 10000000) / 1000000) + ((credit % 100000) / 10000) + ((credit % 1000) / 100) + (credit % 10);
    // retornar a bandeira ou invalido ENG return flag or invalid

    if (realcheck % 10 == 0)
    {
        if ((credit % 1000000000000000 / 10000000000000) == 34 || (credit % 1000000000000000 / 10000000000000) == 37)
        {
            printf("AMEX\n");
        }

        else if (credit % 10000000000000 / 1000000000000 == 4 || (credit % 10000000000000000 / 1000000000000000) == 4)
        {
            printf("VISA\n");
        }

        else if ((credit % 10000000000000000 / 100000000000000) > 50 && (credit % 1000000000000000 / 10000000000000) < 56)
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
