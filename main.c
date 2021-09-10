#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct{
    int year;
    int month;
    int day;
}DOB;

typedef struct{
    char Fname[20];
    char Lname[20];
    DOB date;
    char location[40];
    char phone[40];
    char email[50];
}Contacts;

int counter=0;
Contacts arr[100];

int CheckNumber(char number[40]){
    int i=0,counter=0;
    for(i=0;number[i]!='\0';i++){
        counter++;
    }
    return counter;
}
int CheckMail(char mail[40]){
    int i=0,flag=0;
    for(i=0;i<strlen(mail);i++){
        if(mail[i]=='@')
            flag=1;
    }
    return flag;
}


//Task 1
void readContactsFromFile(){
    FILE* f;
    char filename[20];
    printf("Please Enter the name of file :");
    scanf("%s",filename);
    f=fopen(filename,"r");
    if(f!=NULL){
        while(!feof(f)){
            fscanf(f,"%[^,],",arr[counter].Fname);
            fscanf(f,"%[^,],",arr[counter].Lname);
            fscanf(f,"%d-%d-%d,",&arr[counter].date.day,&arr[counter].date.month,&arr[counter].date.year);
            fscanf(f,"%[^,],",arr[counter].location);
            fscanf(f,"%[^,],",arr[counter].phone);
            fscanf(f,"%[^\n]\n",arr[counter].email);
            counter++;
        }
        printf("file read successfully\n");
    }
    else
        printf("Error, file doesn't exist\n");
    fclose(f);
}

//Task 2
void SearchByLname(){
    char lname[20];
    int i=0,n=0;
    printf("Please enter person's last name: ");
    scanf("%s",lname);
    for(i=0;i<counter;i++){
        if(strcmp(lname,arr[i].Lname)==0){
            printf("%d- First name:%s,\tAddress:%s,\tEmail:%s,\tPhone:%s\n",++n,arr[i].Fname,arr[i].location,arr[i].email,arr[i].phone);
        }
    }
    if(n==0)
        printf("There is no such name\n");

}

//Task 3
void AddContact(){
    char temp;
    printf("\nPlease enter the first name: ");
    scanf("%s",arr[counter].Fname);
    printf("\nEnter the last name: ");
    scanf("%s",arr[counter].Lname);

    printf("\nEnter the date of birth: ");
    scanf("%d %d %d",&arr[counter].date.day,&arr[counter].date.month,&arr[counter].date.year);
    while(arr[counter].date.day<=0 ||arr[counter].date.day>31 || arr[counter].date.month<=0 ||arr[counter].date.month>12 || arr[counter].date.year<1900 || arr[counter].date.year>2022){
        printf("Please re-enter valid date of birth :");
        scanf("%d %d %d",&arr[counter].date.day,&arr[counter].date.month,&arr[counter].date.year);
    }
	scanf("%c",&temp); // temp statement to clear buffer

    printf("\nEnter the street: ");
    scanf("%[^\n]",arr[counter].location);

    printf("\nEnter the phone number: ");
    scanf("%s",arr[counter].phone);
    while(CheckNumber(arr[counter].phone)!=11 || arr[counter].phone[0]!='0'){
        printf("Please re-enter valid mobile phone:");
        scanf("%s",arr[counter].phone);
    }


    printf("\nEnter the Email: ");
    scanf("%s",arr[counter].email);
    while(CheckMail(arr[counter].email)==0){
        printf("Please re-enter valid Email:");
        scanf("%s",arr[counter].email);
    }
    counter++;
}

//Task 4
void RemoveContact(){
    char fname[20],lname[20];
    Contacts temp;
    int i=0,flag=0;
    printf("\nPlease enter the first name: ");
    scanf("%s",fname);
    printf("\nEnter the last name: ");
    scanf("%s",lname);
    for(i=0;i<counter;i++){
            if(strcmp(arr[i].Fname,fname)==0 && strcmp(arr[i].Lname,lname)==0){
            temp =arr[i];
            arr[i]=arr[i+1];
            arr[i+1]=temp;
            flag=1;
        }
    }
    if(flag ==0)
        printf("There is no such name in contacts\n");
    else{
        printf("Removed this name successfully\n");
        counter--;
    }
}

