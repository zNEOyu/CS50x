#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dime(int cents);
int calculate_nickel(int cents);
int calculate_penny(int cents);

// peça o usuário quanto vc deve ENG: how many o owed the user
int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // quarters
    int quarters = calculate_quarters(cents);

    cents = cents - (quarters * 25);

    // dime
    int dime = calculate_dime(cents);

    cents = cents - (dime * 10);

    // nickel
    int nickel = calculate_nickel(cents);

    cents = cents - (nickel * 5);

    int penny = calculate_penny(cents);

    cents = cents - (nickel * 1);

    printf("%i\n", quarters + dime + nickel + penny);
}
// calcule quantos 1/4 vc precisa pagar ENG: calcule how many quarters ou owed

int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}
// calcule quantos 1/10 vc precisa pagar ENG: calcule how many dime ou owed

int calculate_dime(int cents)
{
    int dime = 0;
    while (cents >= 10)
    {
        dime++;
        cents = cents - 10;
    }
    return dime;
}
// calcule quantos 1/20 vc precisa pagar ENG: calcule how many nickel ou owed

int calculate_nickel(int cents)
{
    int nickel = 0;
    while (cents >= 5)
    {
        nickel++;
        cents = cents - 5;
    }
    return nickel;
}
// calcule quantos 1/100 vc precisa pagar ENG: calcule how many penny ou owed

int calculate_penny(int cents)
{
    int penny = 0;
    while (cents >= 1)
    {
        penny++;
        cents = penny - 1;
    }
    return penny;
}
