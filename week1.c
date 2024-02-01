#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char cmd = 'a';
    float curr_re = 0.0;
    float curr_im = 0.0;
    float new_re = 0.0;
    float new_im = 0.0;
    float temp_re = 0.0;
    float temp_im = 0.0;
    int power = 0;
    int i = 1;
    int x = 1;
    int y = 21;ñ
    int int_im = 0;
    int int_re = 0;

    printf("** Complex Calculator **\n");

    while (cmd != 'q')
    {
        printf("Operation [0+-*crpq]? ");
        scanf(" %c", &cmd);
        switch(cmd)
        {
        case 'q':
            break;

        case '+':
            printf("Complex operand? ");
            scanf(" %f", &new_re);
            scanf(" %f", &new_im);
            curr_re += new_re;
            curr_im += new_im;
            break;

        case '-':
            printf("Complex operand? ");
            scanf(" %f", &new_re);
            scanf(" %f", &new_im);
            curr_re -= new_re;
            curr_im -= new_im;
            break;

        case '0':
            curr_re = 0.0;
            curr_im = 0.0;
            break;

        case 'c':
            curr_im *= -1;
            break;

        case '*':
            printf("Complex operand? ");
            scanf(" %f", &new_re);
            scanf(" %f", &new_im);
            temp_re = curr_re;
            temp_im = curr_im;
            curr_re = temp_re * new_re - temp_im * new_im;
            curr_im = temp_re * new_im + temp_im * new_re;
            break;

        case 'r':
            printf("Natural operand? ");
            scanf(" %d", &power);
            i = 1;
            if(power  == 0)
            {
                curr_re = 1;
                curr_im = 0;
                break;
            }
            new_im = curr_im;
            new_re = curr_re;
            while(i < power)
            {
                temp_re = new_re * curr_re - new_im * curr_im;
                temp_im = new_re * curr_im + new_im * curr_re;
                new_re = temp_re;
                new_im = temp_im;
                i++;
            }
            curr_im = new_im;
            curr_re = new_re;
            break;

        case 'p':
            y = 21;
            x = 1;
            int_im = curr_im;
            int_re = curr_re;
            while(y > 0)
                {
                for(x = 1; x <= 21; x++)
                {
                    if(x == int_re + 11 && y == int_im + 11)
                    {
                        printf("*");
                    }
                    else
                    {
                        if(x == 11 && y != 11)
                        {
                            printf("|");
                        }
                        else
                        {
                            if(y == 11 && x != 11)
                            {
                                printf("-");
                            }
                            else
                            {
                                if(x == 11 && y == 11)
                                {
                                    printf("+");
                                }
                                else
                                {
                                    printf(".");
                                }
                            }
                        }
                    }
                }
                printf("\n");
                y--;
            }
            break;

        default :
            printf("Invalid command \'%c\'\n", cmd);
            break;
        }
        if(cmd != 'q')
        {
            if(curr_im >= 0)
            {
                printf("Current value is %f+%fi\n", curr_re, curr_im);
            }
            if(curr_im < 0)
            {
                printf("Current value is %f%fi\n", curr_re, curr_im);
            }
        }
        if (cmd == 'q')
        {
            if(curr_im >= 0)
            {
                printf("Current value is %f+%fi\nBye!\n", curr_re, curr_im);
            }
            if(curr_im < 0)
            {
                printf("Current value is %f%fi\nBye!\n", curr_re, curr_im);
            }        
        }
    }
    return 0;
}
