

#include<stdio.h>
#include<conio.h>
/////

FILE *Input_Fptr;
FILE *Output_Fptr;
int al[2];
int Input[30][8]={0};
int Fcfs[30][8]={0};
int Rr[30][8]={0};
int Psjf[30][8]={0};
int Nsjf[30][8]={0};
int Pp[30][8]={0};
int Row=0;
int Col=0;
int Total_Process;
int Total_Burst_ti;
int ti_Slice;
int Waiting[30][6]={0};
int Turnaround[30][6]={0};

void skip()
{
		for
		(int i=0 ; i<=9 ; i++)
	

}
//
voie skip2()
{
		for
		(int j=0 ; j<=9 ; j++)
}
//===================================================//
//             列出Turnaround ti    
//	      所有資料存在於Turnaround這個陣列中             
//===================================================//
void Show_Turnaround_ti()
{
	int row=0,col;
	fprintf(Output_Fptr,"\n============== Turnaround ti ================\n");
	fprintf(Output_Fptr,"     ID   FCFS     RR   PSJF   NSJF     PP\n");
	for(row=0;row<Row;row++)
	{
		fprintf(Output_Fptr,"%7d",row);
		for(col=1;col<=5;col++)
		{
				fprintf(Output_Fptr,"%7d",Turnaround[row][col]);
		}
		fprintf(Output_Fptr,"\n");
	}
}
//===================================================//
//             列出Waiting ti
//	      所有資料存在於Waiting這個陣列中
//===================================================//
void Show_Waiting_ti()
{
	int row=0,col;
	fprintf(Output_Fptr,"\n============= Waiting ti ====================\n");
	fprintf(Output_Fptr,"     ID   FCFS     RR   PSJF   NSJF     PP\n");
	for(row=0;row<Row;row++)
	{
		fprintf(Output_Fptr,"%7d",row);
		for(col=1;col<=5;col++)
		{
				fprintf(Output_Fptr,"%7d",Waiting[row][col]);
		}
		fprintf(Output_Fptr,"\n");
	}
}
//===================================================//
//             將各排程演算法的Turnaround ti存入Turnaround中
//===================================================//
void Turnaround_ti(int input[30][8],int col)
{
	int row;
	for(row=0;row<Row;row++)
	{
		Turnaround[row][0]=row;
		Turnaround[row][col]=input[row][6];
	}
}
//===================================================//
//             將各排程演算法的Waiting ti存入Waiting中
//===================================================//
void Waiting_ti(int input[30][8],int col)
{
	int row;
	for(row=0;row<Row;row++)
	{
		Waiting[row][0]=row;
		Waiting[row][col]=input[row][5];
	}
}
//===================================================//
//             複製陣列.....
//===================================================//
void Reload_Data()
{
	int row,col;
	for(row=0;row<Row;row++)
	{
		for(col=0;col<=4;col++)
		{
			Fcfs[row][col] = Input[row][col];
			Rr[row][col] = Input[row][col];
			Nsjf[row][col] = Input[row][col];
			Psjf[row][col] = Input[row][col];
			Pp[row][col] = Input[row][col];
		}
	}
}
//===================================================//
//             取得Burst ti
//===================================================//
int Get_Total_Burst_ti(int input[30][8])
{
	int i,count=0;
	for(i=0;i<Row;i++)
	{
		count += input[i][1];
	}
	return count;
}
//===================================================//
//             Show 資料
//		Show_Detail_Input(陣列)
//===================================================//
void Show_Detail_Input(int A[30][8])
{
	int i,j;
	clrscr();
	printf("\n=============== it's your Input ===============\n");
	printf("%7d %7d\n",al[0],al[1]);
	for(i=0;i<Row;i++)
	{
		for(j=0;j<=7;j++)
		{
				printf("%7d ",A[i][j]);
		}
		printf("\n");
	}
	printf("-- Detail -------------------------------------\n");
	printf("Algorithm: %d\n",A[0][0]);
	ti_Slice= A[0][1];
	printf("ti Slice: %d\n",A[0][1]);
	printf("Total Process: %d\n",Row);
	Total_Burst_ti = Get_Total_Burst_ti(Input);
	printf("Total Burst ti = %d\n",Total_Burst_ti);
}

