#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <conio.h> 

//color defined
#define CYN "\e[0;36m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
#define UBLK "\e[4;30m"
#define BHWHT "\e[1;97m"
#define reset "\e[0m"

void welcome();
void display_error_input_num(char *y_n,int *end);
void invalid_input(int *end);
void read_through_file(int numList[],int *count, int *i); 
void read_through_terminal(int numList[],int *count);
void printNumArray(int *numList, int start, int smallest, int count, int arrow_locater); 
void swapValue(int *numList, int start, int smallest, int count); 
void swapMoveAnimation(int *numList, int start, int smallest, int movPosition, int count); 
void end_display(int *end,int *count,int numList[]);

int main() {
    int numList[100],count=0,i; 
    int end =1;
    welcome();
    char input = getche();
    int input_num  = input - '0';//   coversion of character into integer
    if(input_num==1)
        read_through_terminal(numList,&count);
    else if(input_num==2)
    {
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t\t   P l e a s e  E n s u r e  t h e  f i l e  \"number.txt\"  e x i s t s  i n  t h e  \"C_prolect\" F o l d e r. \n");
        printf("\n\t\t\t\t\t   I f   t h e   f i l e   e x i s t s   p r e s s   Y   e l s e   N.\n");
        printf("\t\t\t\t\t   I N P U T  :  ");
        char y_n = getche();
        if (y_n == 'Y' || y_n == 'y' )
        {
        read_through_file(numList,&count,&i);
        }
        else
        {
            display_error_input_num(&y_n,&end);
        }
    }
    else
        invalid_input(&end);

    // Beginning of the simulation
    int temp; 
    int smallest=0; 
    int start=0; 
    for (int i = 0; i < count; i++)  // this loop repeats  printNumArray() a 4*"count" times and then runs swapvalue() a 1*"count" times
    {
        start=i; 
        smallest=i; 
        for (int j = i + 1; j<count; j++) // this loop repeats  printNumArray() a "count-1" times and then runs swapvalue() a 1 times
        {
            if (numList[smallest] > numList[j]) 
                smallest=j;  //---->step : 1
            printNumArray(&numList[0], start, smallest, count, j); //---->call : 2
            }
            Beep(500,100); //--->ejection beep
            usleep(600000);
            swapValue(&numList[0], start,smallest, count); 
        }
        end_display(&end,&count,numList);
    return 0; 
}


void printNumArray(int *numList, int start, int smallest, int count, int arrow_locater)
 // ---->  Responsible to display green, red integers array . Also displays " ^ " below integer array.
{
    system("cls");
    printf("\n\n\n");
    printf("%s", BGRN); 
    printf("\t\t\t\t\t\t\t");
    for(int ix=0; ix<start; ix++) //1
        printf("%03d   ", numList[ix]); 
    printf("%s",reset); 
    for(int ix=start; ix<count; ix++) //2
    {
        if(ix==smallest) 
            printf("%s%03d   %s",BRED, numList[ix],reset); 
        else 
            printf("%s%03d   ",BWHT,numList[ix]); 
    }
    if(-1!=arrow_locater) 
    {
        printf("\n"); 
        printf("\t\t\t\t\t\t\t");
        for(int ix=0; ix < arrow_locater*6+1; ix++) //3
            printf(" "); 
        printf("%s^",BYEL); 
        printf("\n");
    } 
    usleep(900000); // ---> For freezing " ^ " for one second one line below the integer
}


void read_through_file(int numList[],int *count, int *i) 
{
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t   R e s p o n s e   R e c o r d e d\n");
    sleep(1);
    system("cls");
    for(int i=0;i<3;i++)
    {
        if(i==0)
        {
            printf("\n\n\n\t\t\t\t\t\t   L o a d i n g   t h e   s i m u l a t o r ");
            Beep(900,10);
            sleep(1);
            usleep(500000);
            printf(" *  ");
            usleep(500000);
        }
        else
        {
            Beep(900,10);
            usleep(200000);
            printf(" *  ");
            usleep(250000);
        }
    }
    //  ---> Algorithm to fetch data from "number.txt" and get the entries for numList
    char *token; 
    char arr[256]; 
    FILE *InputFile; 
    InputFile = fopen("number.txt", "r"); 
    fscanf(InputFile,"%s",arr); 
    token = strtok (arr,","); 
    *i = 0; 
    while(token != NULL) //'\0'
    {
        numList[*i] = atoi(token); 
        token= strtok (NULL, ",");
        *i = *i+1; 
    }
    *count = *i; 
}


