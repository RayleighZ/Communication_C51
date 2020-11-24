#include <reg52.h>
#include "MusicTool.h"
sbit key1 = P3 ^0;
int flagForSpark = 1;

void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void spark(){
    while (flagForSpark){
        P2 = ~P2;
        delay1s();
    }
}

void main() {
    int count = 0;
    SCON = 0x50;//设置为方式1接收工作
    PCON = 0x01;//SCON=1
    TMOD = 0x20;
    TH1 = 0xff;//设置波特率为4800
    TL1 = 0xf4;
    TR1 = 1;
    EA = 1;
    ES = 1;
    //使用查询的方法发送数据
    while (1) {
        if (key1 == 0) {//如果按下key1
            count++;
            SBUFF = count;
            while (TI == 0);
            TI = 1;
        }
    }
}
//甲机接收乙机发送的信息
void onReceive() /*interrupt 4*/ {
    unsigned char temp;
    RI = 0;
    temp = SBUF;
    switch(temp){
        case '0':{
            spark();
            break;
        }
        case '1':{
            flagForSpark = 0;
            break;
        }
        case '2':{
            play();
            break;
        }
        case '3':{
            stop();
            break;
        }
    }
}