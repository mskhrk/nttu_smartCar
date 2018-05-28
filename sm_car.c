//sm_car.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//此函式庫沒有最上方的宣告所以子函數需要放在上方

/*
halfMapCreat半地圖生成(7方向)
使用說明
使用車上的伺服馬達對指定方向直接取得距離
此函式功能在於處理伺服馬達掃描完後取得的數據
須提供掃描的數量，進行相應次數的讀取
計算平均去除極值，回傳各方向距離

參數說明
*map_data		外部資料輸入
*map 			外部存放位置
allData		資料總筆數
scanTime		一次掃描數量
*/
void halfMapCreat(int *map_data,int *map,int allData,int scanTime)

{
	int i;
	int average=0;
	int newAverage=0;
	int count=0;
	
	if(1== allData)//單方向掃描(如果多方向掃描執行到這個會出錯) J2模式單一方向
	{

		map[0]=map_data[0];
		average=0;
		newAverage=0;
		count=0;
	}
	
	//多方向掃描 J1模式多方向
	else{
	//計算角度22
	for(i=0;i<=(scanTime-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=0;i<=(scanTime-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[0]=0;}
	else
	{map[0]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;
	
	//計算角度44
	for(i=scanTime;i<=(scanTime*2-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=scanTime;i<=(scanTime*2-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[1]=0;}
	else
	{map[1]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;

	//計算角度66
	for(i=scanTime*2;i<=(scanTime*3-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=scanTime*2;i<=(scanTime*3-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[2]=0;}
	else
	{map[2]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;
	
	//計算角度88
	for(i=scanTime*3;i<=(scanTime*4-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=scanTime*3;i<=(scanTime*4-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[3]=0;}
	else
	{map[3]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;
	
	//計算角度110
	for(i=scanTime*4;i<=(scanTime*5-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=scanTime*4;i<=(scanTime*5-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[4]=0;}
	else
	{map[4]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;
	
	//計算角度132
	for(i=scanTime*5;i<=(scanTime*6-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=scanTime*5;i<=(scanTime*6-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[5]=0;}
	else
	{map[5]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;

	
	//計算角度154
	for(i=scanTime*6;i<=(scanTime*7-1);i++)
	{
		average+=map_data[i];
	}
	average=average/scanTime;
	for(i=scanTime*6;i<=(scanTime*7-1);i++)
	{
		if(average-map_data[i]>30||average-map_data[i]<-30){}
		else
		{
			newAverage+=map_data[i];
			count++;
		}

	}
	if(count==0){map[6]=0;}
	else
	{map[6]=newAverage/count;}
	average=0;
	newAverage=0;
	count=0;
	}
}



void uart_send_command(char *command)

{
	
	int fd;
	int out=0;
	int nread;
	char buff[10];
	char *dev ="/dev/ttyPS1";
	fd = OpenDev(dev);
	FILE *fp;//write file
	int b;
	int count=0;
	
	//uart 設定 star
	if (fd>0)set_speed(fd,9600);
	else
	{
		printf("Can't Open Serial Port!\n");
		exit(0);
	}
	if (set_Parity(fd,8,1,'N')== 0)
	{
		printf("Set Parity Error\n");
		exit(1);
	}
	//uart 設定 over
	
	system(command);

	fp = fopen("data1.txt","w+");
	nread=read(fd,buff,9);
	while(nread<=0){nread=read(fd,buff,9);sleep(1);system(command);}
	while(nread > 0 )
	{
		buff[nread]='\0'; 
		fprintf(fp,"%s",buff);
		for(b=0;b<10;b++){
			if(buff[b]==59)out=1;
		}
		if(out==1){close(fd);break;}
		nread=read(fd,buff,9);
	}
	fclose(fp);
}

void uart_send_command2(char *command,char *fileName,char *fileMode)

{
	
	int fd;
	int out=0;
	int nread;
	char buff[10];
	char *dev ="/dev/ttyPS1";
	fd = OpenDev(dev);
	FILE *fp;//write file
	int b;
	int count=0;
	
	//uart 設定 star
	if (fd>0)set_speed(fd,9600);
	else
	{
		printf("Can't Open Serial Port!\n");
		exit(0);
	}
	if (set_Parity(fd,8,1,'N')== 0)
	{
		printf("Set Parity Error\n");
		exit(1);
	}
	//uart 設定 over
	
	system(command);
	fp = fopen(fileName,fileMode);//fileMode w+複寫 a+向下增加
	nread=read(fd,buff,9);
	while(nread > 0 )
	{
		buff[nread]='\0'; 
		fprintf(fp,"%s",buff);
		for(b=0;b<10;b++){
			if(buff[b]==59)out=1;
		}
		if(out==1){close(fd);break;}
		nread=read(fd,buff,8);
	}
	fclose(fp);
}


int fixfile()
{
	FILE *infile;
	FILE *outfile;
	int  i;
	int  nread;
	int  f1=0;//#
	int  f2=0;//" "
	int  f3=0;//-
	int  f4=0;//-
	int  f5=0;//;
	int a;
	float average;
	char buff[10];
	infile = fopen("data1.txt","r+");     /* open file pointer */
	outfile = fopen("data2.txt","w+");
	
	int overNum=0;
	int overNum2=0;
	int overNum3=0;
	int overf1=0;
	
	
	while(f5 == 0 )
	{
		
		
		for(i=0;i<10;i++){				
			buff[i]=getc(infile);
			//printf("%d\n",buff[i]);
			switch(buff[i]){
				
				case '#':
				f1=1;
				break;
				
				case ' ':
				if(f1==1)f2=1;
				break;
				
				case '-':
				if(f3==1)
				{
					nread=putc(buff[i],outfile);
					nread=putc(10,outfile);
					f1=0;f2=0;f3=0;f4=0;
					overNum3=overNum2;
					overNum2=overNum;
					overNum=0;overf1=0;				
				}
				else{
					if(f2==1)f3=1;
				}
				break;
				
				case ';':
				f5=1;
				nread=putc(59,outfile);
				break;
			}
			if(f1==1&&f2==0&&buff[i]!=35)
			{
				//printf("%d\n",buff[i]-48);
				if(overf1==0)overNum+=(buff[i]-48);
				else
				{
					if(overf1==1){overNum=overNum*10;overNum+=(buff[i]-48);}
					if(overf1==2){overNum*=10;overNum+=(buff[i]-48);}
					if(overf1==3){overNum*=10;overNum+=(buff[i]-48);}
				}
				overf1++;
			}
			
			if(f1==1){nread=putc(buff[i],outfile);}
		}
		//if(f5==1){f5=0;break;}
		
	}
	//printf("%d\n",overNum3);
	fclose(infile);
	fclose(outfile);
	return overNum3;	  
}




int checkDataExist(char *datafile)
{
	FILE *infile;
	infile = fopen(datafile,"a+");
	int  i,r=0;
	int  f1=0;//s
	int  f2=0;//t
	int  f3=0;//a
	int  f4=0;//r
	char buff[10];
	
	while(f4 == 0 )
	{
		
		
		for(i=0;i<10;i++){				
			buff[i]=getc(infile);
			switch(buff[i]){
				
				case 's':
				f1=1;
				break;
				
				case 't':
				if(f1==1)f2=1;
				break;
				
				case 'a':
				if(f2==1)f3=1;
				break;
				
				case 'r':
				if(f3==1)
				{f4=1;
				return 1;}
				break;
				default :
				f1=0;f2=0;f3=0;f4=0;
			}
		}
		if(f4==0)r++;
		if(r>10)break;
	}
	fclose(infile);
	return 0;
	
}




void load_data(int *map,int allData)
//從data2載入所有數值到記憶體
//*map 		外部存放中間
//allData	輸入的總數量
{
	FILE *infile;
	//FILE *outfile;
	int  i;
	int  nread;
	int  f1=0;//#
	int  f2=0;//" "
	int  f3=0;//-
	int  f4=0;//-
	int  f5=0;//;
	//int a;
	//float average;
	char buff[10];
	infile = fopen("data2.txt","r");     /* open file pointer */
	//outfile = fopen("data2.txt","w+");
	
	int overNum=0;
	//int overNum2=0;
	//int overNum3=0;
	int overf1=0;
	
	//int allData=50;
	int *map_data = calloc(allData, sizeof(int));
	int data_counter=0;
	
	
	while(f5 == 0 )
	{
		
		
		for(i=0;i<10;i++){				
			buff[i]=getc(infile);
			//printf("%d\n",buff[i]);
			switch(buff[i]){
				
				case '#':
				f1=1;
				break;
				
				case ' ':
				if(f1==1)f2=1;
				break;
				
				case '-':
				if(f3==1)
				{
					//nread=putc(buff[i],outfile);
					//nread=putc(10,outfile);
					f1=0;f2=0;f3=0;f4=0;
					if(overNum<1000){//去除star&over 因為算出來的值剛好很大
						map_data[data_counter]=overNum;
					data_counter++;}
					overNum=0;overf1=0;				
				}
				else{
					if(f2==1)f3=1;
				}
				break;
				
				case ';':
				f5=1;
				break;
			}
			if(f1==1&&f2==1&&f3==1&&f4==0&&buff[i]!=45)
			{
				//printf("%d\n",buff[i]-48);
				if(overf1==0)overNum+=(buff[i]-48);
				else
				{
					if(overf1==1){overNum=overNum*10;overNum+=(buff[i]-48);}
					if(overf1==2){overNum*=10;overNum+=(buff[i]-48);}
					if(overf1==3){overNum*=10;overNum+=(buff[i]-48);}
				}
				overf1++;
			}
			
			//if(f1==1){nread=putc(buff[i],outfile);}
		}
		//if(f5==1){f5=0;break;}
		
	}
	//printf("%d\n",overNum3);
	fclose(infile);
	for(data_counter=0;data_counter<allData;data_counter++)	
	{
		
		map[data_counter]=map_data[data_counter];
	}
	//fclose(outfile);	  
}

//比較兩筆地圖資料找出開頭點
//用於判斷相同點不同的排序順序
//可用於判斷面相位置
int oneCircleTest2(int *map1Data,int *map2Data)
{
	//取樣24方位	
		
	int  map1[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int  map2[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
	int  data_difference[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
	int i,q,tem,total=0,minNum;
	
	for(q=0;q<=23;q++)//導入外部值
	{
		map1[q]=map1Data[q];
		map2[q]=map2Data[q];
	}
	for(q=0;q<=23;q++)
	{	for(i=0;i<=23;i++)
		{
			tem=map1[i]-map2[i];
			if(tem<0){tem=tem*-1;}
			total+=tem;
		}
		data_difference[q]=total;
		tem=map1[0];
		for(i=0;i<=22;i++)//map1向前換位
		{
			map1[i]=map1[i+1];
		}
		map1[23]=tem;
		total=0;

	}
	for(q=0;q<=23;q++)//找最小值
	{
		if(q==0){minNum=data_difference[0];tem=0;}
		if(data_difference[q]<minNum)
		{
			minNum=data_difference[q];
			tem=q;
			}	
	}
	printf("min=%d num=%d\n",minNum,tem);
	return tem;
}

//oneCircleTest2的任意大小版本上限24
int oneCircleTest3(int *map1Data,int *map2Data ,int size)
{
	//	map1Data 比較資料(換位)
	//	map2Data 比較資料(固定)
	//	size	 比較陣列長度(最高24)
	
	int  map1[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int  map2[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
	int  data_difference[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
	int i,q,tem,total=0,minNum;
	
	for(q=0;q<=(size-1);q++)//導入外部值
	{
		map1[q]=map1Data[q];
		map2[q]=map2Data[q];
	}
	for(q=0;q<=(size-1);q++)
	{	for(i=0;i<=(size-1);i++)
		{
			tem=map1[i]-map2[i];
			if(tem<0){tem=tem*-1;}
			total+=tem;
		}
		data_difference[q]=total;
		tem=map1[0];
		for(i=0;i<=(size-2);i++)//map1向前換位
		{
			map1[i]=map1[i+1];
		}
		map1[size-1]=tem;
		total=0;

	}
	for(q=0;q<=(size-1);q++)//找最小值
	{
		if(q==0){minNum=data_difference[0];tem=0;}
		if(data_difference[q]<minNum)
		{
			minNum=data_difference[q];
			tem=q;
			}	
	}
	printf("min=%d num=%d\n",minNum,tem);
	return tem;
}

	
char* modeG(int n1,int n2,int n3,int n4)
{
	static char a[200]="echo \"G";//使用static多次執行modeG可能會有問題 需清除上一次內容
	strcpy(a,"");//清除上一次內容
	a[0]='e';a[1]='c';a[2]='h';a[3]='o';a[4]=' ';a[5]='"';a[6]='G';
	char b[5];
	char c[2]=" ";
	char d[10];
	char e[10];
	char f[10];
	char g[100]=";\" > /dev/ttyPS1";//6sec 150cm
	
	//_itoa(n1,b,10);
	//_itoa(n2,d,10);
	//_itoa(n3,e,10);
	//_itoa(n4,f,10);
	sprintf(b, "%d", n1);
	sprintf(d, "%d", n2);
	sprintf(e, "%d", n3);
	sprintf(f, "%d", n4);
	
	strcat(a, b);
	strcat(a, c);
	strcat(a, d);
	strcat(a, c);
	strcat(a, e);
	strcat(a, c);
	strcat(a, f);
	strcat(a, g);
	printf("\n %s",a);
	return a;
}

void modeH(int n1,int n2,int n3,int n4,int n5)
{
	char a[200]="echo \"H";
	char b[5];
	char c[2]=" ";
	char d[10];
	char e[10];
	char f[10];
	char g[10];
	char h[100]=";\" > /dev/ttyPS1";
	
	//_itoa(n1,b,10);
	//_itoa(n2,d,10);
	//_itoa(n3,e,10);
	//_itoa(n4,f,10);
	
	sprintf(b, "%d", n1);
	sprintf(d, "%d", n2);
	sprintf(e, "%d", n3);
	sprintf(f, "%d", n4);
	sprintf(g, "%d", n5);
	
	
	strcat(a, b);
	strcat(a, c);
	strcat(a, d);
	strcat(a, c);
	strcat(a, e);
	strcat(a, c);
	strcat(a, f);
	strcat(a, c);
	strcat(a, g);
	strcat(a, h);
	printf("\n %s",a);
	system(a);
	
}
void set_map(char *fileName,int x,int y,int *vector,int id)
//#id -X-Y-vector[0]-vector[1]-vector[2]-vector[3]-vector[4]-vector[5]-vector[6]-
{

	FILE *map1;
	FILE *mapTem;
	//map1 = fopen(fileName,"a+");
	mapTem = fopen("mapTem.txt","w+");//fileMode w+複寫 a+向下增加
	
	char buff[10];
	char buff2[50];
	int f1=0;//紀錄是否為#
	int f2=0;//紀錄是否為#0項
	int f3=0;//紀錄-出現的次數
	int f4=0;//可以開始寫入的訊號
	int f5=0;//讀到';'
	int f6=0;//把buff2暫存輸出到mapTem
	int buff2Counter =0;//紀錄buff2目前位置
	int i,q;//for計數器
	if(checkDataExist(fileName)==0)//檔案沒有起始項
	{
		map1 = fopen(fileName,"a+");
		fprintf(map1,"#0 -star-\n");//加入起始項
		fprintf(map1,"#0 -over-;");
		fclose(map1);//在if裡面開就要在if中關閉	
	}
	
	map1 = fopen(fileName,"r");
		
	//#0 -star-
	//#1 -10-10-10-10-10-10-10-10-10-
	while(f5 == 0 )
	{
		for(i=0;i<10;i++){				

			buff[i]=getc(map1);
			
			switch(buff[i]){
				case '#':
				f1=1;
				break;
				
				case '0':
				if(f1==1){f1=0;f2=1;}//清除f1以免之後數值0干擾
				break;				
				
				case '-':
				f3++;
				
				if(f2==1&&f3==2)
				{
					buff[i]=getc(map1);
					if(buff[i]==';'){f5=1;}
					else{
							f1=0;
							f2=0;
							f3=0;
							f4=1;
							buff[i]=getc(map1);//讀去#0項後的下一筆
					}
								
				}
				if(f3==10)
				{
					f6=1;
				}
				break;
				
				case ';':
				f5=1;
				break;
				
				default:
				f1=0;//清除f1以免之後數值0干擾
			}
			
			if(f5==1)break;
			
			if(f4==1)
			{
				buff2[buff2Counter]=buff[i];
				buff2Counter++;
				if(buff2Counter>50){printf("buff2Counter error");}
				}
				
			if(f6==1)
			{
				for(q=0;q<buff2Counter;q++)//q的數值與buff2Counter多1關系已考慮
				{
					fprintf(mapTem,"%c",buff2[q]);
				}
				f1=0;
				f3=0;
				f6=0;
				buff2Counter=0;			
			}
		}	
	}
		fprintf(mapTem,";");
		fclose(map1);
		fclose(mapTem);

	
		map1 = fopen(fileName,"w+");
		mapTem = fopen("mapTem.txt","r");
		fprintf(map1,"#0 -star-\n");//加入起始項
		
		//寫入新資料
		fprintf(map1,"#%d -",id);
		fprintf(map1,"%d-",x);
		fprintf(map1,"%d-",y);
		fprintf(map1,"%d-",vector[0]);
		fprintf(map1,"%d-",vector[1]);
		fprintf(map1,"%d-",vector[2]);
		fprintf(map1,"%d-",vector[3]);
		fprintf(map1,"%d-",vector[4]);
		fprintf(map1,"%d-",vector[5]);
		fprintf(map1,"%d-\n",vector[6]);
		
		//導入舊資料
		do
		{
			buff[0]=getc(mapTem);
			if(buff[0]!= ';')fprintf(map1,"%c",buff[0]);
		}while(buff[0]!= ';');
		
		fprintf(map1,"\n#0 -over-;");//加入結束項
		
		fclose(map1);
		fclose(mapTem);
}


int get_map(char *fileName,int *vector,int id)
//使用id找資料，如果找完全部檔案沒有return 0
{
	FILE *map1;
	int buff;
	int f1=0;//紀錄是否為#
	int f2=0;//紀錄是否為id1
	int f3=0;//紀錄是否為id2
	int f4=0;//紀錄是否為id3
	int f5=0;//紀錄是否為id4
	int f6=0;//紀錄是否為id結束空白
	int id1,id2,id3,id4,idc=0;//idc計算id位數
	int outid;
	
	int i=0;//for迴圈計數器
	int overf1=0;//計算進位數
	
	outid =id;
	id1=outid%10;
	id2=(outid/10)%10;
	id3=(outid/100)%10;
	id4=(outid/1000)%10;
	
	//vector初始化
	for(i=0;i<9;i++)
	{
		vector[i]=0;
	}
		if(checkDataExist(fileName)==0){printf("map not exist or no stat data\n");return 0;}//檔案沒有起始項
	
	if(id1>0)idc=1;
	if(id2>0)idc=2;
	if(id3>0)idc=3;
	if(id4>0)idc=4;
	if(idc==0){printf("id=%d is error",id);return 0;}
	map1 = fopen(fileName,"r");
	do
	{
		buff=getc(map1);
		if(buff=='#'){f1=1;}
		
		switch(idc){
				case 1:			
				if(f1==1)
				{
					buff=getc(map1);
					if(id1==(buff-48))
					{
						buff=getc(map1);
						if(buff==' '){
							/*執行輸出外部值並return id*/
							//#1 -10-10-10-10-10-10-10-10-10-
							for(i=0;i<10;)
							{
								buff=getc(map1);
								if(buff=='-'){i++;overf1=0;}
								else
								{
									if(overf1==0){vector[i-1]+=(buff-48);}
									else
									{
										if(overf1==1){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
										if(overf1==2){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
										if(overf1==3){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
									}
									overf1++;
								}
								
							}
							return outid;
							}
						else{f1=0;}
					}
					else{f1=0;}
				}
				break;
				
				case 2:
				if(f1==1)
				{
					buff=getc(map1);
					if(id2==(buff-48))
					{
						buff=getc(map1);
						if(id1==(buff-48))
						{
							buff=getc(map1);
							if(buff==' '){
							/*執行輸出外部值並return id*/
							for(i=0;i<10;)
							{
								buff=getc(map1);
								if(buff=='-'){i++;overf1=0;}
								else
								{
									if(overf1==0){vector[i-1]+=(buff-48);}
									else
									{
										if(overf1==1){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
										if(overf1==2){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
										if(overf1==3){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
									}
									overf1++;
								}
								
							}
							return outid;
							}
							else{f1=0;}
							break;
						}
						else{f1=0;}
					}
					else{f1=0;}
				}
				break;
				
				case 3:
				if(f1==1)
				{
					buff=getc(map1);
					if(id3==(buff-48))
					{
						buff=getc(map1);
						if(id2==(buff-48))
						{
							buff=getc(map1);
							if(id1==(buff-48))
							{
								buff=getc(map1);
								if(buff==' '){
								/*執行輸出外部值並return id*/
								for(i=0;i<10;)
							{
								buff=getc(map1);
								if(buff=='-'){i++;overf1=0;}
								else
								{
									if(overf1==0){vector[i-1]+=(buff-48);}
									else
									{
										if(overf1==1){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
										if(overf1==2){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
										if(overf1==3){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
									}
									overf1++;
								}
								
							}
							return outid;
								}
								else{f1=0;}
								break;
							}
							else{f1=0;}
							break;
						}
						else{f1=0;}
						break;
					}
					else{f1=0;}
				}
				break;
				
				case 4:
				if(f1==1)
				{
					buff=getc(map1);
					if(id4==(buff-48))
					{
						buff=getc(map1);
						if(id3==(buff-48))
						{
							buff=getc(map1);
							if(id2==(buff-48))
							{
								buff=getc(map1);
								if(id1==(buff-48))
								{	
									buff=getc(map1);
									if(buff==' '){
										/*執行輸出外部值並return id*/
										for(i=0;i<10;)
										{
											buff=getc(map1);
										if(buff=='-'){i++;overf1=0;}
										else
										{
											if(overf1==0){vector[i-1]+=(buff-48);}
											else
											{
												if(overf1==1){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
												if(overf1==2){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
												if(overf1==3){vector[i-1]=vector[i-1]*10;vector[i-1]+=(buff-48);}
											}
											overf1++;
										}
								
									}
										return outid;
										}
									else{f1=0;}
									break;
									
								}
								else{f1=0;}
								break;
							}
							else{f1=0;}
							break;
						}
						else{f1=0;}
						break;
					}
					else{f1=0;}
				}
				break;
		}
	}while(buff != ';');
	fclose(map1);
	return 0;
}

//整合modeJ 將目前xy的外部掃描寫入地圖
void scanXY(int map_x,int map_y,int map_id)
{
	int  map_point[7]={0,0,0,0,0,0,0};
	int allData;
	/*輸入探測指令、接收回傳資料、寫入檔案scanData.map*/
	char *a="echo \"J1 22 154 22 10 12000;\" > /dev/ttyPS1";
	
	//printf("%s\n",a);
	uart_send_command(a);
	
	allData=fixfile();//自動計算回傳總筆數
	
	int *map_data = calloc(allData, sizeof(int));//建立一個空間中資料
	
	load_data(map_data,allData);//檔案值載入記憶體
	
	halfMapCreat(map_data,map_point,allData,10);//map_point中取得外部資料 J1 22 154 22 10 12000 的10
		
	//將資料加上ID寫入地圖
	set_map("car.map",map_x,map_y,map_point,map_id);//第1筆id = 1 x = 0 y = 0
}

void scanXY2(int map_x,int map_y,int map_id ,int direction)
//依照方位進行寫入
//x:x座標 y:y座標 map_id:存在地圖的序號 direction:這次面相的方向(1~4)(北東南西)
{
	int  map_point[7]={0,0,0,0,0,0,0};//新掃描數值資料
	int  map_point2[7]={0,0,0,0,0,0,0};//舊地圖暫存
	int  map_point3[9]={0,0,0,0,0,0,0,0,0};//getmap用空間
	int allData;
	/*輸入探測指令、接收回傳資料、寫入檔案scanData.map*/
	//char *a="echo \"J1 22 154 22 10 12000;\" > /dev/ttyPS1";
	char *a="echo \"J1 60 120 10 10 12000;\" > /dev/ttyPS1";
	
	
	//printf("%s\n",a);
	uart_send_command(a);
	
	allData=fixfile();//自動計算回傳總筆數
	
	int *map_data = calloc(allData, sizeof(int));//建立一個空間中資料
	
	load_data(map_data,allData);//檔案值載入記憶體
	
	halfMapCreat(map_data,map_point,allData,10);//map_point中取得外部資料 J1 22 154 22 10 12000 的10
	
	get_map("car.map",map_point3,map_id);
	
	//map3 去除 x y 格式編號 放入 map2
	map_point2[1]=map_point3[3];
	map_point2[2]=map_point3[4];
	map_point2[3]=map_point3[5];
	map_point2[4]=map_point3[6];
	map_point2[5]=map_point3[7];
	map_point2[6]=map_point3[8];
	
	if(map_point[0]>70&&map_point[1]>70&&map_point[2]>70&&map_point[3]>70&&map_point[4]>70&&map_point[5]>70&&map_point[6]>70)
	//所有都超過70cm
	{
		switch(direction)
		{
			case 1:
			map_point2[1]=1;
			break;
			
			case 2:
			map_point2[2]=1;
			break;
			
			case 3:
			map_point2[3]=1;
			break;
			
			case 4:
			map_point2[4]=1;
			break;
		}
	}
	else
	{
		switch(direction)
		{
			case 1:
			map_point2[1]=0;
			break;
			
			case 2:
			map_point2[2]=0;
			break;
			
			case 3:
			map_point2[3]=0;
			break;
			
			case 4:
			map_point2[4]=0;
			break;
		}
	}
	//#序號 -X-Y-格式-北-東-南-西-預留-預留-
	map_point2[0]=999;//設定999為此種格式
		
	//將資料加上ID寫入地圖
	set_map("car.map",map_x,map_y,map_point2,map_id);//第1筆id = 1 x = 5000 y = 5000
}



void initScanXY(int map_x,int map_y,int map_id)
{
	int  map_point[7]={0,0,0,0,0,0,0};
	int allData;
	/*輸入探測指令、接收回傳資料、寫入檔案scanData.map*/
	char *a="echo \"J2 90 7 12000;\" > /dev/ttyPS1";
	
	//printf("%s\n",a);
	uart_send_command(a);
	
	allData=fixfile();//自動計算回傳總筆數
	
	int *map_data = calloc(allData, sizeof(int));//建立一個空間中資料
	
	load_data(map_data,allData);//檔案值載入記憶體

	halfMapCreat(map_data,map_point,allData,7);//map_point中取得外部資料
		
	//將資料加上ID寫入地圖
	set_map("car.map",map_x,map_y,map_point,map_id);//第1筆id = 1 x = 0 y = 0
}

//依照目標與現有資訊進行移動命令
//面向方向、目前
//id 方向轉換

int goTarget(char *fileName,int direction,int nowId,int nextId)
{
	int targetDirection;
	int circle;//正(逆時鐘) 負(順時鐘)
	char *c1="echo \"K1 90;\" > /dev/ttyPS1";//右順90
	char *c2="echo \"K2 90;\" > /dev/ttyPS1";//左逆90
	char *c3="echo \"K1 180;\" > /dev/ttyPS1";//右順180
	char *c4="echo \"A11\" > /dev/ttyPS1";//直1格
	
	targetDirection=id2direction(fileName,nowId,nextId);
	circle=direction-targetDirection;
	if(circle==3){circle=-1;}
	if(circle==-3){circle=1;}
	if(circle==1){
		system(c2);
		sleep(3);
	}
	if(circle==-1){
		system(c1);
		sleep(3);
	}
	if(circle==2||circle==-2){
		system(c3);
		sleep(3);
	}
	system(c4);
	sleep(3);
	return targetDirection;
}

int id2direction(char *fileName,int star,int end)
{
	int  map_point_star[9]={0,0,0,0,0,0,0,0,0};
	int checkEmpty;
	checkEmpty=get_map(fileName,map_point_star,star);
	if(checkEmpty==0)
	{
		printf("star id can't find error\n");
		return 0;
	}
	if(end==map_point_star[3]){return 1;}
	if(end==map_point_star[4]){return 2;}
	if(end==map_point_star[5]){return 3;}
	if(end==map_point_star[6]){return 4;}

	return 0;
}


void addSecPoint(int add,int *secPoint,int size)
//add想要加入的點
//secPoint存放第2備援點的陣列
//size存放第2備援點的陣列的大小
{
	//先檢查是否已經有此點存在
	int i,noSame=0;
	if(add!=0){
		for(i=0;i<size;i++)
		{
			if(secPoint[i]==add)noSame++;
		}
		//所有點往後移動(如果移動次數超過size會導致資料遺失)
		//如果超過size時需增大secPoint的大小
		//size等於地圖大小時不會有上述問題發生
		if(noSame==0)
		{
			for(i=size-1;i>0;i--)
			{
				secPoint[i]=secPoint[i-1];
			}
			secPoint[0]=add;
		}
	}
}

void delSecPoint(int del,int *secPoint,int size)
//del想要刪除的點
//secPoint存放第2備援點的陣列
//size存放第2備援點的陣列的大小
//想要刪除的點不存在時不做任何動作
{
	//先檢查是否已經有此點存在，並記錄位置
	int i,Same=-1;
	for(i=0;i<size;i++)
	{
		if(secPoint[i]==del)Same=i;
	}

	if(Same!=-1)
	{
		for(i=Same;i<size-1;i++)
		{
			secPoint[i]=secPoint[i+1];
		}
	}
}


void getSecPoint(int ans,int *pointx4,int *CM_passPoint,int CM_passPointSize,int *secPoint,int secPointSize)
{
	if(ans!=0){
		//先確認是否在過去走過的路上出現過，沒有就加入
		int i,ok0=1,ok1=1,ok2=1,ok3=1;
		for(i=0;i<CM_passPointSize;i++)
		{
			if(pointx4[0]==CM_passPoint[i]||pointx4[0]==0)ok0=0;
			if(pointx4[1]==CM_passPoint[i]||pointx4[1]==0)ok1=0;
			if(pointx4[2]==CM_passPoint[i]||pointx4[2]==0)ok2=0;
			if(pointx4[3]==CM_passPoint[i]||pointx4[3]==0)ok3=0;
		}
		if(ok0==1)addSecPoint(pointx4[0],secPoint,secPointSize);
		if(ok1==1)addSecPoint(pointx4[1],secPoint,secPointSize);
		if(ok2==1)addSecPoint(pointx4[2],secPoint,secPointSize);
		if(ok3==1)addSecPoint(pointx4[3],secPoint,secPointSize);
		
		//刪除CM_passPoint的ans(是ans就不是備援)
		delSecPoint(ans,secPoint,secPointSize);
	}
}


//取得4方位連結點
int nextLink(char *fileName,int *pointx4,int id,int direction)
//fileName地圖檔
//pointx4存放4個方位的連結
//id要檢測的點
//direction目標絕對方向 1~4北東南西
{
	int  map_point[9]={0,0,0,0,0,0,0,0,0};
	int	 checkEmpty;
	checkEmpty=get_map(fileName,map_point,id);
	if(checkEmpty==0)
	{
		printf("This id can't find error");
		return 0;
	}
	pointx4[0]=map_point[3];
	pointx4[1]=map_point[4];
	pointx4[2]=map_point[5];
	pointx4[3]=map_point[6];
	
		switch(direction)
	{
		case 0://單純使用pointx4存放4個方位的連結功能
		return 0;
		break;
		
		case 1:
		return map_point[3];
		break;
		
		case 2:
		return map_point[4];
		break;
		
		case 3:
		return map_point[5];
		break;
		
		case 4:
		return map_point[6];
		break;
	}
}


int nextPoint(char *fileName,int goDirection1,int goDirection2,int nowPoint)
//回傳下一個目標點
//回傳0表示沒有下一個目標點
//只檢測目標方向
{
	int pointx4[4]={0,0,0,0};
	int ans;
	if(goDirection1!=0)
	{
		ans=nextLink(fileName,pointx4,nowPoint,goDirection1);
		if(ans==0)
		{
			ans=nextLink(fileName,pointx4,nowPoint,goDirection2);
			return ans;
		}
		return ans;
	}
	else
	{
		ans=nextLink(fileName,pointx4,nowPoint,goDirection2);
		return ans;
	}
	
}


int planPoint(char *fileName,int goDirection1,int goDirection2,int starPoint,int *secPoint)
//第二路徑起點secendPoint
//前一點previousPoint
//備援點secPoint
{
	
	int ans;
	int pointx4[4]={0,0,0,0};
	int newDirection1,newDirection2;
	int secPoint_i=0;
	extern int CM_passPoint[50];
	extern int CM_passPointSize;
	extern int CM_secPoint[50];
	extern int CM_secPointSize;
	ans=nextPoint(fileName,goDirection1,goDirection2,starPoint);
	nextLink(fileName,pointx4,starPoint,0);
	getSecPoint(ans,pointx4,CM_passPoint,CM_passPointSize,CM_secPoint,CM_secPointSize);

	if(ans==0)//目標方向檢測不到換方向
	{
		if(goDirection1==1){
		newDirection1=3;
		}
		else{
		newDirection1=1;
		}
		ans=nextPoint(fileName,newDirection1,goDirection2,starPoint);
		getSecPoint(ans,pointx4,CM_passPoint,CM_passPointSize,CM_secPoint,CM_secPointSize);
	}
	
	if(ans==0)//目標方向檢測不到換方向
	{
		if(goDirection2==2){
		newDirection2=4;
		}
		else{
		newDirection2=2;
		}
		ans=nextPoint(fileName,goDirection1,newDirection2,starPoint);
		getSecPoint(ans,pointx4,CM_passPoint,CM_passPointSize,CM_secPoint,CM_secPointSize);
		if(ans==0)printf("起始點即是目標or目標無法到達");
		return 0;
	}
	return ans;
}

int findPath(char *fileName,int star,int end,int *secPoint,int *passPoint)
{
	int  map_point_star[9]={0,0,0,0,0,0,0,0,0};
	int  map_point_end[9]={0,0,0,0,0,0,0,0,0};
	int  map_point_tem[9]={0,0,0,0,0,0,0,0,0};
	int  pointx4[4]={0,0,0,0};
	int checkEmpty;
	int goDirection1;//目標絕對方向無=0 北=1 南=3(最終結果)
	int goDirection2;//目標絕對方向無=0 東=2 西=4(最終結果)
	int distance1,distance2;//目標絕對方向的距離
	int prePoint,nowPoint;
	int passPointNum=1,psi=1,passCount=0;//psi起始不能檢測，因為planPoint要用現在位置推算下一筆
	extern int CM_secPointSize;
	checkEmpty=get_map(fileName,map_point_star,star);
	if(checkEmpty==0)
	{
		printf("star id can't find error\n");
		return 0;
	}
	checkEmpty=get_map(fileName,map_point_end,end);
	if(checkEmpty==0)
	{
		printf("end id can't find error\n");
		return 0;
	}
	goDirection1=map_point_star[1]-map_point_end[1];
	goDirection2=map_point_star[0]-map_point_end[0];
	if(goDirection1>0)
		{
			distance1=goDirection1;
			goDirection1=3;
		}
	if(goDirection1<0)
		{
			distance1=goDirection1*-1;
			goDirection1=1;
		}
	if(goDirection2>0)
		{
			distance2=goDirection2;
			goDirection2=4;
		}
	if(goDirection2<0)
		{
			distance2=goDirection2*-1;
			goDirection2=2;	
		}
	if(goDirection1==0&&goDirection2==0)return 0;
	
	
	//檢測是否有走過
	int newStar;
	newStar=planPoint(fileName,goDirection1,goDirection2,star,secPoint);
	do
	{
		passPointNum=passPoint[psi];
		if(passPointNum==0)break;//第一筆不用檢測
		if(newStar==passPointNum)//過去走過
		{
			
			
			passCount++;
			if(passCount==1)
			{
				newStar=nextLink(fileName,pointx4,passPoint[0],2);//passPoint[0]拿上一次的去比較
				if(newStar==0)passCount++;
			}
			if(passCount==2)
			{
				newStar=nextLink(fileName,pointx4,passPoint[0],4);
				if(newStar==0)passCount++;
			}
			if(passCount==3)
			{
				newStar=nextLink(fileName,pointx4,passPoint[0],3);
				if(newStar==0)passCount++;
			}
			if(passCount==4)
			{
				newStar=nextLink(fileName,pointx4,passPoint[0],1);
				if(newStar==0)passCount++;
			}
			if(passCount==5)
			{
				printf("!!");//須使用備援點(之後須建立備援點使用順序)
				newStar=secPoint[0];//先用第1筆測試(之後筆要在寫)
				delSecPoint(newStar,secPoint,CM_secPointSize);
				return newStar;
			}
			psi=0;
		}
		psi++;
	}
	while(passPointNum!=0);//檢測到最後一筆(必0)
	delSecPoint(newStar,secPoint,CM_secPointSize);
	return newStar;

	
	checkEmpty=get_map(fileName,map_point_star,newStar);
	if(checkEmpty==0)
	{
		printf("star id can't find error");
		return 0;
	}

		
}

int cleanPath(char *fileName,int starPoint)
{
	extern int CM_passPointSize;
	extern int CM_passPoint[];
	int  pointx4[4]={0,0,0,0};
	int i,start=0;
	for(i=0;i<CM_passPointSize;i++)
	{
		nextLink(fileName,pointx4,CM_passPoint[i],0);
		start=i;
		if(pointx4[0]==starPoint)break;
		if(pointx4[1]==starPoint)break;
		if(pointx4[2]==starPoint)break;
		if(pointx4[3]==starPoint)break;
	}
	for(i=start+1;i<CM_passPointSize;i++)
	{
		CM_passPoint[i]=0;
	}
	return start;
	
}

void saveMap(char *fileName,int x,int y,int id,int local,int mode)
//手動紀錄方案(暫停使用)
//#序號 -X-Y-格式999-北-東-南-西-分區-預留-(環境資訊)
//#序號 -X-Y-格式998-北-東-南-西-動作-預留-(動作紀錄)用local數值當動作
{
	int  map_point[9]={0,0,0,0,0,0,0,0,0};
	int  map_point2[7]={0,0,0,0,0,0,0};
	
	get_map(fileName,map_point,id);
	map_point2[6]=map_point[8];
	map_point2[5]=map_point[7];
	map_point2[4]=map_point[6];
	map_point2[3]=map_point[5];
	map_point2[2]=map_point[4];
	map_point2[1]=map_point[3];
	switch (mode)
	{
		case 1: 							//模式1寫入北方可走一格
		map_point2[0]=999;					//格式999
		map_point2[1]=1;					//北
		map_point2[5]=local;				//分區
		set_map(fileName,x,y,map_point2,id);
		break;
		
		case 2:								//模式2寫入東方可走一格
		map_point2[0]=999;					//格式999
		map_point2[2]=1;					//東
		map_point2[5]=local;				//分區
		set_map(fileName,x,y,map_point2,id);
		break;

		case 3: 							//模式3寫入南方可走一格
		map_point2[0]=999;					//格式999						
		map_point2[3]=1;					//南
		map_point2[5]=local;				//分區
		set_map(fileName,x,y,map_point2,id);
		break;
		
		case 4:								//模式4寫入西方可走一格
		map_point2[0]=999;					//格式999
		map_point2[4]=1;;					//西
		map_point2[5]=local;				//分區
		set_map(fileName,x,y,map_point2,id);
		break;		
		
		case 5: 							//模式5寫入面相方向與旋轉方向
		map_point2[0]=998;					//格式998
		map_point2[1]=1;					//面向北方
		map_point2[2]=0;
		map_point2[3]=0;
		map_point2[4]=0;
		map_point2[5]=local;				//選轉動作1右2左
		set_map(fileName,x,y,map_point2,id);
		break;
		
		case 6: 							//模式6寫入面相方向與旋轉方向
		map_point2[0]=998;					//格式998
		map_point2[1]=0;
		map_point2[2]=1;					//面向東方
		map_point2[3]=0;
		map_point2[4]=0;
		map_point2[5]=local;				//選轉動作1右2左
		set_map(fileName,x,y,map_point2,id);
		break;

		case 7: 							//模式7寫入面相方向與旋轉方向
		map_point2[0]=998;					//格式998
		map_point2[1]=0;
		map_point2[2]=0;
		map_point2[3]=1;					//面向南方
		map_point2[4]=0;
		map_point2[5]=local;				//選轉動作1右2左
		set_map(fileName,x,y,map_point2,id);
		break;
		
		case 8: 							//模式8寫入面相方向與旋轉方向
		map_point2[0]=998;					//格式998
		map_point2[1]=0;
		map_point2[2]=0;
		map_point2[3]=0;
		map_point2[4]=1;					//面向西方
		map_point2[5]=local;				//選轉動作1右2左
		set_map(fileName,x,y,map_point2,id);
		break;	
	}
	
}
void initArryay(int *arr,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		arr[i]=0;
	}
}


