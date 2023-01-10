#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define VECTOR_STARTING_CAPACITY 8  // number of elements a Subset/Sets is initially allocated
#define VECTOR_CAPACITY_INCREMENT 2 // factor by which a Subset/Sets' capacity is multiplied when it runs out of space

#define MAXIMUM_SUBSET_ELEMENT_LENGTH 31 // maximum length of a Subset string including the null terminator character

#define RESERVED_KEYWORD_AMOUNT 25
#define FUNCTION_AMOUNT 9

typedef enum
{
    SUCCESS,
    INVALID_PROGRAM_ARGUMENTS,
    INVALID_SET_FORMAT,
    MEMORY_ERROR
} SetCalcError;

typedef enum
{
    UNIVERSUM,
    SET,
    RELATION
} SubsetType;

// vector (dynamically sized array) of strings that serves as a Subset, also holds its type
typedef struct
{
    SubsetType type;
    int ID;
    int size;
    int capacity;
    char **elements;
} Subset; // rename to Set maybe ??

// vector of vectors (dynamically sized 2D array), serves as the set of all sets
typedef struct
{
    int size;
    int capacity;
    Subset *subSets;
} SetFamily;

const char *functionList[RESERVED_KEYWORD_AMOUNT] = {"empty", "card", "complement", "union", "intersect", "minus", "subseteq", "subset",
                                                     "equals", "reflexive", "symmetric", "antisymmetric", "transitive", "function",
                                                     "domain", "codomain", "injective", "surjective", "bijective", "closure_ref",
                                                     "closure_sym", "closure_trans", "select", "true", "false"};

Subset *GetSetByID(SetFamily *setFamily, int subsetID)
{
    for (int i = 0; i < setFamily->size; i++)
    {
        if (setFamily->subSets[i].ID == subsetID)
            return &setFamily->subSets[i];
    }
    return NULL;
}

void InitializeSubset(Subset *subset)
{
    subset->elements = (char **)malloc(sizeof(char *) * VECTOR_STARTING_CAPACITY);
    subset->capacity = VECTOR_STARTING_CAPACITY;
    subset->size = 0;
}

int AddStringToSubset(SetFamily *setFamily, int subsetID, char *string)
{
    Subset *subset = GetSetByID(setFamily, subsetID);

    if (subset->size == subset->capacity)
    {
        subset->elements = realloc(subset->elements, sizeof(char *) * subset->capacity * VECTOR_CAPACITY_INCREMENT);
        subset->capacity *= VECTOR_CAPACITY_INCREMENT;
    }

    if (subset->type == UNIVERSUM)
    {
        // initialize the string element on the heap
        subset->elements[subset->size] = (char *)malloc(sizeof(char) * strlen(string) + 1);

        // copy the input string to the heap, otherwise it would get deleted when ParseLine() ends (?)
        strcpy(subset->elements[subset->size], string);
        subset->size++;
        return 0;
    }
    else
    {
        for (int i = 0; i < setFamily->subSets[0].size; i++)
        {
            // if universum contains the string to be added, pass it's pointer to subset
            if (strcmp(setFamily->subSets[0].elements[i], string) == 0)
            {
                subset->elements[subset->size] = setFamily->subSets[0].elements[i];
                subset->size++;
                return 0;
            }
        }
    }
    return 1;
}

void PrintSubset(SetFamily *setFamily, int subsetID)
{
    Subset *subset = GetSetByID(setFamily, subsetID);

    if (subset->type == UNIVERSUM)
        printf("U");
    else if (subset->type == SET)
        printf("S");
    else if (subset->type == RELATION)
        printf("R");

    if (subset->type == RELATION)
    {
        for (int i = 0; i < subset->size; i += 2)
        {
            printf(" (%s %s)", subset->elements[i], subset->elements[i + 1]);
        }
    }
    else
    {
        for (int i = 0; i < subset->size; i++)
        {
            printf(" %s", subset->elements[i]);
        }
    }

    printf("\n");
}

