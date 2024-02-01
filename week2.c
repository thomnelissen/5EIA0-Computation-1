#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 30
#define SPACE_C 32

void printArray(char a[], int length)
{
    printf("[");
    for (int i = 0; i < length; i++)
    {
        char el = a[i];

        if (i != 0)
            printf(",");

        if (el == '\0')
            printf("\\0");
        else if (el == '\n')
            printf("\\n");
        else
            printf("%c", el);
    }
    printf("]\n");
}
void printString(char str[])
{
    putchar('"');
    for (int i = 0;; i++)
    {
        char c = str[i];
        if (c == 0)
        {
            break;
        }
        putchar(c);
    }
    putchar('"');
    putchar('\n');
}
void readLine(char str[], int length)
{
    int i = 0;
    while (1)
    {
        char c = '\0';
        c = getchar();

        if (c == '\n')
        {
            if (i < length - 1)
            {
                str[i] = '\0';
            }
            break;
        }
        str[i] = c;
        i++;
    }
    str[length - 1] = '\0';
}
int readInt(char str[], int length)
{
    int sum = -1;
    int i = 0;
    char c = str[0];

    while (c >= '0' && c <= '9')
    {
        if (sum == -1)
            sum = 0;
        sum += c - 48;
        i++;
        c = str[i];
    }
    return sum;
}
int findFirstOccurrence(char str[], char aChar)
{
    char currC = str[0];
    int i = 0;
    while (currC != '\0')
    {
        currC = str[i];
        if (currC == aChar)
        {
            return i;
        }
        i++;
    }
    return -1;
}
void insertChar(char str[], char aChar, int index)
{
    int len = strlen(str);
    if (index > len)
    {
        return;
    }
    for (int i = len; i >= 0; i--)
    {
        if (i >= index)
            str[i + 1] = str[i];
        if (i == index)
            str[i] = aChar;
    }
}
int strContains(char str[], char s)
{
    for (unsigned int i = 0; i < strlen(str); i++)
    {
        if (str[i] == s)
        {
            return 1;
        }
    }
    return 0;
}
void replaceChars(char str[], char fromString[], char toChar)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (strContains(fromString, str[i]))
        {
            str[i] = toChar;
        }
    }
}
int min(int a, int b)
{
    return (a < b ? a : b);
}
int max(int a, int b)
{
    return (a > b ? a : b);
}
void stringReorder(char str[], int index1, int index2)
{
    int len = strlen(str);
    int graterIndex = max(index1, index2);
    int smallerIndex = min(index1, index2);
    char subArrayLeft[smallerIndex];
    char subArrayMiddle[graterIndex - smallerIndex];
    char subArrayRight[len - graterIndex];
    for (int i = 0; i < len; i++)
    {
        char c = str[i];
        if (i < smallerIndex)
            subArrayLeft[i] = c;
        if (i >= smallerIndex && i < graterIndex)
            subArrayMiddle[i - smallerIndex] = c;
        if (i >= graterIndex)
            subArrayRight[i - graterIndex] = c;
    }
    for (int i = 0; i < len; i++)
    {
        if (i < (len - graterIndex))
            str[i] = subArrayRight[i];
        if (i >= (len - graterIndex) && i < (len - smallerIndex))
            str[i] = subArrayMiddle[i - len + graterIndex];
        if (i >= (len - smallerIndex))
            str[i] = subArrayLeft[i - len + smallerIndex];
    }
}
int main()
{
    char inputString[LENGTH] = "";
    char currStrign[LENGTH] = "";
    do
    {
        printf("Command [qpasoirR123]? ");
        readLine(inputString, 2);
        switch (inputString[0])
        {
        case 'q':
            printf("Bye!\n");
            break;
        case 'p':
            printf("The current string is: ");
            printString(currStrign);
            break;
        case 'a':
            printf("The current array is: ");
            printArray(currStrign, LENGTH);
            break;
        case 's':
            printf("Please enter a string? ");
            readLine(currStrign, LENGTH);
            break;
        case 'o':
        {
            char c[1] = "";
            printf("Find first occurrence of which character? ");
            readLine(c, 2);
            printf("The first occurrence of '%c' is at index %d\n",
                   c[0],
                   findFirstOccurrence(currStrign, c[0]));
            break;
        }
        case 'i':
        {
            char c[1] = "";
            char index[3] = "";
            printf("Insert which character? ");
            readLine(c, 2);
            printf("At what index? ");
            readLine(index, 4);
            //safety checks
            if (strlen(currStrign) == LENGTH)
            {
                break;
            }
            insertChar(currStrign, c[0], atoi(index));
            break;
        }
        case 'r':
        {
            char fromString[LENGTH] = "";
            char toChar[1] = "";
            printf("Replace which characters? ");
            readLine(fromString, LENGTH);
            printf("with which character? ");
            readLine(toChar, 2);
            replaceChars(currStrign, fromString, toChar[0]);
            break;
        }
        case 'R':
        {
            char index1[3] = "";
            printf("Please enter index 1? ");
            readLine(index1, 4);
            char index2[3] = "";
            printf("Please enter index 2? ");
            readLine(index2, 4);
            stringReorder(currStrign, atoi(index1), atoi(index2));
            break;
        }
        case '1':
            replaceChars(currStrign, "aeiou", 'a');
            break;
        case '2':
        {
            char c = '.';
            for (int i = 0; c != '\0'; i++)
            {
                c = currStrign[i];
                int len = strlen(currStrign);
                char nextC = i < len - 1 ? currStrign[i + 1] : SPACE_C;
                if (c == SPACE_C && strContains("aeiouAEIOU", nextC) == 0 && nextC > 64 && nextC < 123)
                {
                    insertChar(currStrign, 'y', i + 1);
                    insertChar(currStrign, 'a', i + 1);
                }
                else if (i == 0 && strContains("aeiouAEIOU", c) == 0 && c > 64 && c < 123)
                {
                    insertChar(currStrign, 'y', i);
                    insertChar(currStrign, 'a', i);
                }
            }
            break;
        }
        case '3':
        {
            int len = strlen(currStrign);
            int wordsFound = 0;
            int sliceIndex = -1;
            for (int i = 0; sliceIndex == -1 && i < len; i++)
            {
                char c = currStrign[i];
                char prevC = i == 0 ? SPACE_C : currStrign[i - 1];
                char nextC = i == len - 1 ? SPACE_C : currStrign[i + 1];
                if (c != SPACE_C && prevC == SPACE_C)
                {
                    wordsFound += 1;
                }
                if (c != SPACE_C && nextC == SPACE_C && wordsFound == 2)
                {
                    sliceIndex = i + 2;
                }
            }
            stringReorder(currStrign, 0, sliceIndex);
            insertChar(currStrign, SPACE_C, len - sliceIndex);
            currStrign[len] = 0;
            break;
        }
        default:
            printf("Unknown command '%c'\n", inputString[0]);
            break;
        }
    } while (inputString[0] != 'q');
    return 0;
}x