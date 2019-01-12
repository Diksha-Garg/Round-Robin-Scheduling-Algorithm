#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
struct node{
int pid;
int ptime;
struct node *prev;
struct node *next;
};
static int i=1;

struct node *insertion(struct node *start)
{
 struct node *n,*t=start;

 int time;
 n=new node;
 n->pid=i;

 /*cout<<"Enter burst time for process "<<i<<" ";
 cin>>time;*/
 n->ptime=rand()%20;
 i++;
 if(start==NULL)
 {   start=n;
     n->prev=start;
     n->next=start;
     }
     else
     {

         while(t->next!=start)
            t=t->next;
         t->next=n;
         n->prev=t;
         n->next=start;
         start->prev=n;

     }
return start;
}
void display(struct node *start)
{
     node *p;
  p=start;
  cout<<"PID"<<"  "<<"PTIME"<<endl;
do
  {  cout<<p->pid<<"  "<<p->ptime<<endl;
  p=p->next;
}while(p!=start);

}
struct node * deletion(struct node *start)
{
    if(start==NULL){
    cout<<"LIST IS EMPTY";
    return start;
    }
     if(start->next==start)
        start=NULL;
    else{
        struct node *ptr1;
        ptr1=start->next;
        ptr1->prev=ptr1->prev->prev;
        ptr1->prev->next=ptr1;
        start=ptr1;
    }

    return start;
}
struct node * roundrobin(struct node *start,int matrix[][2],int *size)
{
    const int totalcycles=1500;
    int nptime=rand()%10;
       static int c=0;
 struct node *ptr=start;
 int tq,id,time;
 cout<<"Enter time quantum ";
 cin>>tq;
 cout<<"PID"<<"  "<<"PTIME"<<endl;
 while(ptr!=NULL)
 {
     if(ptr->ptime<=tq)
     {
         id=ptr->pid;
         time=ptr->ptime;
         ptr->ptime=0;
         cout<<ptr->pid<<"  "<<ptr->ptime<<endl;
         ptr=deletion(ptr);
     }
     else{
        ptr->ptime=ptr->ptime-tq;
        id=ptr->pid;
         time=tq;
        cout<<ptr->pid<<"  "<<ptr->ptime<<endl;
        ptr=ptr->next;
}
matrix[c][0]=id;
if(c==0)
    matrix[c][1]=time;
else
{
    time=time+matrix[c-1][1];
}
matrix[c][1]=time;
c++;
if(time>=totalcycles)
    break;
if(time>=nptime)
{
 ptr=insertion(ptr);
 nptime=rand()%(time+10);
}
}
*size=c;
 return ptr;

}
int main()
{
    srand(time(NULL));
    cout<<"Enter no.of processes ";
    int t;
    cin>>t;
    struct node *start=NULL;
    while(t--)
    {
        start=insertion(start);

    }
    cout<<"After insertion"<<endl;
    display(start);
    int matrix[1000][2]={0};
    int size;
    //cout<<"After deletion"<<endl;
   // start=deletion(start);
    //display(start);
    start=roundrobin(start,matrix,&size);
    cout<<"GANTT CHART"<<endl;
    int i,j;
    cout<<"PID"<<"  "<<"PTIME"<<endl;
    for(i=0;i<size;i++)
    {
        for(j=0;j<2;j++)
            cout<<matrix[i][j]<<"  ";
        cout<<endl;
    }

}