void PrintSubsetElements(Subset *subset)
{
    for (int i = 0; i < subset->size; i++)
    {
        printf(" %s", subset->elements[i]);
    }
}

void DestructSubset(Subset *subset)
{
    for (int i = 0; i < subset->size; i++)
    {
        if (subset->type == UNIVERSUM)
            free(subset->elements[i]);
        subset->elements[i] = NULL;
    }

    free(subset->elements);
    subset->elements = NULL;
    subset->capacity = 0;
    subset->size = 0;
}

SetFamily *ConstructSetFamily()
{
    SetFamily *setFamily = (SetFamily *)malloc(sizeof(SetFamily));

    if (setFamily != NULL)
    {
        setFamily->subSets = (Subset *)malloc(sizeof(Subset) * VECTOR_STARTING_CAPACITY);
        setFamily->capacity = VECTOR_STARTING_CAPACITY;
        setFamily->size = 0;
    }

    return setFamily;
}

// add a new empty subset to SetFamily
void AppendSetFamily(SetFamily *setFamily, SubsetType subsetType, int subsetID)
{
    if (setFamily->size == setFamily->capacity)
    {
        setFamily->subSets = (Subset *)realloc(setFamily->subSets, sizeof(Subset) * setFamily->size * VECTOR_CAPACITY_INCREMENT);
        setFamily->capacity *= VECTOR_CAPACITY_INCREMENT;
    }

    InitializeSubset(&(setFamily->subSets[setFamily->size]));
    setFamily->subSets[setFamily->size].type = subsetType;
    setFamily->subSets[setFamily->size].ID = subsetID;
    setFamily->size++;
}

// recursively free all sets and their elements
void DestroySetFamily(SetFamily *setFamily)
{
    for (int i = 0; i < setFamily->size; i++)
        DestructSubset(&(setFamily->subSets[i]));

    free(setFamily->subSets);
    setFamily->subSets = NULL;

    free(setFamily);
    setFamily = NULL;
}

int ValidateString(char *string)
{
    for (int i = 0; i < RESERVED_KEYWORD_AMOUNT; i++)
    {
        if (strstr(string, functionList[i]))
            return 1;
    }
    return 0;
}

int ParseLine(SetFamily *setFamily, int subsetID, FILE *file)
{
    // TODO this sucks real bad

    char character;
    char string[MAXIMUM_SUBSET_ELEMENT_LENGTH] = {'\0'};
    int charCounter = 0;
    int stringCounter = 0;

    if ((character = fgetc(file)) == '\n')
        return SUCCESS;
    else if (character != ' ')
        return INVALID_SET_FORMAT;

    while ((character = fgetc(file)) != '\n')
    {
        if (charCounter > 30)
            return INVALID_SET_FORMAT;

        if (isalpha(character))
        {
            string[charCounter] = character;
            charCounter++;
        }
        else if (character == ' ')
        {
            if (string[0] != '\0' && !ValidateString(string))
            {
                string[charCounter] = '\0';
                AddStringToSubset(setFamily, subsetID, string);
                string[0] = '\0';
                charCounter = 0;
                stringCounter++;
            }
            else
                return INVALID_SET_FORMAT;
        }
        else
            return INVALID_SET_FORMAT;
    }
    if (string[0] != '\0' && !ValidateString(string))
    {
        if (charCounter > 30)
            return INVALID_SET_FORMAT;

        string[charCounter] = '\0';
        AddStringToSubset(setFamily, subsetID, string);
        return SUCCESS;
    }
    return INVALID_SET_FORMAT;
}

