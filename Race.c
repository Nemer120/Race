#include <stdio.h>
#include <stdlib.h>

typedef struct contestant_t Contestant;
struct contestant_t
{
    long Id;
    char First_Name[30];
    char Last_Name[30];
    double duration;
    Contestant * next;
}*race_res;
/* lines 12-21 are all the functions i have used*/
void GetNewData();
void InsertNewContestant (Contestant * tmp);
void PrintRace();
Contestant* getContestantbyID(long id);
void DeleteContestant(long id);
void printcontafter(long id);
int getContestantRank(long id);
void freeRace (Contestant* race);
int main()
{
    int number,ConID,counter=0,Number1=1,place,check=0;
    Contestant *getID;
    printf("Enter the number of contestants in the race:\n");
    check=scanf("%d",&number);
    if(check<1) /*if user inputs something other than a number*/
    {
        printf("Input Error\n");
        exit(1);
    }
    if(number<1) /* if the number of contestants is 0 or less no need to activate our functions because there is no one in the race*/
    {
        printf("Input Error\n");
        exit(1);
    }
    while(counter!=number) /* keep getting data about the contestants*/
    {
        GetNewData();
        counter++;
    }
    PrintRace();
    printf("Enter an ID of a contestant\n");
    scanf("%d",&ConID);
    place=getContestantRank(ConID); /*saving the place of the contestant*/
    getID=getContestantbyID(ConID); /* getting the information of the contestant by his ID*/

    if(getID==NULL||place==-1) /* if the contestant by his ID is not found we print the contestant in the first place*/
    {
        printf("No Such Contestant\nThere is no such contestant in the race\n");
        printf("Printing the contestant after deleting (section 8):\n");
        printf("%ld %s %s finished at the time of %.2lf and finish in place: %d\n",race_res->Id,race_res->First_Name,race_res->Last_Name,race_res->duration,Number1);
        printf("Printing the Race (section 9):\n");
        PrintRace();
        freeRace (race_res);
        exit(0);
    }
    if(getID->next==NULL) /*if we delete a contestant and there is no contestant after him then we print the contestant in place 1*/
    {
        printf("%ld %s %s finished at the time of %.2lf and finish in place: %d\n",getID->Id,getID->First_Name,getID->Last_Name,getID->duration,place);
        DeleteContestant(ConID);
        printf("Contestant %d was deleted\n",ConID);
        printf("Printing the contestant after deleting (section 8):\n");
        if(race_res!=NULL)
        {
            printf("%ld %s %s finished at the time of %.2lf and finish in place: %d\n",race_res->Id,race_res->First_Name,race_res->Last_Name,race_res->duration,Number1);
            printf("Printing the Race (section 9):\n");
            PrintRace();
            freeRace (race_res);
            exit(0);
        }
        else /* in some cases we will have 1 contestant but after deleting him we will have an empty struct node so we print there is no contestants*/
        {
            printf("No Such Contestant\nThere is no such contestant in the race\n");
            printf("Printing the Race (section 9):\n");
            printf("No Such Contestant\nThere is no such contestant in the race\n");
            exit(0);
        }
    }
    while(getID!=NULL) /*normal check, no cases involved*/
    {
        if(getID->Id==ConID)
        {
            printf("%ld %s %s finished at the time of %.2lf and finish in place: %d\n",getID->Id,getID->First_Name,getID->Last_Name,getID->duration,place);
            printf("Contestant %d was deleted\n",ConID);
            printf("Printing the contestant after deleting (section 8):\n");
            printcontafter(ConID);
            DeleteContestant(ConID);
            printf("Printing the Race (section 9):\n");
            PrintRace();
            freeRace (race_res);
            exit(0);
        }
        getID=getID->next;
    }
}
void GetNewData() /* function to get information from the user*/
{
    Contestant *newContestant;
    int check=0;
    newContestant=(Contestant*)malloc(sizeof(Contestant));
    if(newContestant==NULL)
    {
        printf("Cannot allocate memory\n");
        exit(1);
    }
    printf("Enter the contestant's first name:\n");
    scanf("%s",newContestant->First_Name); /*scanning*/
    printf("Enter the contestant's last name:\n");
    scanf("%s",newContestant->Last_Name);
    printf("Enter the contestant's ID:\n");
    check=scanf("%ld",&newContestant->Id);
    if(check<1) /* checking if the input is valid*/
    {
        printf("Input Error\n");
        exit(1);
    }
    printf("Enter the contestant's time in the race:\n");
    check=scanf("%lf",&newContestant->duration);
    if(check<1)
    {
        printf("Input Error\n");
        exit(1);
    }
    InsertNewContestant (newContestant);
}
void InsertNewContestant (Contestant * tmp) /* function to insert new contestant and sort them from lowest duration to highest*/
{
    Contestant *newNode, *currentNode;
    if((newNode=(Contestant *)malloc(sizeof(Contestant)))==NULL) /*allocating memory*/
    {
        printf("Allocation failed\n");
        exit(1);
    }
    newNode=tmp;
    newNode->duration=tmp->duration;

    if(race_res==NULL || race_res->duration > tmp->duration)
    {

        newNode->next=race_res;
        race_res=newNode;
        return;
    }
    else
    {
        currentNode=race_res;
        while(currentNode->next!=NULL && currentNode->next->duration < tmp->duration)
        {
            currentNode=currentNode->next;
        }
        newNode->next=currentNode->next;
        currentNode->next=newNode;
        return;
    }
}
void PrintRace() /*function to print all the contestant,the race*/
{
    Contestant *temp=race_res;
    while(temp!=NULL)
    {
        printf("%ld %s %s finished at the time of %.2lf and finish in place: %d\n",temp->Id,temp->First_Name,temp->Last_Name,temp->duration,getContestantRank(temp->Id));
        temp=temp->next;
    }
}
Contestant* getContestantbyID(long id) /*function that receives an id an returns the contestant with his data if no contestant found returns null*/
{
    Contestant *temporary=race_res;
    while(temporary!=NULL)
    {
        if(temporary->Id==id)
        {
            return temporary;
        }
        temporary=temporary->next;
    }
    return NULL;
}
void DeleteContestant(long id) /*function to delete a contestant*/
{
    Contestant *Currentnode,*PREV;
    Currentnode=race_res;
    if(race_res==NULL)
    {
        printf("No Such Contestant\nThere is no such contestant in the race\n");
        return;
    }
    if(id==race_res->Id)
    {
        Currentnode=race_res;
        race_res=race_res->next;
        free(Currentnode);
        return;
    }
    else
    {
        PREV=race_res;
        Currentnode=race_res->next;
        while(Currentnode!=NULL && Currentnode->Id!=id)
        {
            PREV=Currentnode;
            Currentnode=Currentnode->next;
        }
        if(Currentnode!=NULL)
        {
            PREV->next=Currentnode->next;
            free(Currentnode);
            return;
        }
    }
    return;
}
void printcontafter(long id) /* function to print the contestant after the contestant we want to delete*/
{
    Contestant *trialnode;
    trialnode=race_res;
    int counter=0;
    while(trialnode!=NULL)
    {
        counter++;
        if(id==trialnode->Id)
        {
            trialnode=trialnode->next;
            printf("%ld %s %s finished at the time of %.2lf and finish in place: %d\n",trialnode->Id,trialnode->First_Name,trialnode->Last_Name,trialnode->duration,counter);
        }
        trialnode=trialnode->next;
    }
}
int getContestantRank(long id) /*function that gives us the place of the contestant based on his id if not found returns -1 as requested*/
{
    Contestant *testNode;
    testNode=race_res;
    int Count=0;
    while(testNode!=NULL)
    {
        Count++;
        if(id==testNode->Id)
        {
            return Count;
        }
        testNode=testNode->next;
    }
    return -1;
}
void freeRace (Contestant* race) /* function to free all the contestants*/
{
    if(race!=NULL)
    {
        freeRace(race->next);
        free(race);
    }
}
