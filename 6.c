//a
#include<stdio.h>
int main()
{
int i, j, n, a[50], frame[10], no, k, avail, count=0;
printf("\n ENTER THE NUMBER OF PAGES:\n");
scanf("%d", &n);
printf("\n ENTER THE PAGE NUMBER :\n");
for(i=1; i<=n; i++)
scanf("%d",&a[i]);
printf("\n ENTER THE NUMBER OF FRAMES :");
scanf("%d", &no);
for(i=0; i<no; i++)
frame[i]= -1;
j=0;
printf("\tref string\t page frames\n");
for(i=1; i<=n; i++)
{
printf("%d\t\t", a[i]);
avail=0;
for(k=0; k<no; k++)
if(frame[k]==a[i])
avail=1;
if (avail==0)
{ 
    frame[j]=a[i];
j=(j+1)%no;
count++;
for(k=0;k<no;k++)
printf("%d\t", frame[k]);
}
printf("\n");
}
printf("Page Fault Is %d", count);
return 0;
}

//b
#include<stdio.h>
main()
{
int q[20], p[50], c=0, c1, d, f, i, j, k=0, n, r, t, b[20], c2[20];
printf("Enter no of pages:");
scanf("%d", &n);
printf("Enter the reference string:");
for(i=0; i<n; i++)
scanf("%d", &p[i]);
printf("Enter no of frames:");
scanf("%d",&f);
q[k]=p[k];
printf("\n\t%d\n",q[k]);
c++;
k++;
for(i=1; i<n; i++)
{
c1=0;
for(j=0; j<f; j++)
{
if(p[i]!=q[j])
c1++;
}
if(c1==f)
{
c++;
if(k<f)
{
q[k]=p[i];
k++;
for(j=0; j<k; j++)
printf("\t%d",q[j]);
printf("\n");
}
else
{
for(r=0; r<f; r++)
{
c2[r]=0;
for(j=i-1; j<n; j--)
{
if(q[r]!=p[j])
c2[r]++;
else
break;
}
}
for(r=0; r<f; r++)
b[r]=c2[r];
for(r=0; r<f; r++)
{
    for(j=r; j<f; j++)
{
if(b[r]<b[j])
{
t=b[r];
b[r]=b[j];
b[j]=t;
}
}
}
for(r=0; r<f; r++)
{
if(c2[r]==b[0])
q[r]=p[i];
printf("\t%d",q[r]);
}
printf("\n");
}
}
}
printf("\nThe no of page faults is %d",c);
}