int ParseLineRelation(SetFamily *setFamily, int subsetID, FILE *file)
{
    // TODO this sucks REAL bad but it works!

    char character;
    char string[MAXIMUM_SUBSET_ELEMENT_LENGTH] = {'\0'};
    int charCounter = 0;
    int stringCounter = 0;
    int parentheses = 0;

    if ((character = fgetc(file)) == '\n')
        return SUCCESS;
    else if (character != ' ')
        return INVALID_SET_FORMAT;

    while ((character = fgetc(file)) != '\n')
    {
        if (charCounter > 30 || parentheses > 1 || parentheses < 0)
            return INVALID_SET_FORMAT;

        if (isalpha(character))
        {
            string[charCounter] = character;
            charCounter++;
        }
        else if (character == ' ')
        {
            if (string[0] != '\0' && !ValidateString(string) && parentheses)
            {
                string[charCounter] = '\0';
                AddStringToSubset(setFamily, subsetID, string);
                string[0] = '\0';
                charCounter = 0;
                stringCounter++;
            }
            else if (parentheses)
                return INVALID_SET_FORMAT;
        }
        else if (character == '(')
        {
            if (stringCounter == 0)
                parentheses++;
            else
                return INVALID_SET_FORMAT;
        }
        else if (character == ')')
        {
            if (string[0] != '\0' && !ValidateString(string) && parentheses)
            {
                string[charCounter] = '\0';
                AddStringToSubset(setFamily, subsetID, string);
                string[0] = '\0';
                charCounter = 0;
                stringCounter++;
            }
            if (stringCounter == 2)
            {
                parentheses--;
                stringCounter = 0;
            }
            else
                return INVALID_SET_FORMAT;
        }
        else
            return INVALID_SET_FORMAT;
    }
    if (!parentheses)
        return SUCCESS;
    else
        return INVALID_SET_FORMAT;
}

long ParseNumber(FILE *file)
{
    char number[5] = {'\0'};
    char character;
    int charCounter = 0;

    while ((character = fgetc(file)) != ' ' && character != '\n')
    {
        if (charCounter > 4)
            return -1;

        if (isdigit(character))
        {
            number[charCounter] = character;
            charCounter++;
        }
        else
            return -1;
    }

    if (number[0] != '\0')
        return strtol(number, NULL, 10);
    else
        return -1;
}

