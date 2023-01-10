#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int small_letters(char *buffer) //function for searching small letters 
{
  int a = 0; //temporary variable
  for(int i = 0 ; buffer[i] != '\0'; i++) //cycle for (runs until the end of the file) (same in other functions)
  {
    if(buffer[i] >= 'a' && buffer[i] <= 'z') //comparison from ASCI table
    {
      a++; 
    } 
  }
  if(a >= 1) //if the cycle find some small letter it sets return to 1
    return 1;
  else
    return 0; 
}   // other functions are similar

int large_letters(char *buffer)
{
  int a = 0;
  for(int i = 0 ; buffer[i] != '\0'; i++) 
  {
    if(buffer[i] >= 'A' && buffer[i] <= 'Z')
    {
      a++;
    }
  }
  if(a >= 1)
      return 1;
    else
      return 0;
}

int number(char *buffer)
{
  int a = 0;
  for(int i = 0 ; buffer[i] != '\0'; i++) 
  {
    if(buffer[i] >= '0' && buffer[i] <= '9')
    {
      a++;
    }
  }
  if(a >= 1)
      return 1;
    else
      return 0;
}

int special(char *buffer)
{
  int a = 0;
  for(int i = 0 ; buffer[i] != '\0'; i++)
  {
    if(((buffer[i] >= 32) && (buffer[i] <= 47)) || ((buffer[i] >= 58) && (buffer[i] <= 64)) || ((buffer[i] >= 91) && (buffer[i] <= 96)) || ((buffer[i] >= 122) && (buffer[i] <= 126))) 
    {
      a++;
    } //this if determines if there is a special character in the password
  }
  if(a >= 1)
      return 1;
    else
      return 0;
}

int cmp_two_strings(char *buffer, int X)//this function compare 2 strings (one of size param) and another (buffer-entry string from stdin)
{
  char helpbuff[100] = {0};
  int a = 0;
  int b = 0;
  for(int j = 0; buffer[j] != '\0'; j++) 
  {
    b = 0;
    for (int i = 0; i < X; i++)//this cyclus adding in substring (helpbuff) string of size param
    {
      helpbuff[i] = buffer[i+j];
    } 
    for(int k = 0; buffer[k] != '\0';k++)
    {
      a = 0;
      for(int l = 0; helpbuff[l] != '\0'; l++)
      {
        if (helpbuff[l] == buffer[l+k]) //compare if there is not substring (helpbuff) in string (buffer)
        {
          a++; //if yes ads in a 1
        }      
      }
      if(a == X)
        b++; 
    }
    if(b >= 2)
      return 0;
  }
  return 1;
}

int rule_one(char *buffer) //function for first rule, calling 2 diferent functions
{
  if((small_letters(buffer) == 1 ) && (large_letters(buffer) == 1))
    return 1;
  else
    return 0;
}

int rule_two(char *buffer, int X) //function for second rule, calling 4 diferent functions 
{
  switch(X) //swtich case for X groups from rule 2
  {
    case 1:
      if(small_letters(buffer) == 1)
        return 1;
      else 
        return 0;
      break;

    case 2:
      if((small_letters(buffer) == 1) && (large_letters(buffer) == 1))
        return 1;
      else
        return 0;
      break;

    case 3:
      if((small_letters(buffer) == 1) && (large_letters(buffer) == 1) && (number(buffer) == 1))
         return 1;
      else
        return 0;
      break;

    case 4:
      if((small_letters(buffer) == 1) && (large_letters(buffer) == 1) && (number(buffer) == 1) && (special(buffer) == 1))
         return 1;
      else
        return 0;
      break;

    default :
      return 2;
  }
}

int rule_three(char *buffer, int X) 
{
  int b = X; //only for for cycle 
  int a = 0;
  int j = 0;
  for(int i = 0 ;buffer[i] != '\0';i++)
  {
    for(j = i; j != b + i; j++) //this 2 for cycles compare if the next character does not equel previous character 
    {
      if (buffer[i] == buffer[j])
      {
        a++;
      }
    }
    if(X == a)
      return 0;
    a = 0;
  }
  if (rule_two(buffer,X) == 1)
    return 1;
  else
    return 0;
}

int rule_four(char *buffer, int X)
{
  if((cmp_two_strings(buffer,X) == 1) && (rule_three(buffer,X) == 1))
    return 1;
  else
    return 0;
}

int str_len(char *buffer)
{
  int a = 0; //temporary variable
  for(int i = 0 ; buffer[i] != '\0'; i++) 
  {
      a++;   
  }
  if(a != 0 && a != 1)
    a -= 2; // -2 because i am adding a space and a line break
  if(a >= 101)
  {
    fprintf(stderr,"Password lenght = %d",a);
    fprintf(stderr,"Too long entry password");
    return 1;
  }
  return a;
}

