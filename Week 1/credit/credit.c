#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Function prototype
int isFormatValid(string number);

int main(void)
{
    string cardnumber = get_string("Number ");
    isFormatValid(cardnumber);
}

// Will see if the entry number is valid
int isFormatValid(string number)
{
    // Definition of variables and their initializations
    int i;
    int index;
    int sum_double = 0;
    int sum = 0;
    int len = strlen(number);
    int first_digit = number[0] - '0';
    int prefix = (first_digit * 10) + (number[1] - '0');

    // Checks if all the characters are digits
    for (i = 0; i < len; i++)
    {
        if (!isdigit(number[i]))
        {
            printf("INVALID\n");
            return 0;
        }
    }

    // Logic to validate the credit card number using Luhn's algorithm
    for (i = len - 1, index = 0; i >= 0; i--, index++)
    {
        int digit = number[i] - '0';
        if (index % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            int doubled = digit * 2;
            if (doubled > 9)
                sum += (doubled - 9);
            else
                sum += doubled;
        }
    }
    // If the sum is not a multiple of 10, the number is invalid
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Verifies if the input have the right lenght
    if ((len == 16) && (prefix >= 51 && prefix <= 55))
    {
        printf("MASTERCARD\n");
        return 1;
    }
    else if ((len == 15) && (prefix == 34 || prefix == 37))
    {
        printf("AMEX\n");
        return 1;
    }
    else if (first_digit == 4 && (len == 16 || len == 13))
    {
        printf("VISA\n");
        return 1;
    }
    printf("INVALID\n");
    return 0;
}