void exchange(int i,int j,int input[30][8])
{
	int temp,k;
	for(k=0;k<=7;k++)
	{
		temp=input[i][k];
		input[i][k]=input[j][k];
		input[j][k]=temp;
	}
}
//===================================================//
//             排序資料
//		Sort_Data( 陣列  ,  排序標準之行   ,到第幾列
//===================================================//
void Sort_Data(int input[30][8],int k,int l,int m)
{
	int i,j;
	for(i=m;i<m+l;i++)
	{
		for(j=m;j<=i;j++)
		{
			if(input[i][k]<input[j][k])
			{
				exchange(i,j,input);
			}
			else if(input[i][k]==input[j][k])
			{
				if(input[i][2]<input[j][2])
					exchange(i,j,input);
				else if(input[i][2]==input[j][2])
					if(input[i][0]<input[j][0])
					exchange(i,j,input);
			}
		}
	}
}
void Sort_Data2(int input[30][8],int k,int l,int m)
{
	int i,j;
	for(i=m;i<=m+l;i++)
	{
		for(j=m;j<=i;j++)
		{
			if(input[i][k]<input[j][k])
			{
				exchange(i,j,input);
			}
		}
	}
}
void FCFS()
{
	int i=0,j,count=0,ti=0,check,output;
	Sort_Data(Fcfs,2,Row,0);
	ti = Get_Total_Burst_ti(Fcfs);
	ti += Fcfs[0][2];
	fprintf(Output_Fptr,"\n============== FCFS ================\n");
	while(count<=ti)
	{
		check=0;
		for(i=0;i<Row;i++)
		{
			if(Fcfs[i][2]<=count&&Fcfs[i][1]!=0)
			{
				output=i;
				check=1;
				Fcfs[i][1]--;
				break;
			}
		}
		if(check==1)
		{
			Sort_Data(Input,2,Row,0);
			Fcfs[output][5]=count-Input[output][1]-Fcfs[output][2]+1;
			Fcfs[output][6]=Input[output][1]+Fcfs[output][5];
			Sort_Data(Input,0,Row,0);
			if(Fcfs[output][0]<=9)
			{
				fprintf(Output_Fptr,"%d",Fcfs[output][0]);
			}
			else
				fprintf(Output_Fptr,"%c",Fcfs[output][0]+55);
		}
		else
		{
			fprintf(Output_Fptr,"-");
		}
		count++;

	}
	Sort_Data(Fcfs,0,Row,0);
	Waiting_ti(Fcfs,1);
	Turnaround_ti(Fcfs,1);
	fprintf(Output_Fptr,"\n");
}
void PP()
{
	int i=0,j,p=0,count=0,count2=0,count3=0,count4=0,ti=0,check,output,temp;
	Sort_Data(Pp,2,Row,0);
	ti = Get_Total_Burst_ti(Pp);
	ti += Pp[0][2];
	fprintf(Output_Fptr,"\n============== PP ===================\n");
	while(count<=ti)
	{
		check=0;
		count2=0;
		count3=0;
		count4=0;
		p=0;
		Sort_Data(Nsjf,2,Row,0);
		for(i=0;i<Row;i++)
		{
			if(Pp[i][2]<=count&&Pp[i][1]!=0&&Pp[i][7]==0)
			{
					Pp[i][7]=Pp[i][1];
			}
		}
		for(i=0;i<Row;i++)
		{
			if(Pp[i][7]>0)
			{
				count2++;
			}
		}
		Sort_Data(Pp,3,count2,0);
		for(i=0;i<count2;i++)
		{
			if(Pp[i][2]<=count&&Pp[i][1]!=0)
			{
				output=i;
				check=1;
				count3=Pp[i][1];
				break;
			}
		}
		for(i=output+1;i<count2;i++)
		{
			if(Pp[i][1] == Pp[output][1])
			{
				p++;
			}
		}
		if(p>0)
		{
			Sort_Data(Pp,3,p,output);
		}
		for(i=0;i<count2;i++)
		{
			if(Pp[i][2]<=count&&Pp[i][1]!=0)
			{
				output=i;
				check=1;
				count3=Pp[i][1];
				break;
			}
		}
		if(check==1)
		{
			Pp[output][5]=count-Pp[output][2];
			Pp[output][6]=Pp[output][7]+Pp[output][5];
			for(i=0;i<count3;i++)
			{
				if(Pp[output][0]<=9)
				{
					fprintf(Output_Fptr,"%d",Pp[output][0]);
				}
				else
					fprintf(Output_Fptr,"%c",Pp[output][0]+55);
				Pp[output][1]--;
				count++;
				for(i=0;i<Row;i++)
				{
					if(Pp[i][2]<=count&&Pp[i][1]!=0&&Pp[i][7]==0)
					{
						Pp[i][7]=Pp[i][1];
					}
				}
				for(i=0;i<Row;i++)
				{
					if(Pp[i][7]>0)
					{
						count4++;
					}
				}
				if(count2 != count4)
				{
					break;
				}
			}
		}
		else
		{
			count++;
			fprintf(Output_Fptr,"-");
		}
	}
	Sort_Data(Pp,0,Row,0);
	Waiting_ti(Pp,5);
	Turnaround_ti(Pp,5);
	fprintf(Output_Fptr,"\n");
}
//===================================================//
//             Open File, Read Data
//	      變數：
//			K：讀取進來的字元
//			row：行
//			col：列
//===================================================//
void File_Load()
{
	int k,row=0,col=0;
		
	char *Input_File_Path,*Output_File_Path;
	printf("Your Input File Name:");
	scanf("%s",Input_File_Path);
	Input_Fptr = fopen(Input_File_Path,"r");
	printf("Your Output File Name:");
	scanf("%s",Output_File_Path);
	Output_Fptr = fopen(Output_File_Path,"w");

	if(Input_Fptr!=NULL)
	{
		  while(!feof(Input_Fptr))
		  {
			fscanf(Input_Fptr,"%d",&k);
			if(row==0)
				//如果row為0，代表讀入為演算法的選擇以及ti Slice
				//存入Al陣列中
			{
				al[col]=k;
				col++;
				if(col==2)
				{
					row++;
				}
			}
			else
				//否則則為各process的資料
				//存入Input陣列中
			{
				Input[Row][Col]=k;
				Col++;
				if(Col>3)
				{
					Row++;
					Input[Row][4]=Row;
					Col=0;
				}
			}
		  }
	}
	else
	{
		fprintf(Output_Fptr,"Cannot Open File!!");
	}
}
void main()
{
	clrscr();
	File_Load();
		//讀取檔案的資料
	Show_Detail_Input(Input);
		//輸出獨進來的資料
	Reload_Data();
		//複製一份至各演算法所需的陣列中
	FCFS();
		//做FCFS演算法
//	RR();
	PSJF();
	NSJF();
	PP();
	Show_Waiting_ti();
		//列出所有的Waiting ti
	Show_Turnaround_ti();
		//列出所有的Turnaround ti
	fclose(Input_Fptr);
	fclose(Output_Fptr);
}