int str_len_help(char *helpbuff)
{
  int a = 0; //temporary variable
  for(int i = 0 ; helpbuff[i] != '\0'; i++) 
  {
      a++;   
  }
  if(a != 0 && a != 1)
    a -= 2; // -2 because i am adding a space and a line break
  return a;
}

char NCHARS(char *buffer, char *helpbuff)
{
  for(int i = 0; buffer[i] != '\0';i++)
    {
      for(int j = 0; buffer[j] != '\0'; j++)
      {
        if(buffer[j] != helpbuff[i])
        { 
          helpbuff[i] = buffer[j];
          i++; 
        }  
      }//if users enters stats this function compares 2 strings and adds another character
    }
  return *helpbuff;
}

int stats(char *argv[])
{
    int a = 0;
    char *helpstr = argv[3];
    char string[] = "--stats";
    for(int i = 0 ; helpstr[i] != '\0'; i++)
    {
      if (helpstr[i] != string[i])
      a++;   
    } 
    if(a >= 1)
    {      
      fprintf(stderr,"Invalid argv[3] - please write --stats\n");
      return 0;
    }
    else
      return 1;    
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    fprintf(stderr,"ERROR in argc - not enough variables\n"); //if the user enters only 1 variable 
    return 1;  
  }
  if(argc > 4) //entry treatment 
  {
    fprintf(stderr,"ERROR in argc - to many variables\n"); //if the user enters more then 3 variables 
    return 1;  
  }
  int y = 0; //temporary variable for entry treatments 
  if(argc == 4) //if users enters --stats
  { 
      y = stats(argv); //using temporary variable y
      if(y == 0)
        return 1;
  }
  int index = 0; //temporary variable for stats
  float index1 = 0; //temporary variable for stats
  float len_buffer = 0; //temporary variable for stats
  int nchar = 0; //temporarz variable for stats
  char lenght[100]; //temporary variable for stats 
  char helpbuff[100]; //temporary variable for stats
  int a = atoi(argv[1]); //saving first argument
  int X = atoi(argv[2]); //saving second argument
  if(a <= 0 || a >= 5) //entry treatment
  {
    fprintf(stderr,"Invalid argv[0]");
    return 1;
  }
  if(X <= 0 || X >= 1500000) //entry treatment 
  {
    fprintf(stderr,"Invalid argv[1]");
    return 1;
  } 
  char buffer[100]; //variable for reading from stdin
  while(fgets(buffer, 100, stdin)!=NULL) //loading from stdin to variable named buffer ONE LINE in one CYCLE
  {
    switch(a) //switch case for rules and asking functions
    {
      case 1:
        if (rule_one(buffer) == 1)
        {
          fprintf(stdout,"%s",buffer); //writing on stdout 
        }  
          break;

      case 2:
        if(rule_two(buffer,X) == 1)
        {
          if(rule_two(buffer,X) == 2)
            fprintf(stderr,"Error, PARAM < entry variable\n");

          fprintf(stdout,"%s",buffer);
        }
          break;
       
      case 3:
        if(rule_three(buffer,X) == 1)
        {
          fprintf(stdout,"%s",buffer);
        }
          break; 
       
      case 4:
        if(rule_four(buffer,X) == 1)
        {
          fprintf(stdout,"%s",buffer);
        }
          break;

      default :
        fprintf(stderr,"Invalid data - in argv[1] is more then 1-4\n"); //if the user enters more then 4 rules
        return 0;

    } 
    if(y == 1) //using temporary variable
    { 
      lenght[index] = str_len(buffer);//lenght of buffer
      len_buffer += str_len(buffer); 
      *helpbuff = NCHARS(buffer,helpbuff);
    } //using stats 
    index++;
    
  }
  if(y == 1) //if the users enters --stats
  {
    nchar = str_len(helpbuff);
    index1 = index; //int to float
    float how_long_is_it = len_buffer / index1; //for ,,prumerna delka,, 
    int variable = 101; //if i know that password can be < 101 
    for(int i = 0 ; lenght[i] != '\0'; i++) 
    {
      if(variable > lenght[i])
        variable = lenght[i];
    }
    fprintf(stdout,"Statistika:\n");
    fprintf(stdout,"Ruznych znaku: %d\n", nchar);
    fprintf(stdout,"Minimalni delka: %d\n",variable);
    fprintf(stdout,"Prumerna delka: %.1f\n",how_long_is_it);
  }
 return 0;
}