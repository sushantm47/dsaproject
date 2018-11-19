#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int id;
    int units;
    char data[20];
    struct node *next;
};
typedef struct node NODE;


NODE * insert_at_end(NODE * start, int id,int units, char *data)
{
    NODE * newnode, * nextnode;
    newnode = (NODE *)malloc(sizeof(NODE));
    if(newnode == NULL) {
        printf("Memory Allocation Failed\n");
        return start;
    }

    newnode->id = id;
    newnode->units = units;
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
        printf("%d\t%d\t%s\n", start->id,start->units, start->data);
        start = start->next;
    }
}

NODE * read_from_file(NODE * start)
{
    FILE *fp;
    int id;
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
        start = insert_at_end(start, id, units, data);

    }
    fclose(fp);
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
    FILE *fp;
    fp = fopen("p.txt", "w");
    if(fp == NULL) {
        printf("Unable to open file\n");
        return;
    }

    // Dump the list data back to file
     while(start!=NULL)
    {
        fprintf(fp, "%d %d %s\n", start->id, start->units,start->data);
        start = start->next;
    }
    fclose(fp);
/*
        FILE *fp2;
        fp2 = fopen("water.txt", "w");
        if(fp2 == NULL) {
            printf("Unable to open file\n");
            return;
        }

        // Dump the list data back to file
         while(start!=NULL)
        {
            fprintf(fp, "%d %d %s\n", start->id, start->units,start->data);
            start = start->next;
        }
        fclose(fp2);*/
}

int main()
{
    NODE *start = NULL;
    int choice;
    int id,units;
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
                    printf("Enter id(int) and units and data(string)\n");
                    scanf("%d %d", &id,&units);
                    gets(data);
                    start = insert_at_end(start, id,units, data);
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
