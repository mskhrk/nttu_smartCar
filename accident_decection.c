
extern int IR_judgment;

extern int Wifi_fire,Wifi_mq3,Wifi_mq4;
extern int Wifi_mq7,Wifi_heart;
extern int Wifi_triaxialAccelerator;

extern int AD_nowRun;//現在正在執行的項目代號

extern int CM_run; 
extern int CM_target;
extern int CM_localFire;//AD_nowRun代號1
extern int CM_localMq3;//AD_nowRun代號2
extern int CM_localMq4;//AD_nowRun代號3
extern int CM_localMq7;//AD_nowRun代號4
extern int CM_localFall;//跌倒與心跳均到人的附近，因此使用同一個位置資訊 AD_nowRun代號5~7

int accident_decection()
{
	
	
	while(1){
		while(CM_run==1){sleep(100);}
		
		//先判斷是否有危險訊息、後判斷是否正在移動
		//設定目標位置、意外種類辨別變數、移動訊號變數
		if(Wifi_fire==1&&CM_run==0){CM_target=CM_localFire;AD_nowRun=1;CM_run=1;}
		if(Wifi_mq3==1&&CM_run==0){CM_target=CM_localMq3;AD_nowRun=2;CM_run=1;}
		if(Wifi_mq4==1&&CM_run==0){CM_target=CM_localMq4;AD_nowRun=3;CM_run=1;}
		if(Wifi_mq7==1&&CM_run==0){CM_target=CM_localMq7;AD_nowRun=4;CM_run=1;}
		if(Wifi_heart==1&&CM_run==0){CM_target=CM_localFall;AD_nowRun=5;CM_run=1;}
		if(Wifi_triaxialAccelerator==1&&CM_run==0){CM_target=CM_localFall;AD_nowRun=6;CM_run=1;}
		if(IR_judgment==1&&Wifi_triaxialAccelerator==1&&CM_run==0){CM_target=CM_localFall;AD_nowRun=7;CM_run=1;}//三軸和影像辨識相同功能(三軸優先於影像)
	}

return 0;
}
