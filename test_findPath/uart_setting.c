//uart_setting.c


#include     <stdio.h>      /*標準輸入輸出定義*/

#include     <stdlib.h>     /*標準函數庫定義*/

#include     <unistd.h>     /*Unix標準函數定義*/

#include     <sys/types.h>  /**/

#include     <sys/stat.h>   /**/

#include     <fcntl.h>      /*檔控制定義*/

#include     <termios.h>    /*PPSIX終端控制定義*/

#include     <errno.h>      /*錯誤號定義*/

int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,

            B38400, B19200, B9600, B4800, B2400, B1200, B300, };

int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300,

            38400,  19200,  9600, 4800, 2400, 1200,  300, };

void set_speed(int fd, int speed)

{

  int   i;

  int   status;

  struct termios   Opt;

  tcgetattr(fd, &Opt);

  for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)

   {

        if  (speed == name_arr[i])

        {

            tcflush(fd, TCIOFLUSH);

        cfsetispeed(&Opt, speed_arr[i]);

        cfsetospeed(&Opt, speed_arr[i]);

        status = tcsetattr(fd, TCSANOW, &Opt);

        if  (status != 0)

            perror("tcsetattr fd1");

        return;

        }

   tcflush(fd,TCIOFLUSH);

   }

}

/**

*@brief   設置串口資料位元，停止位元和效驗位

*@param  fd     類型  int  打開的串口文件控制碼*

*@param  databits 類型  int 資料位元   取值 為 7 或者8*

*@param  stopbits 類型  int 停止位   取值為 1 或者2*

*@param  parity  類型  int  效驗類型 取值為N,E,O,,S

*/

int set_Parity(int fd,int databits,int stopbits,int parity)

{

        struct termios options;

 if  ( tcgetattr( fd,&options)  !=  0)

  {
	printf("tcgetattr error\n");
        perror("SetupSerial 1");

        return(0);

  }

  options.c_cflag &= ~CSIZE;

  switch (databits) /*設置數據位元數*/

  {

        case 7:

                 options.c_cflag |= CS7;

                 break;

        case 8:

                 options.c_cflag |= CS8;

                 break;

        default:

                 fprintf(stderr,"Unsupported data size\n");
		printf("Unsupported data size error\n");

                 return (0);

        }

  switch (parity)

        {

        case 'n':

        case 'N':

                 options.c_cflag &= ~PARENB;   /* Clear parity enable */

                 options.c_iflag &= ~INPCK;     /* Enable parity checking */

                 break;

        case 'o':

        case 'O':

                 options.c_cflag |= (PARODD | PARENB);  /* 設置為奇效驗*/ 

                 options.c_iflag |= INPCK;             /* Disnable parity checking */

                 break;

        case 'e':

        case 'E':

                 options.c_cflag |= PARENB;     /* Enable parity */

                 options.c_cflag &= ~PARODD;   /* 轉換為偶效驗*/  

                 options.c_iflag |= INPCK;       /* Disnable parity checking */

                 break;

        case 'S':

        case 's':  /*as no parity*/

                 options.c_cflag &= ~PARENB;

                 options.c_cflag &= ~CSTOPB;

                 break;

        default:

                 fprintf(stderr,"Unsupported parity\n");
		printf("Unsupported parity error\n");

                 return (0);

                 }

  /* 設置停止位*/   

  switch (stopbits)

        {

        case 1:

                 options.c_cflag &= ~CSTOPB;

                 break;

        case 2:

                 options.c_cflag |= CSTOPB;

                 break;

        default:

                 fprintf(stderr,"Unsupported stop bits\n");
		printf("Unsupported stop bits error\n");

                 return (0);

        }

  /* Set input parity option */

  if (parity != 'n')

                 options.c_iflag |= INPCK;

    options.c_cc[VTIME] = 150; // 15 seconds

    options.c_cc[VMIN] = 0;

 

  tcflush(fd,TCIFLUSH); /* Update the options and do it NOW */

  if (tcsetattr(fd,TCSANOW,&options) != 0)

        {

		printf("SetupSerial 3 error\n");
                 perror("SetupSerial 3");

                 return (0);

        }

  return (1);

 }

/**

*@breif 打開串口

*/

int OpenDev(char *Dev)

{

int     fd = open( Dev, O_RDONLY );         //| O_NOCTTY | O_NDELAY

        if (-1 == fd)

                 { /*設置數據位元數*/

                         perror("Can't Open Serial Port");

                         return -1;

                 }

        else

        return fd;

}