//Task 5
void ModifyContact(){
    char lname[20],mini_counter=0,n=0,flag=0;
    int i,x;
    printf("\nPlease enter the last name of the contact you need to modify:");
    scanf("%s",lname);
    for(i=0;i<counter;i++){
        if(strcmp(arr[i].Lname,lname)==0){
            printf("%d- %s %s\n",++n,arr[i].Fname,arr[i].Lname);
            flag=1;
            }
    }
    if(flag==0){
        printf("There is no such name\n");
        return;
    }
    do{
    printf("Please choose a contact (1-%d)",n);
    scanf("%d",&x);
    }while(x<1 || x>n);
    for(i=0;i<counter;i++){
        if(strcmp(arr[i].Lname,lname)==0)
            mini_counter++;
    if(mini_counter==x)
        break;
    }
    printf("Please enter the new information:\n");
    int temp;
    temp=counter;
    counter=i;
    AddContact();
    counter =temp;
    printf("Modified the contact successfully\n");
}
//Task 6
void PrintSorted(){
    int choice,i;
    printf("What type of sorting do you want?(choose by number)\n1-Sort By Date of Birth\n2-Sort By Last name\n");
    scanf("%d",&choice);
    while(choice !=1 && choice!=2){
        printf("\nPlease enter valid number(either 1 or 2)");
        scanf("%d",&choice);
    }
    if(choice==2){
        SortByLname();
        for(i=0;i<counter;i++)
            printf("%s,%s,%d-%d-%d,%s,%s,%s\n",arr[i].Fname,arr[i].Lname,arr[i].date.day,arr[i].date.month,arr[i].date.year,arr[i].location,arr[i].phone,arr[i].email);
    }
    if(choice==1){
        SortByDOB();
        for(i=0;i<counter;i++)
            printf("%s,%s,%d-%d-%d,%s,%s,%s\n",arr[i].Fname,arr[i].Lname,arr[i].date.day,arr[i].date.month,arr[i].date.year,arr[i].location,arr[i].phone,arr[i].email);
        }
}
void SortByDOB(){
    int i,j;
    Contacts temp;
    for(i=0;i<counter;i++){
        for(j=0;j<counter;j++){
            if(arr[i].date.year<arr[j].date.year){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
            if(arr[i].date.year == arr[j].date.year && arr[i].date.month<arr[j].date.month){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
            if(arr[i].date.year == arr[j].date.year && arr[i].date.month==arr[j].date.month && arr[i].date.day<arr[j].date.day){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

void SortByLname(){
    int i,j;
    Contacts temp;
    for(i=0;i<counter;i++){
        for(j=0;j<counter;j++){
            if(strcmp(arr[i].Lname,arr[j].Lname)<0){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

//Task 7
void SaveProgram(){
    FILE* f;
    int i=0;
    f=fopen("output.txt","w");
    for(i=0;i<counter;i++)
        fprintf(f,"%s,%s,%d-%d-%d,%s,%s,%s\n",arr[i].Fname,arr[i].Lname,arr[i].date.day,arr[i].date.month,arr[i].date.year,arr[i].location,arr[i].phone,arr[i].email);
    printf("Exported successfully to output.txt\n");
    fclose(f);
}
//Task 8
void QuitProgram(){
    char x;
    printf("Are you sure you want to exit?changes will be discarded(Y/N)");
    x=getchar();
    x=getchar();
    switch(x)
    {
        case 'Yes':
        case 'yes':
        case 'Y':
        case 'y':
            exit(0);
            break;
        case 'No':
        case 'no':
        case 'N':
        case 'n':
            break;
        default:
            exit(0);
    }

}
//Menu
interface(){
printf("*****************************Phonebook*****************************\n");
printf("1)Read contacts from files\n");
printf("2)Search for a name\n");
printf("3)Add contacts\n");
printf("4)Remove contacts\n");
printf("5)Modify contacts\n");
printf("6)Sort contacts\n");
printf("7)Save program\n");
printf("8)Quit\n");
printf("Please choose a number for a task from 1 to 8 for a task: ");
}
int main()
{
    int g=1,z,y;
    while(g==1){
    interface();
    scanf("%d",&z);
    while(z<1||z>8){
       printf("Enter a valid number: ");
       scanf("%d",&z);
    }
    switch(z){
    case 1:readContactsFromFile();
    break;
    case 2:SearchByLname();
    break;
    case 3:AddContact();
    break;
    case 4:RemoveContact();
    break;
    case 5:ModifyContact();
    break;
    case 6:PrintSorted();
    break;
    case 7:SaveProgram();
    break;
    case 8:QuitProgram();
    break;
    }
    printf("Enter 1 to return to menu: ");
    scanf("%d",&y);
    while(y!=1){
        printf("\nEnter 1 to return to menu: ");
        scanf("%d",&y);
    }
    system("cls");
}
    return 0;
}
