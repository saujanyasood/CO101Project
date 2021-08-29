#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum {false,true} bool;
struct res
{
    char fname[15];
    char lname[15];
    char add[5];
    char phone[11];
    int age;
    char occupation[15];
    char cmd[15];
    int ptID;
    int apt;
};


void insert_res(int counter)
{
    system("cls");
    FILE *fp;
    int d;
        struct res r1;
        printf("Please give the following information -\nName - ");
        fflush(stdin);
        scanf("%s %s",r1.fname,r1.lname);
        printf("Address - ");
        scanf("%s",r1.add);
        printf("Contact Number - ");
        scanf("%s",r1.phone);
        printf("Age - ");
        scanf("%d",&r1.age);
        printf("Occupation - ");
        scanf("%s",r1.occupation);
        printf("Health Problems(If Any) - ");
        scanf("%s",r1.cmd);
        r1.ptID=counter+1;
        printf("\nEnter today's date \t July  ");
        scanf("%d",&d);
        r1.apt=d+1+(counter/10);
        fp=fopen("database.dat","ab");
        fwrite(&r1,sizeof(r1),1,fp);
        fclose(fp);
        FILE *fo;
        fo=fopen("count.dat","wb");
        fprintf(fo,"%d",counter+1);
        fclose(fo);
        printf("\nSign up successfull!!\nYour Patient ID is %d\nYou have your appointment on %d July\n ",r1.ptID,r1.apt);
        return;
}
void remove_res()
{
    system("cls");
    int pt;
    bool check=true;
    printf("\nEnter the PATIENT ID of the person you want to vaccinate\n");
    scanf("%d",&pt);
    FILE *ft;
    ft=fopen("temp.dat","wb+");
    FILE *fp;
    fp=fopen("database.dat","rb+");
    struct res rr;
    while(fread(&rr,sizeof(rr),1,fp)==1)
    {
        if(pt!=rr.ptID)
        {
        fwrite(&rr,sizeof(rr),1,ft);
        }

        else
        check=false;
    }
    fclose(fp);
    fclose(ft);
    remove("database.dat");
    rename("temp.dat","database.dat");
    if(check==true)
    {
        printf("\nPerson not found!!\n");
        return;
    }
    printf("\nSuccesfully vaccinated!!!\n");
}
void viewapt()
{
    printf("Enter the date for which you want to see the apppointments - ");
    int d;
    scanf("%d",&d);
    struct  res r;
    FILE *fp;
    fp=fopen("database.dat","rb");
    while(fread(&r,sizeof(r),1,fp)==1)
    {
        if(d==r.apt)
        {
            printf("\n%d %s %s %s %s %d %s %s\n",r.ptID,r.fname,r.lname,r.add,r.phone,r.age,r.occupation,r.cmd);
            
        }
    }
}
void viewres()
{
    FILE *fp;
   fp=fopen("database.dat","rb");
   struct res r1;
   system("cls");
   fflush(stdin);
   while(fread (&r1,sizeof(r1),1,fp)==1)
   printf("\n%d %s %s %d July\n",r1.ptID,r1.fname,r1.lname,r1.apt);
}
void viewadmin()
{
   FILE *fp;
   fp=fopen("database.dat","rb");
   struct res r1;
   system("cls");
   fflush(stdin);
   while(fread (&r1,sizeof(r1),1,fp)==1)
   printf("\n%d %s %s %s %s %d %s %s\n",r1.ptID,r1.fname,r1.lname,r1.add,r1.phone,r1.age,r1.occupation,r1.cmd);
}
void res_menu(int counter)
{
    bool check=true;
    char ch;
    system("cls");
    printf("\t\t******Welcome Resident******\n\t\tBe Safe and Maintain Social Distancing\n");
    while(check){
    printf("\nEnter your choice -\na)Sign up to get vaccination\nb)Vaccination Index\nc)Exit\n");
    fflush(stdin);
    scanf("%c",&ch);
    if(ch=='a')
    {
    insert_res(counter);
    check=false;
    }
    else if(ch=='b'){
    viewres();
    
    }
    else if(ch=='c')
    exit(0);
    else{
        char che;
        printf("\nWrong Choice!!\nEnter your choice -\na)Re-enter Choice\nb)Exit\n");
        fflush(stdin);
        scanf("%c",&che);
        if(che=='b')
        exit(0);
    }
    }
}
void admin_menu(char *name)
{
    char ch;
    bool check=true;
    system("cls");
    printf("\t\t******Welcome %s******\n\t\t  Thank You For Your service\n",name);
    while(check)
    {
        printf("\nEnter your choice -\na)Vaccination Index\nb)Your Appointments\nc)Vaccinate a resident\nd)Exit\n");
        fflush(stdin);
        scanf("%c",&ch);
        if(ch=='c')
        {
        remove_res();
        
        }
        else if(ch=='a')
        {
        viewadmin();
        
        }
        else if(ch=='d')
        exit(0);
        else if(ch=='b')
        viewapt();
        else
        {
            char che;
        printf("\nWrong Choice!!\nEnter your choice -\na)Re-enter Choice\nb)Exit\n");
        fflush(stdin);
        scanf("%c",&che);
        if(che=='b')
        exit(0);
        }
    }
}
void login()
{
    system("cls");
    bool check=true;
    char ch;
    char name[10];
    int pass;
    while(check){
    printf("Enter your name and password - \n");
    scanf("%s %d",name,&pass);
    if(pass==2134)
    {
        admin_menu(name);
        ~check;
    }
    else
    {
        char che;
        printf("\nIncorrect username or password!!\n Enter choice - \n a)Re-enter Username and password \n b)Exit\n");
        fflush(stdin);
        scanf("%c",&che);
        if(che=='b')
        exit(0);
        
    }
    }
}
int main()
{
    char ch;
    int counter;
    FILE *p;
    p=fopen("count.dat","rb");
    if(p==NULL)
    {
        counter=0;
        p=fopen("count.dat","wb");
        fprintf(p,"%d",counter);
        fclose(p);
        p=fopen("count.dat","rb");
    }
    fscanf(p,"%d",&counter);
    fclose(p);
    system("cls");
    bool check = true;
    printf("\t\t***********WELCOME TO FRIENDS COLONY VACCINATION SYSTEM***********");
    while(check)
    {
        fflush(stdin);
        printf("\nEnter your choice : \na)Healthcare Employee \nb)Resident\nc)Exit\n");
        scanf("%c",&ch);
        if(ch=='a')
        {
            login();
           check=false;
        }
        else if(ch=='b')
        {
            res_menu(counter);
            check = false;
        }
        else if(ch=='c')
            exit(0);
        else
        {
            printf("\nInvalid input!!");

        }
    }
    return 0;
}