#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


const int MAXCOMMANDS = 6; //set the amount of commands here 


int *cmdparser(int argcnt, char *argv[], char *commands[]);
void cmdsingler(char *command, char *startaddr);
void cmdlonger(char *command, char *startaddr);
int singleOrLong(char *command); //ik i give my commands very desriptive names 
void strncpyn(char *string1, char *string2, int start, int end); //copies from start to end
void strlower(char *input);


int main(int argc, char *argv[])
{
    /*
        set commands here 
        firstly write the "long" version of the command and then seperated by 
        a space, a comma and another space the "short" version of the command
        if there does not exist a "short" version, simply put !
     */

    char *commands[MAXCOMMANDS] = 
    {
        "help , h", //0
        "hello , !", //1
        "cmd1 , c", //2
        "test , t", //3
        "--help , !",//4
        "wow , w" //5
    };

    for(int i = 0; i < argc; i++)
    {
        if(strlen(argv[i]) > 100)
        {
            printf("***************\nargument at %d too long!!\nMAXLEN is 100\n***************\n", i);
            return 1;
        }
    }

    int *list = malloc(100 * sizeof(int));
    list = cmdparser(argc, argv, commands);

    
    printf("DEBUG: OUTPUTTED ARRAY:\n");
    for(int i = 1; i < 10; i++) //i starts at 1 because argv at 0 is the executable 
    {
        printf("%d\n", list[i]);
    }

    free(list);
    return 0;
}

int singleOrLong(char *command)
{
    if(command[0] != '-')
    {
        return -1; //invalid
    }
    if(command[1] != '-')
    {
        return 0; //single
    }
    return 1; //long
}

void cmdsingler(char *command, char *startaddr)
{
    char *pCmd = startaddr;
    int i = 0;
    while(command[i] != ' ')
    {
        i++;
    }
    //at i is the space, meaning at i + 3 is the single character
    *pCmd = command[i + 3];
}

void cmdlonger(char *command, char *startaddr)
{
    char *pCmd = startaddr;
    int i = 0;
    while(command[i] != ' ')
    {
        i++;
    }
    strncpy(pCmd, command, i);
    pCmd[i] = '\0';
}

void strncpyn(char *string1, char *string2, int start, int end)
{
    char *s1P = string1;
    char *s2P = string2;
    s2P += start;
    for(int i = 0; i < (end - 1); i++)
    {
        *s1P = *s2P;
        s1P++;
        s2P++;
    }
}



int *cmdparser(int argcnt, char *argv[], char **commands)
{
    //int cmdlen = (int) sizeof(commands) / 104;
    //printf("cmdlen: %d", cmdlen);
    int cmdlen =  MAXCOMMANDS;
    const int MAXARGV = 100;
    
    char *buffer = malloc(104);

    int *operators = malloc(MAXARGV * sizeof(int));

    for(int i = 0; i < MAXARGV; i++)
    {
        operators[i] = -1;
    }

    for(int i = 1; i < argcnt; i++) //starts at 1 because argv[0] is the executable
    {
        int mode = singleOrLong(argv[i]);
        
        if(mode == -1)
        {
            operators[i] = -10;
            continue;
        } 
        if(mode == 0) //single mode
        {
            bool succes = false;

            if(strlen(argv[i]) > 2) 
            {
                operators[i] = -2; //-2 = too many args for "-"
                continue;
            }
            else
            {
                for(int j = 0; j < cmdlen; j++) 
                {
                    cmdsingler(commands[j], &buffer[0]);
                    if(argv[i][1] == buffer[0] && argv[i][1] != '!')
                    {
                        operators[i] = j;
                        succes = true;

                    }
                }
            }
            if(!succes)
            {
                printf("No valid command found at %d\n", i);
            }

            
        }
        else //long mode
        {
            //remove the --
            char tmp[100];
            char *raw = malloc(100);
            strcpy(raw, argv[i]);
            strncpyn(tmp, argv[i], 2, strlen(argv[i]));

            strlower(tmp);

            bool succes = false;

            for(int j = 0; j < cmdlen; j++)
            {
                cmdlonger(commands[j], &buffer[0]);
                if(strcmp(tmp, buffer) == 0)
                {
                    operators[i] = j;
                    succes = true;
                }
            }
            if(!succes)
            {
                printf("No valid command found at %d!\n", i);
            }
        }
    }

    free(buffer);
    return operators;   
}

void strlower(char *input)
{
    for(int i = 0; i < strlen(input); i++)
    {
        input[i] = tolower((unsigned char) input[i]);
    }
}