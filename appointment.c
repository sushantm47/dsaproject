#include <stdio.h>
#include <conio.h>
#include <string.h>

int main()
{
  int flag;
  int t,x,i,j;
  t=10;x=0;
  int slot,doctor;
  int a[10][3];
for(i=0;i<=4;i++)
    for (j=0;j<=2;j++)
    {
      //printf("@\n");
      a[i][j]=0;
    }
    for(i=0;i<5;i++)
      for (j=0;j<1;j++)
      {
      //  printf("*\n");
        a[i][j]=x;
        x=x+1;
      }

  /*doctor 1=1
    doctor 2=2
    doctor 3=3
    doctor 4=4*/
  //  printf("enter your preffered doctor\n");
    printf("enter the time slot\n");
    for (i=0;i<5;i++){
      printf("%d:00 to %d:00 = %d\n",t,t+1,i);
      t=t+2;
    }

    for(i=0;i<5;i++)
      {
        for (j=0;j<=1;j++)
      {
        printf("%d\t",a[i][j]);
        }
        printf("\n");
}

    //scanf("%d",&doctor)
  while(1){

          printf("press 1 for booking 7 for exit\n");
          scanf("%d",&x );
          printf("enter the time slot\n");
          scanf("%d",&slot);
  switch (x) {
            case 1:  for(i=0;i<5;i++){
                    for (j=1;j<2;j++)
                    {
                      if (a[slot][1]==0)
                            {
                              printf("are you sure you want to book the slot??\n[Yes=1][No=0]\n");
                              scanf("%d",&flag);
                              if(flag==1){
                              printf("confirmed\n");
                              a[slot][1]=1;
                            break;
                            }

                              else{
                            printf("slot cancelled\n");
                            exit(1);
                            }
                            }
                      else if(a[slot][1]==1)
                            printf("slot unavailable\n");
                          }

                      break;
                    }
                    for(i=0;i<5;i++)
                    {  for (j=0;j<=1;j++)
                      {
                        printf("%d\t",a[i][j]);
                      }
                    printf("\n");
              }break;
          case 7:exit(1);
        }
    }
}
