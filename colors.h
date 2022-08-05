#include <stdio.h>

void black(void)
{
    printf("\033[0;30m"); //Set the text to the color black
}

void red(void)
{
    printf("\033[0;31m"); //Set the text to the color red
}

void green(void)
{
    printf("\033[0;32m"); //Set the text to the color green
}

void yellow(void)
{
    printf("\033[0;33m"); //Set the text to the color blue
}

void blue(void)
{
    printf("\033[0;34m"); //Set the text to the color blue
}

void purple(void)
{
    printf("\033[0;35m"); //Set the text to the color purple
}

void cyan(void)
{
    printf("\033[0;36m"); //Set the text to the color cyan
}

void white(void)
{
    printf("\033[0;37m"); //Set the text to the color blue
}

void reset(void)
{
    printf("\033[0m"); //Resets the text to default color
}