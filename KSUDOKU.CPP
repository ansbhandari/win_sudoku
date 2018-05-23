#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip.h>
#include<conio.h>
//////////////////////////////////////////////////
class sudoku
{
int sudo[9][9][10];
FILE *inp;
FILE *oup;
int i,j,k;
public:
sudoku(); //constructor
void readfile();
void write();
void show();
void eliminate();
void update();
void solve();
int issolved();
};
//////////////////////////////////////////////////
sudoku :: sudoku() //constructor definition
{
for(i=0;i<9;i++)
for(j=0;j<9;j++)
for(k=0;k<=9;k++)
sudo[i][j][k]=0;
}
//////////////////////////////////////////////////
void sudoku :: readfile()
{
inp=fopen("input.txt","r");
if(inp==NULL){
cout<<"Cannot open file 'input.txt'"<<endl;
getch();
exit(0);}
else
cout<<"Reading data form file "<<endl;
for(i=0;i<9;i++)
for(j=0;j<9;j++){
fscanf(inp,"%d",&sudo[i][j][0]);
//cout<<"copying 1 through 9\n";
if(sudo[i][j][0]==0){
	for(k=1;k<=9;k++)
	sudo[i][j][k]=k;
	//cout<<"Copied in ["<<i<<"]["<<j<<"]"<<endl;
	}}
}
///////////////////////////////////////////////////////
void sudoku :: write()
{
char yes;
cout<<"Do you want to write result in file 'write.txt' <<y/n>>: ";
cin>>yes;
if(yes=='y')
{
oup=fopen("output.txt","w");
fprintf(oup,"Solved sudoku... \n\n");
for(i=0;i<9;i++) {
for(j=0;j<9;j++)
fprintf(oup,"%d\t",sudo[i][j][0]);
fprintf(oup,"\n");}
fclose(oup);
cout<<"\nResult written.";
}
else
cout<<"Result is not written in the file.";
}
///////////////////////////////////////////////////////
void sudoku :: show()
{
clrscr();
cout<<endl;
for(i=0;i<9;i++)
{
for(j=0;j<9;j++)
if(sudo[i][j][0]!=0)
cout<<sudo[i][j][0]<<"\t";
else cout<<"-\t" ;
cout<<endl;
}
cout<<"\nPossible values : \n";
for(i=0;i<9;i++){
for(j=0;j<9;j++)
{
if(sudo[i][j][0]==0)
	{for(k=1;k<=9;k++)
	if(sudo[i][j][k]!=0)
	cout<<sudo[i][j][k];}
else
cout<<"-";
cout<<"\t";}
cout<<endl;}
}
///////////////////////////////////////////////////////
void sudoku :: solve()
{
char w;
int row, col, value;
this->eliminate();
do
{ this->show();
cout<<"\nPress 'e'-to exit,'d'-if done,'Ctrl+u'-for auto-update or 'Enter' to input yourself : ";
w=getche();
if(w=='d')
break;
else if(w=='e'||w==27)
exit(0);
else if(w==21)
this->update();
else{
cout<<"Enter position and value to replace :\n";
cout<<"(e.g 1 2 9 to replace value[1][2] by 9) : ";
cin>>row>>col>>value;
if(sudo[row-1][col-1][0]==0)
{
	sudo[row-1][col-1][0]=value;
	for(k=1;k<=9;k++)
	sudo[row-1][col-1][k]=0;
	this->eliminate();
	}
else{
cout<<"Illigal input....stupid user!";
getch();}
}
//this->show();
}while(w!= 27);
}
//////////////////////////////////////////////////////////
int sudoku :: issolved()
{
int val,m,n,chk=0,sc,sr;
for(i=0;i<9;i++)
for(j=0;j<9;j++)
{
val=sudo[i][j][0];
if(val==0){
cout<<"Position ("<<i<<","<<j<<") is unfilled !\n";	 	//found unfilled place
chk=1;}
for(m=0;m<0&&m!=j;m++)
if(sudo[i][m][0]==val){
cout<<"Match found in "<<i+1<<"th row\n";	//match found in row
chk=1;}
for(n=0;n<9&&n!=i;n++)
if(sudo[n][j][0]==val){
cout<<"Match found in "<<j+1<<"th column\n";	//match found in column
chk=1;}
sr=3*(i/3);
sc=3*(j/3);
for(n=sr;n<(sr+3)&&n!=i;n++)
for(m=sc;m<(sc+3)&&m!=j;m++)
if(sudo[n][m][0]==val){
cout<<"Match found in "<<sr+1<<sc+1<<"th square.\n";	//match found in column
chk=1;}
}
getch();
return chk;
}
//////////////////////////////////////////////////////////
void sudoku :: update()
{
int count,ans; //for solution
for(i=0;i<9;i++)
for(j=0;j<9;j++)
if(sudo[i][j][0]==0)
{
	count=0;
	for(k=1;k<=9;k++)
	if(sudo[i][j][k]!=0)
	{
	ans=sudo[i][j][k];
	count++;
	}//if !=0
	if(count==1&&ans!=0){
	sudo[i][j][0]=ans;
	cout<<"Replaced ["<<i<<"]["<<j<<"]"<<endl;}
}
this->eliminate();
this->show();
}//update
/////////////////////////////////////////////////////////
void sudoku :: eliminate()
{
int m, n;
int val,sc,sr;
//normalizing
for(i=0;i<9;i++)
for(j=0;j<9;j++)
if(sudo[i][j][0]!=0)
{	val=sudo[i][j][0];
	//cout<<"Checking row\n";
	for(m=0;m<9;m++)  //row ko k lai laddu
	{
	if(sudo[i][m][0]==0)
	for(k=1;k<=9;k++)
	if(val==sudo[i][m][k]){
	//cout<<"Replaced value"<<sudo[i][m][k]<<endl;
	sudo[i][m][k]=0; }
	}
	//cout<<"Checking column"<<endl;
	for(n=0;n<9;n++)   //column ko k lai laddu
	{
	if(sudo[n][j][0]==0)
	for(k=1;k<=9;k++)
	if(val==sudo[n][j][k]){
	//cout<<"Replaced value"<<sudo[i][m][k]<<endl;
	sudo[n][j][k]=0;}
	}
	sr=3*(i/3);
	sc=3*(j/3);
	//cout<<"Checking small square\n";
	for(n=sr;n<(sr+3);n++)
	for(m=sc;m<(sc+3);m++)  //small square ko k lai laddu
	{
	if(sudo[n][m][0]==0)
	for(k=1;k<=9;k++)
	if(val==sudo[n][m][k]){
	//cout<<"Replaced value"<<sudo[n][m][k]<<endl;
	sudo[n][m][k]=0;}
	}
}//if
}//eliminate

//////////////////////////////////////////////////////////
void main()
{
clrscr();
sudoku s;
s.readfile();
s.solve();
int res=s.issolved();
s.show();
if(res==1)
cout<<"OH It is not solved........Try next time!\n";
else{
cout<<"CONGRATULATION YOU SOLVED IT !\n";
s.write();}
getch();
}