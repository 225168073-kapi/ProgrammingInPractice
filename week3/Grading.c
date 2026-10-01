#include <stdio.h>

int main(){


    char StudentName[30];
    int mark;
    

    printf("Enter the name of the student!\n");
    scanf("%s", StudentName);

    printf("Enter the mark of the student!\n");
    scanf("%d", &mark);

    if (mark >= 80)
    {
        printf("You got A\n");
    }
    else if (mark >= 70)
    {
        printf("You got B\n");
    }
    
        else if (mark >= 60)
    {
        printf("You got C\n");
    }

     else if (mark >= 50)
    {
     printf("You got D\n");
    }

        else if (mark >= 40)
    {
        printf("You got E\n");
    }

    return 0;
    }