#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct node
{
    int id;
    int units;
    int age;
    int g;
    char data[20];
    struct node *next;
};
typedef struct node NODE;


NODE * insert_at_end(NODE * start, int id,int units,int g,int age, char *data)
{
    NODE * newnode, * nextnode;
    newnode = (NODE *)malloc(sizeof(NODE));
    if(newnode == NULL) {
        printf("Memory Allocation Failed\n");
        return start;
    }

    newnode->id = id;
    newnode->units = units;
    newnode->g=g;
    newnode->age=age;
	strcpy(newnode->data, data);
	newnode->next = NULL;

    if(start == NULL)
        start = newnode;
    else {
        nextnode = start;
        while(nextnode->next != NULL)
            nextnode = nextnode->next;

        nextnode->next = newnode;
    }
    return start;
}

void display(NODE * start)
{
    while(start!=NULL) {
        printf("%d\t%d\t%d\t%d\t%s\n", start->id,start->units,start->g,start->age, start->data);
        start = start->next;
    }
}

NODE * read_from_file(NODE * start)
{
    FILE *fp;
    int id;
    int units;
    int g;
    int age;
	char data[20];
    FILE *fp2;
    fp2 = fopen("water.txt", "r");
    FILE *fp3;
    fp3 = fopen("electricity.txt", "r");

    fp = fopen("p.txt", "r");
    if(fp == NULL) {
        printf("Unable to open file\n");
        return 0;
    }

    // Until we reach the end of the file,
    // Read the numbers from one by one and
    // Insert at the end of the list
    while(1) {
        if(feof(fp))
            break;

        fscanf(fp, "%d %d %s ", &id,&age, data);
        fscanf(fp2,"%d",&g);
        fscanf(fp3, "%d",&units );
        start = insert_at_end(start, id, units,g,age, data);

    }
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    printf("\nThe list read from file is...\n");
    printf("ID\t UNITS\t GALLONS\t USER \n" );
    display(start);
    printf("\nYou will be now operating on above list.\n");
    return start;
}

NODE * current_bill(NODE * start,int id )
{
    NODE * p;
    p=start;
     while(p!=NULL)
    {
        if(p->id==id)
        {
            printf("\n id found and units = %d",p->units);
            return start;
        }
        else{
            p=p->next;
          }
      }
      return start;

}



void dump_data(NODE * start)
{
    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    fp3 = fopen("electricity.txt", "w");
    fp2 = fopen("water.txt", "w");
    fp = fopen("p.txt", "w");
    if(fp == NULL) {
        printf("Unable to open main file file\n");
        return;
    }
    if(fp2 == NULL) {
        printf("Unable to open water file\n");
        return;
    }
    if(fp3 == NULL) {
        printf("Unable to open electricity file file\n");
        return;
    }

    // Dump the list data back to file
     while(start!=NULL)
    {
        fprintf(fp, "%d \t %d\t %s\n", start->id,start->age,start->data);
        fprintf(fp2,"%d\n",start->g);
        fprintf(fp3,"%d\n",start->units);
        start = start->next;
    }
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
/*
        FILE *fp2;

        if(fp2 == NULL) {
            printf("Unable to open file\n");
            return;
        }

        // Dump the list data back to file
         while(start!=NULL)
        {
            fprintf(fp, " %d \n", start->units);
            start = start->next;
        }
        fclose(fp2);*/
}

int main()
{
    NODE *start = NULL;
    int choice;
    int id,units,g,age;
    char data[20];

    // Before we start with any operations,
    // We read existing file details into list
    start = read_from_file(start);

    while(1)
    {
        // You have menu to perform required list operations
        printf("\n** MENU **\n");
        printf("1-Display List\n");
        printf("2-Add to list(list end)\n");
        printf("3-current\n ");
        printf("7-Exit\n");

        printf("Enter your choice\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: display(start);
                    break;

            case 2: printf("Enter data you want to insert to list\n");
                    printf("Enter the following details:\n1. your id(int)\n2. units(int)\n3.Water used in this month(in gallons)\n4'age\n4. data(string)\n");
                    scanf("%d %d %d %d", &id,&units,&g,&age);
                    gets(data);
                    start = insert_at_end(start, id,units,g,age, data);
                    break;
            case 3:printf("enter the id to be located");
                    scanf("%d",&id);
                    start = current_bill( start, id );
                    break;
            case 7: printf("Program Terminating\n");
                    // Before we terminate, we dump the existing
                    // list data to file
                    dump_data(start);
                    exit(1);
        }
    }
    return 0;
}