void read_through_terminal(int numList[],int *count)
{
    int n;
    system("cls");
    // printf("\t\t\t\t\t\t    I N P U T  :  ");
    printf("\n\n\n\t\t\t\t\t\t   E n t e r   t h e   n u m b e r s  y o u   w a n t   t o   e n t e r  :  \n");
    printf("\t\t\t\t\t\t   I n p u t  :  ");
    scanf("%d",&n);
    system("cls");
    printf("\n\n\n\t\t\t\t   E n t e r   t h e   n u m b e r s   b e l o w.  P r e s s   E n t e r   t o   I n p u t   n e x t.\n");
    printf("\t\t\t\t   I n p u t   N u m b e r s  :  \n");
    for(int j=0;j<n;j++)// ---> Receive Input from the user
    {
        printf("\n\t\t\t\t   %d .  ",j+1);
        scanf("%d",&numList[j]);
    }
    *count = n;
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t   R e s p o n s e   R e c o r d e d\n");
    sleep(1);
    system("cls");
    for(int i=0;i<3;i++)
    {
        if(i==0)
        {
            printf("\n\n\n\t\t\t\t\t\t   L o a d i n g   t h e   s i m u l a t o r ");
            Beep(900,10);
            sleep(1);
            usleep(500000);
            printf(" *  ");
            usleep(500000);
        }
        else
        {
            Beep(900,10);
            usleep(200000);
            printf(" *  ");
            usleep(250000);
        }
    }
}

void welcome()
{
    system("cls");
    printf("\n\n\n\n");
    Beep(250,100);
    usleep(900000);
    usleep(500000);

    printf("\t\t\t\t\t\t\t\t%s    T E A M   H O O L I  \n",BWHT);
    sleep(1);
    system("cls");
    printf("\n\n\n\n");
    Beep(250,100);
    usleep(150000);
    printf("\t\t\t\t\t\t\t\t%s   W E L C O M E S\n",BWHT);
    sleep(1);
    system("cls");
    printf("\n\n\n\n");
    Beep(250,100);
    usleep(150000);
    printf("\t\t\t\t\t\t\t\t%s   Y O U \n",BWHT);
    sleep(1);
    system("cls");
    printf("\n\n\n\n");
    Beep(250,100);
    usleep(150000);
    printf("\t\t\t\t\t\t\t\t%s    T O\n",BWHT);
    sleep(1);
    system("cls");
    printf("\n\n\n");
    Beep(250,100);
    usleep(150000);
    printf("%s",reset);
    printf("\t\t\t\t\t\t\t%s    B u b b l e   S o r t   A l g o r i t h m\n\n",BWHT);
    printf("\t\t\t\t\t\t\t                 S I M U L A T O R\n");
    printf("\t\t\t\t\t\t\t______________________________________________________\n\n");
    sleep(2);
    system("cls");
    printf("\n\n\n\n");
    printf("%s",reset);
    printf("\t\t\t\t\t\t\t\t       ----- I N S T R U C T I O N S -----\n\n");
    printf("\t\t\t\t\t\t--> T o   i n p u t   n u m b e r s   t h r o u g h   k e y b o a r d  : P r e s s  1.\n");
    printf("\t\t\t\t\t\t--> T o   i n p u t   n u m b e r s   f r o m   F i l e                : P r e s s  2.\n\n");
    printf("\t\t\t\t\t\t    I N P U T  :  ");
}


void display_error_input_num(char *y_n,int *end)
{
     if(*y_n == 'N' || *y_n == 'n')
    {
        *end = 0;
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t\tF i r s t   c r e a t e   t h e   f i l e  \"number.txt\"  i n   \"C_prolect\"   F o l d e r  .\n\n");
        printf("\t\t\t\t\tT e r m i n a t i n g   t h e   P r o g r a m .\n");
        sleep(1);
            Beep(1500,200);
            sleep(1);
        for(int i=0;i<4;i++) // ---> to display the XXXXXX
        {
            if(i==0)
            {
                usleep(200000);
        printf("\t\t\t\t\t\t                        X  ");
             sleep(1);
            }
             else
             {
                 Beep(1500,200);
                 usleep(99550);
             printf("X  ");
            //  Beep(1500,200);
             usleep(700000);
             }
        }
    }
    else
    {
        *end = 0;
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t  I n v a l i d   I n p u t. \n");
        printf("\n\t\t\t\t\t\t\t\t      E x p e c t e d   Y  or  N   F r o m   Y o u . \n");
        sleep(2);
        usleep(500000);
    }
}


