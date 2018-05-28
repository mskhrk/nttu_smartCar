//sm_car.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//此函式庫沒有最上方的宣告所以子函數需要放在上方

/*
mapCreat 地圖生成(16方向)

使用說明
使用車子自旋連續取得超音波數據，並將此數據切為16份，每一份代表一個方向
此函式功能在於處理旋轉完後取得的數據
對數據分群，餘額分配，計算平均後輸出結果

參數說明
map_data 外部輸入資料存放陣列
map		 輸出資料陣列
allData	 外部輸入資料數量


*/
void mapCreat(int *map_data,int *map,int allData)
{
	int  group_member; //每組基本個數(不包含餘數)
	int  member_remain;//剩餘個數
	int  i,q=0;			//for計數器
	int  group_law[16]={1,9,5,13,3,11,15,7,2,10,16,8,4,12,14,6};//剩餘個數平均分配規則
	int  group_amount[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	//各組成員數
	int  map_16direction[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	//最終結果16個方向(單一數值為各組數值平均)
	int  data_counter=0;//計數器
	int  overAddStart;
	int  overAddStartMod;
	
	
	group_member=allData/16;//每組個數
	member_remain=allData%16;//剩餘個數
	
	for(i=0;i<16;i++)//把每一組的人數加入(不含餘數)
	{
		group_amount[group_law[i]-1]=group_member;
	}
	
	for(i=0;i<member_remain;i++)//把餘數按平均規則加入
	{
		group_amount[group_law[i]-1]+=1;
	}
	
	for(i=0;i<16;i++)//計算16個方位的數值
	{
		if(i==0)
		{
			overAddStart=group_amount[0]/2;
			overAddStartMod=group_amount[0]%2;
			data_counter=allData-overAddStart;
			for(q=0;q<overAddStart;q++)
				{
					map_16direction[0]+=map_data[data_counter];//把結尾的地圖資料放入所屬的方位中
					data_counter++;
				}
			data_counter=0;
			for(q=0;q<(overAddStart+overAddStartMod);q++)
				{
					map_16direction[0]+=map_data[data_counter];//把開頭的地圖資料放入所屬的方位中
					data_counter++;
				}
			map_16direction[0] /= group_amount[0];
		}	
		else
		{
			for(q=0;q<group_amount[i];q++)
			{
				map_16direction[i]+=map_data[data_counter];//把每一筆的地圖資料放入所屬的方位中
				data_counter++;
			}
			map_16direction[i] /= group_amount[i];//每組的所有數值取平均
		}
	}
	
	for(i=0;i<16;i++)
	{
		map[i]=map_16direction[i];
	}
	
	//free(map_data);
}


//利用車子自轉連續取得數值，並計算出外部環境樣貌
//與現有起點資料比較找出起點(目前方位)
int oneCircleTest(int *testData,int dataSize,int bufferSize,int deviation,int e)
//*testData  待測試資料的來源位置
//dataSize	 待測試資料的數量(alldata)
//bufferSize 測試框的大小，越小越不准，上限不可超過一圈
//deviation  測試差異的誤差精準度，誤差值越大越不精準，誤差值過低可能導致判斷失敗
//e 		 容許多或少值的數量

//return 	 檢測出的第1個值
{
	int i,q;
	int *testBuffer = calloc(bufferSize, sizeof(int));//動態配置測試框
	int testPass=0;
	int testCounter=0;
	int testingData;
	int testPassFlag;
	int k;//k迴圈計數器、e容許失誤範圍(e=1 範圍為+-1)
	
	

	
	for(i=0;i<bufferSize;i++)//外部資料輸入
	{
		testBuffer[i]=testData[i];
		//printf("%d %d\n",i,testBuffer[i]);
	}
	
		
		//
		for(i=0;i<dataSize-bufferSize;i++)//外部資料檢測 dataSize-bufferSize扣除前面不用比較的
	{
		if(dataSize-bufferSize<=0){printf("dataSize&bufferSize setting error    \n");break;}
		printf("dataSize-bufferSize =%d\n",(dataSize-bufferSize));
		printf("i =%d\n",i);
		testingData=(testData[i+bufferSize]-testBuffer[testCounter]);
		//printf("%d %d\n",testData[i+bufferSize],testBuffer[testCounter]);
		if(testingData<0){testingData*=-1;}
		//printf("oneCircleTest ok1-1\n");

		
		if(testingData<=deviation)
		{
			testPass++;
			testCounter++;
		}
		else
		{
			testingData=(testData[i+bufferSize]-testBuffer[0]);//測試是否從頭
			if(testingData<0){testingData*=-1;}			
			if(testingData<=deviation)
			{
				testPass=1;
				testCounter=1;//第0個判斷通過，下一個是第一個
			}
			else
			{	
				testPassFlag=0;//初始testPassFlag，for迴圈判定旗標
				for(k=1;k<=e;k++)
				{
					if(i+bufferSize+k>dataSize-1)break;//避免讀取超過區域的資料i+bufferSize+k(陣列index)不可大於dataSize(陣列數量)
					if(i+bufferSize-k<0)break;//避免讀取超過區域的資料
					testingData=(testData[i+bufferSize+k]-testBuffer[testCounter]);//是否少項
					if(testingData<0){testingData*=-1;}
					if(testingData<=deviation)
					{
						testPass++;//少項判斷後會計入通過次數
						testCounter++;
						i--;//要比較的位置不變
						testPassFlag=1;
						break;
					}
					else{
						testingData=(testData[i+bufferSize-k]-testBuffer[testCounter]);//是否多項
						if(testingData<0){testingData*=-1;}
						if(testingData<=deviation)
						{
							testPass++;
							testCounter++;
							testPassFlag=1;
							i=i+k;//要比較的位置向後移動
							break;
						}
					}
				}
				//printf("oneCircleTest ok1-2\n");
				if(testPassFlag==0)//for全都沒有判斷到
				{
					testPass=0;
					testCounter=0;
					//printf("oneCircleTest ok2\n");	
				}
										
			}
			
		}
		
		if(testPass==bufferSize)
		{
			printf("oneCircleTest ok3\n");	
			return (i+2);	//回傳檢測出的第1個 
					//i+b-(b-1)+1 計數器i(算到最後一筆符合)+站存空間b(最前面b個不比較)-((b-1)要回傳的是第一筆)+1(實際數值起頭是1)
		}
	}
	free(testBuffer);
	printf("oneCircleTest ok3-1\n");
	return 0;
}

int oneCircleTime(int scanTime,int secendStart,int alldata)
{
	int oneGapTime;
	int answer;
	oneGapTime=(scanTime/alldata);
	answer=oneGapTime*(secendStart-1);
	printf("auto run ans %d",answer);
	if(answer>=6000||answer<=2000){answer=4350;}
	return answer;
}
	
