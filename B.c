//
// Created by Lenovo on 2020-11-26.
//
#include <reg52.h>

unsigned char Temp;
unsigned int c[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delay10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void main() {
    unsigned char temp = 0;
    SCON = 0x50;//设置为方式1接收工作
    PCON = 0x70;// SMOD=1
    TMOD = 0x20;
    TH1 = 0xff;//设置波特率为4800
    TL1 = 0xf4;
    TR1 = 1;
    EA = 1;
    ES = 1;
    //使用查询的方法发送数据
    while (1) {
        if (P3 != ~0x00) {
            delay10ms();
            if (P3 != ~0x00) {
                switch (P3) {
                    case ~0x01: {//0001
                        temp = 1;
                        break;
                    }
                    case ~0x02: {//0010
                        temp = 0;
                        break;
                    }
                    case ~0x04: {//0100
                        temp = 2;
                        break;
                    }
                    case ~0x08: {
                        temp = 3;
                        break;
                    }
                }
                SBUF = temp;
                while (TI == 0);
                TI = 1;
            }
        }
    }
}

void onReceive() interrupt 4 {
    if (RI) {
        int count = 0;
        RI = 0;
        Temp = SBUF;
        count = Temp;
        P0 = c[count];
    }
}
