#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int id;
    int age;
    int units;
    int gallons;
    char data[20];
    struct node *next;
};
typedef struct node NODE;


NODE * insert_at_end(NODE * start, int id,int units,int gallons, char *data,int user)
{
    NODE * newnode, * nextnode;
    newnode = (NODE *)malloc(sizeof(NODE));
    if(newnode == NULL) {
        printf("Memory Allocation Failed\n");
        return start;
    }
    if(user==1){
        newnode->id = id;
        newnode->units = units;
        newnode->gallons=gallons;
        strcpy(newnode->data, data);
    }
    else if((user==0)&&(gallons==0)){
      newnode->id = id;
      newnode->units = units;
      strcpy(newnode->data, data);
}
    else if((user==0)&&(gallons=1)) {
    newnode->gallons=gallons;
  }
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
  printf("ID\tUNITS\tGALLONS\tDATA\n");

    while(start!=NULL) {
        printf("%d\t%d\t%d\t%s\n", start->id,start->units,start->gallons,start->data);
        start = start->next;
    }
}

NODE * read_from_file(NODE * start)
{
    NODE * start2;
    FILE *fp,*fp2;
    int id;
    int gallons=0;
    int units;
	char data[20];

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

            fscanf(fp, "%d %d %s\n", &id, &units, data);
            start = insert_at_end(start, id, units,0, data,0);

        }
        fclose(fp);
        start2=start;

    //file to store number of gallons used by a particular id
    fp2 = fopen("water.txt", "r");
    if(fp2 == NULL) {
        printf("Unable to open file\n");
        return 0;
    }
    while(1) {
        if(feof(fp2))
        {printf(" to open file 2\n");
            break;}
        fscanf(fp2, "%d %d %s\n", &id,&gallons, data);
        start2 = insert_at_end(start2, id,3,gallons, data,0);
    }

    fclose(fp2);
    printf("\nThe list read from file is...\n");
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
    NODE *start2;
    start2=start;
    FILE *fp,*fp2;
    fp = fopen("p.txt", "w");
    if(fp == NULL) {
        printf("Unable to open file\n");
        return;
    }
  // Dump the electricity list data back to p file  file
     while(start!=NULL)
    {
        fprintf(fp, "%d %d %s\n", start->id, start->units,start->data);
        start = start->next;
    }
    fclose(fp);

    //water bill file
    fp2 = fopen("water.txt", "w");
    if(fp2 == NULL) {
        printf("Unable to open file\n");
        return;
    }
    // Dump the water bill related data from list data back to water.txt file
     while(start2!=NULL)
    {
        fprintf(fp2, "%d %d %s\n", start2->id, start2->gallons,start2->data);
        start2 = start2->next;
    }
    fclose(fp2);
}

int main()
{
    NODE *start = NULL;
    NODE *start2=NULL;
    int choice;
    int id,units,gallons;
    char data[20];

    // Before we start with any operations,
    // We read existing file details into list
    start = read_from_file(start);

    while(1)
    {
        // You have menu to perform required list operations
        printf("\n** MENU **\n");
        printf("1,9-Display List\n");
        printf("2-Add to list(list end)\n");
        printf("3-HESCOM BILL\n");
        printf("3-WATER BILL\n ");
        printf("7-Exit\n");

        printf("Enter your choice\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: display(start);
                    break;
            case 9: display(start2);
                            break;
            case 2: printf("Enter data you want to insert to list\n");
                    printf("Enter id(int) and units and data(string)\n");
                    scanf("%d %d %d", &id,&units,&gallons);
                    gets(data);
                    start = insert_at_end(start, id,units,gallons ,data,1);
                    break;
            /*case 3:printf("enter the id to be located\n");
                    scanf("%d",&id);
                    start = current_bill( start, id );
                    break;*/
            case 4:printf("enter the id to be located\n");
            case 7: printf("Program Terminating\n");
                    // Before we terminate, we dump the existing
                    // list data to file
                    dump_data(start);
                    exit(1);
        }
    }
    return 0;
}