void invalid_input(int *end)
{
    *end = 0;
    system("cls");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tI n v a l i d   I n p u t .\n\n");
    printf("\t\t\t\t\t\t\t\t      T e r m i n a t i n g   t h e   P r o g r a m .\n");
    sleep(1);
    Beep(1500,200);
    sleep(1);
    usleep(200000);
    printf("\t\t\t\t\t\t\t\t                 X  ");
    sleep(1);
        for(int i=0;i<4;i++)
        {
            Beep(1500,200);
            usleep(99550);
            printf("X  ");
         //  Beep(1500,200);
        usleep(700000);
        }
}

void swapValue(int *numList, int start, int smallest, int count) 
{
    int temp; 
    system("cls");
    printf("\n"); 
    for(int move=0; move <= smallest-start; move++) //--->to point out the integer uptowhich the spaces are to be created in 1st line of animation()
    {
    system("cls");
    printf("\n\n");
    swapMoveAnimation(numList, start, smallest, move, count); 
    if(smallest==start)
    {
        ;
    }
    else
    sleep(1);
    }
    Beep(200,100); //---->settlement beep

    temp=numList[start]; 
    numList[start]=numList[smallest]; 
    numList[smallest]=temp; 
}


void swapMoveAnimation(int *numList, int start, int smallest, int movPosition, int count) 
{
    if (smallest==start) 
    {
    printf("\n");
    printf("\t\t\t\t\t\t\t");
        for(int ix=0; ix < count; ix++) //2
    {
        if(ix<start) //---> to retain green integers during animation
        {
            printf("%s%03d   %s",BGRN, numList[ix],reset);
        }
        else
        printf("%s%03d   %s",BWHT, numList[ix],reset); //---> Displays all other integers other than those which are one line above and below the integer array
    }
    }
    else{
        printf("\t\t\t\t\t\t\t");
    for(int ix=0; ix < start+movPosition; ix++) //1
    {
    printf("      "); //---> creates spaces for integer that is one line above the integer array
    }

    printf("%s%03d%s\n",BWHT, numList[start],reset); //---> since the entire screen is blank , so integer indexed at start is displayed followed by list of integer array in the next line
    printf("\t\t\t\t\t\t\t");

    for(int ix=0; ix < count; ix++) //2
    {
    if(ix == start || ix == smallest) 
    {
    printf("      "); //---> creates spaces for the integer that is not present in integer array
    }
    else
    {
        if(ix<start) //---> to retain green integers during animation
        {
            printf("%s%03d   %s",BGRN, numList[ix],reset);
        }
        else
        printf("%s%03d   %s",BWHT, numList[ix],reset); //---> Displays all other integers other than those which are one line above and below the integer array
    }
    }
    printf("\n"); //---> starts a new line to isolate red integer from the integer array
    printf("\t\t\t\t\t\t\t");
    for(int ix=0; ix < smallest-movPosition; ix++) // 3
    {
    printf("      "); //---> creates spaces for displaying red integer one line below the integer array
    }
    printf("%s%03d\n\n",BRED, numList[smallest]); 
    }
}


void end_display(int *end,int *count, int numList[])
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\t\t\t");
    if(*end==1)// ---> Success Output
    {
    for(int i=0;i<*count;i++)//--> Final Output
    {
        printf("%s%03d   ",BGRN,numList[i]);
    }
    printf("%s",BGRN);
    printf("\n\n\t\t\t\t\t     E n d   o f   t h e   S i m u l a t i o n  .  C H E E R S !!!");
    printf("%s",reset);
    printf("\n\n\n\t\t\t\t\t%s                      D E S I G N E D   B Y  .:%s",BWHT,reset);
    printf("\n\t\t\t\t\t%s                                                                         .%s",UBLK,reset);
    printf("\n\n\t\t\t\t\t %s1 .  H E M A N T   P A N C H A R I Y A *     -->   0 7 7  B C T   0 2 9     \n",BCYN);
    printf("\n\t\t\t\t\t %s2 .  K R I P E S H   N I H U R E             -->   0 7 7  B C T   0 3 7     \n",CYN);
    printf("\n\t\t\t\t\t 3 .  B I R A J  Kr.  K A R A N J I T         -->   0 7 7  B C T   0 2 0     \n");
    printf("\n\t\t\t\t\t 4 .  B I R A J   A C H A R Y A               -->   0 7 7  B C T   0 1 9     ");
    printf("%s",reset);
    printf("\n\t\t\t\t\t%s                                                                         .%s\n\n\n\n\n\n",UBLK,reset);
    }
    else // ---> Failure Output
    {
        printf("%s\n\n\t\t\t\t\t\t\t\t\t  R e - R u n   T h e   S i m u l a t i o n .%s",BRED,reset);//--> Final Output
    }
}