int ParseCommand(FILE *file)
{
    char character;
    char string[MAXIMUM_SUBSET_ELEMENT_LENGTH] = {'\0'};
    int charCounter = 0;

    if ((character = fgetc(file)) != ' ')
        return INVALID_SET_FORMAT;

    while ((character = fgetc(file)) != ' ')
    {
        if (charCounter > 30)
            return INVALID_SET_FORMAT;

        if (isalpha(character))
        {
            string[charCounter] = character;
            charCounter++;
        }
        else
            return -1;
    }
    string[charCounter] = '\0';

    for (int i = 0; i < FUNCTION_AMOUNT; i++)
    {
        if (strcmp(string, functionList[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int LogErrorAndTerminate(SetCalcError error, SetFamily *setFamily, FILE *file)
{
    switch (error)
    {
    case SUCCESS:
        DestroySetFamily(setFamily);
        fclose(file);
        return SUCCESS;

    case INVALID_PROGRAM_ARGUMENTS:
        DestroySetFamily(setFamily);
        fclose(file);
        fprintf(stderr, "ERROR: Invalid program argument format\n");
        return INVALID_PROGRAM_ARGUMENTS;

    case INVALID_SET_FORMAT:
        DestroySetFamily(setFamily);
        fclose(file);
        fprintf(stderr, "ERROR: Invalid set input format\n"); // ??
        return INVALID_SET_FORMAT;

    case MEMORY_ERROR:
        DestroySetFamily(setFamily);
        fclose(file);
        fprintf(stderr, "ERROR: Memory error\n");
        return MEMORY_ERROR;
    }
    return SUCCESS;
}

// TODO: functions functions functions functions functions functions functions functions functions functions functions functions
// functions functions functions functions functions functions functions functions functions functions functions functions

int SetEmpty(SetFamily *setFamily, FILE *file)
{
    long subsetID = ParseNumber(file);

    if (subsetID == -1)
        return -1;

    Subset *subset = GetSetByID(setFamily, subsetID);

    if (subset->type != SET)
        return -1;

    if (subset->size == 0)
    {
        printf("true\n");
    }
    else
        printf("false\n");

    return 0;
}

int SetCard(SetFamily *setFamily, FILE *file)
{
    long subsetID = ParseNumber(file);

    if (subsetID == -1)
        return -1;

    Subset *subset = GetSetByID(setFamily, subsetID);

    if (subset->type != SET)
        return -1;

    printf("%d\n", subset->size);

    return 0;
}

int SetComplement(SetFamily *setFamily, FILE *file)
{
    long subsetID = ParseNumber(file);

    if (subsetID == -1)
        return -1;

    Subset *subset = GetSetByID(setFamily, subsetID);

    if (subset->type != SET)
        return -1;

    printf("S");

    int found = 0;
    for (int i = 0; i < setFamily->subSets[0].size; i++)
    {
        found = 0;

        for (int j = 0; j < subset->size; j++)
        {
            if (setFamily->subSets[0].elements[i] == subset->elements[j])
                found = 1;
        }
        if (!found)
            printf(" %s", setFamily->subSets[0].elements[i]);
    }
    printf("\n");

    return 0;
}

int SetUnion(SetFamily *setFamily, FILE *file)
{
    long subsetAID = ParseNumber(file);
    long subsetBID = ParseNumber(file);

    if (subsetAID == -1 || subsetBID == -1)
        return -1;

    Subset *subsetA = GetSetByID(setFamily, subsetAID);
    Subset *subsetB = GetSetByID(setFamily, subsetBID);

    if (subsetA->type != SET || subsetB->type != SET)
        return -1;

    printf("S");
    PrintSubsetElements(subsetA);

    int found = 0;
    for (int i = 0; i < subsetB->size; i++)
    {
        found = 0;

        for (int j = 0; j < subsetA->size; j++)
        {
            if (subsetB->elements[i] == subsetA->elements[j])
                found = 1;
        }
        if (!found)
            printf(" %s", subsetB->elements[i]);
    }
    printf("\n");

    return 0;
}

int SetIntersect(SetFamily *setFamily, FILE *file)
{
    long subsetAID = ParseNumber(file);
    long subsetBID = ParseNumber(file);

    if (subsetAID == -1 || subsetBID == -1)
        return -1;

    Subset *subsetA = GetSetByID(setFamily, subsetAID);
    Subset *subsetB = GetSetByID(setFamily, subsetBID);

    if (subsetA->type != SET || subsetB->type != SET)
        return -1;

    printf("S");

    int found = 0;
    for (int i = 0; i < subsetA->size; i++)
    {
        found = 0;

        for (int j = 0; j < subsetB->size; j++)
        {
            if (subsetA->elements[i] == subsetB->elements[j])
                found = 1;
        }
        if (found)
            printf(" %s", subsetA->elements[i]);
    }
    printf("\n");

    return 0;
}

int SetMinus(SetFamily *setFamily, FILE *file)
{
    long subsetAID = ParseNumber(file);
    long subsetBID = ParseNumber(file);

    if (subsetAID == -1 || subsetBID == -1)
        return -1;

    Subset *subsetA = GetSetByID(setFamily, subsetAID);
    Subset *subsetB = GetSetByID(setFamily, subsetBID);

    if (subsetA->type != SET || subsetB->type != SET)
        return -1;

    printf("S");

    int found = 0;
    for (int i = 0; i < subsetA->size; i++)
    {
        found = 0;

        for (int j = 0; j < subsetB->size; j++)
        {
            if (subsetA->elements[i] == subsetB->elements[j])
                found = 1;
        }
        if (!found)
            printf(" %s", subsetA->elements[i]);
    }
    printf("\n");

    return 0;
}

int SetSubsetEq(SetFamily *setFamily, FILE *file)
{
    long subsetAID = ParseNumber(file);
    long subsetBID = ParseNumber(file);

    if (subsetAID == -1 || subsetBID == -1)
        return -1;

    Subset *subsetA = GetSetByID(setFamily, subsetAID);
    Subset *subsetB = GetSetByID(setFamily, subsetBID);

    if (subsetA->type != SET || subsetB->type != SET)
        return -1;

    int found = 0;
    for (int i = 0; i < subsetA->size; i++)
    {
        found = 0;

        for (int j = 0; j < subsetB->size; j++)
        {
            if (subsetA->elements[i] == subsetB->elements[j])
                found = 1;
        }
        if (!found)
        {
            printf("false\n");
            return 0;
        }
    }
    printf("true\n");

    return 0;
}

int SetSubset(SetFamily *setFamily, FILE *file)
{
    long subsetAID = ParseNumber(file);
    long subsetBID = ParseNumber(file);

    if (subsetAID == -1 || subsetBID == -1)
        return -1;

    Subset *subsetA = GetSetByID(setFamily, subsetAID);
    Subset *subsetB = GetSetByID(setFamily, subsetBID);

    if (subsetA->type != SET || subsetB->type != SET)
        return -1;

    if (subsetA->size >= subsetB->size)
    {
        printf("false\n");
        return 0;
    }
    else
    {
        int found = 0;
        for (int i = 0; i < subsetA->size; i++)
        {
            found = 0;

            for (int j = 0; j < subsetB->size; j++)
            {
                if (subsetA->elements[i] == subsetB->elements[j])
                    found = 1;
            }
            if (!found)
            {
                printf("false\n");
                return 0;
            }
        }
        printf("true\n");
    }

    return 0;
}

int SetEquals(SetFamily *setFamily, FILE *file)
{
    long subsetAID = ParseNumber(file);
    long subsetBID = ParseNumber(file);

    if (subsetAID == -1 || subsetBID == -1)
        return -1;
    Subset *subsetA = GetSetByID(setFamily, subsetAID);
    Subset *subsetB = GetSetByID(setFamily, subsetBID);

    if (subsetA->type != SET || subsetB->type != SET)
        return -1;

    if (subsetA->size != subsetB->size)
    {
        printf("false\n");
        return 0;
    }
    else
    {
        int found = 0;
        for (int i = 0; i < subsetA->size; i++)
        {
            found = 0;

            for (int j = 0; j < subsetB->size; j++)
            {
                if (subsetA->elements[i] == subsetB->elements[j])
                    found = 1;
            }
            if (!found)
            {
                printf("false\n");
                return 0;
            }
        }
        printf("true\n");
    }

    return 0;
}

void SetReflexive(SetFamily *setFamily, int subsetID)
{
    Subset *subset = GetSetByID(setFamily, subsetID);

    bool found = false;
    bool equals = false;
    for (int i = 0; i < subset->size; i++)
    {
        for (int j = 0; j < subset->size; j++)
        {
            if (subset->elements[i] == subset->elements[j])
                found = true;
        }
        if (subset->elements[i] == subset->elements[i+1] && found)
            equals = true;
        i++;
    }
    if (!equals)
    {
        printf("false\n");
        return;
    }
    printf("true\n");
}

void SetSymmetric(SetFamily *setFamily, int subsetID)
{
    Subset *subset = GetSetByID(setFamily, subsetID);

    bool found = false;
    bool opposite = false;
    for (int i = 0; i < subset->size; i+=2)
    {
        for (int j = 0; j < subset->size; j+=2)
        {
            for (int k = 0; k < subset->size; k++)
            {
                if (subset->elements[j] == subset->elements[k] || subset->elements[j+1] == subset->elements[k])
                    found = true;
                if (!found)
                {
                    printf("false\n");
                    return;
                }
            }
            if (subset->elements[i] == subset->elements[j+1] && subset->elements[i+1] == subset->elements[j] && found)
                opposite = true;
        }
    }
    if (!opposite)
    {
        printf("false\n");
        return;
    }
    printf("true\n");
}

// TODO: antisymmetric function

void SetTransitive(SetFamily *setFamily, int subsetID)
{
    Subset *subset = GetSetByID(setFamily, subsetID);

    int count = 0;
    for (int i = 1; i < subset->size; i+=2)
    {
        for (int j = 0; j < subset->size; i+=2)
        {
            if (subset->elements[i] == subset->elements[j])
                {
                    for (int k = 0; k < subset->size; k+=2)
                        {
                            if (subset->elements[k] == subset->elements[j] && subset->elements[j+1] == subset->elements[i])
                                count++;
                        }
                }
        }
    }
    if (count != subset->size / 2)
    {
        printf("false\n");
        return;
    }
    printf("true\n");
}

void SetFunction(SetFamily *SetFamily, int subsetID)
{
    Subset *subset = GetSetByID(SetFamily, subsetID);

    int count = 0;
    for (int i = 0; i < subset->size; i+=2)
    {
        if (subset->elements[i] == subset->elements[i+2])
            count++;
    }
    for (int j = 1; j < subset->size; j+=2)
    {
        if (subset->elements[j] == subset->elements[j+2])
            count++;
    }
    if (count != 0)
    {
        printf("false\n");
        return;
    }
    printf("true\n");
}

void SetDomain(SetFamily *SetFamily, int subsetID)
{
    Subset *subset = GetSetByID(SetFamily, subsetID);

    for (int i = 0; i < subset->size; i+=2)
    {
        for (int j = 0; j < i; j+=2)
        {
            if (subset->elements[i] == subset->elements[j])
                continue;
        }
        printf(" %s", subset->elements[i]);
    }
}

void SetCodomain(SetFamily *SetFamily, int subsetID)
{
    Subset *subset = GetSetByID(SetFamily, subsetID);

    for (int i = 1; i < subset->size; i+=2)
    {
        for (int j = 1; j < i; j+=2)
        {
            if (subset->elements[i] == subset->elements[j])
                continue;
        }
        printf(" %s", subset->elements[i]);
    }
}

int main(int argc, char **argv)
{
    // TODO: validate program arguments and file

    FILE *file;
    file = fopen(argv[1], "r");

    char ch = (char)argc;

    SetFamily *setFamily = ConstructSetFamily();

    if (setFamily == NULL)
        return MEMORY_ERROR;

    int line = 1;

    int (*function[FUNCTION_AMOUNT])(SetFamily * setFamily, FILE * file) = {SetEmpty, SetCard, SetComplement, SetUnion, SetIntersect,
                                                                            SetMinus, SetSubsetEq, SetSubset, SetEquals};

    while ((ch = fgetc(file)) != EOF)
    {
        switch (ch)
        {
        case 'U':
            if (line != 1) // check whether UNIVERSUM is on the first line
                return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);

            AppendSetFamily(setFamily, UNIVERSUM, line);
            if (ParseLine(setFamily, line, file))
                return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);
            PrintSubset(setFamily, line);
            line++;
            break;

        case 'S':
            AppendSetFamily(setFamily, SET, line);
            if (ParseLine(setFamily, line, file))
                return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);
            PrintSubset(setFamily, line);
            line++;
            break;

        case 'R':
            AppendSetFamily(setFamily, RELATION, line);
            if (ParseLineRelation(setFamily, line, file) || setFamily->subSets[setFamily->size - 1].size % 2 != 0)
                return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);
            PrintSubset(setFamily, line);
            line++;
            break;

        case 'C': ;
            int num = ParseCommand(file);
            if (num == -1)
                return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);
            if ((*function[num])(setFamily, file) == -1)
                return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);
            break;

        default:
            return LogErrorAndTerminate(INVALID_SET_FORMAT, setFamily, file);
            break;
        }
    }

    return LogErrorAndTerminate(SUCCESS, setFamily, file);
}