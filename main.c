#include <reg52.h>

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

sbit p15 = P1 ^5;

char lastOne;
int pu[] = {6, 7, 8, 8, 7, 8, 8, 10,10, 7,7, 0,0,0, 3, 6, 6, 5, 6,6, 8,8, 5};

void dor() {
    unsigned char a, b;
    for (b = 127; b > 0; b--)
        for (a = 6; a > 0; a--);
}

void re() {
    unsigned char a, b;
    for (b = 188; b > 0; b--)
        for (a = 3; a > 0; a--);
}

void mi() {
    unsigned char a, b;
    for (b = 109; b > 0; b--)
        for (a = 5; a > 0; a--);
}

void fa() {
    unsigned char a, b;
    for (b = 109; b > 0; b--)
        for (a = 5; a > 0; a--);
}

void so() {
    unsigned char a, b;
    for (b = 3; b > 0; b--)
        for (a = 209; a > 0; a--);
}

void la() {
    unsigned char a, b, c;
    for (c = 2; c > 0; c--)
        for (b = 112; b > 0; b--)
            for (a = 1; a > 0; a--);
}

void si() {
    unsigned char a, b;
    for (b = 59; b > 0; b--)
        for (a = 7; a > 0; a--);
}

void douP() {
    unsigned char a, b;
    for (b = 3; b > 0; b--)
        for (a = 157; a > 0; a--);
}

void reP() {
    unsigned char a, b;
    for (b = 121; b > 0; b--)
        for (a = 2; a > 0; a--);
}

void miP() {
    unsigned char a, b;
    for (b = 151; b > 0; b--)
        for (a = 1; a > 0; a--);
}

void faP() {
    unsigned char a, b;
    for (b = 8; b > 0; b--)
        for (a = 43; a > 0; a--);
}

void sing() {
    while (1) {
        for (i = 0; i < 23; ++i) {
            z = 0;
            for (j = 0; j < 500; ++j) {
                switch (pu[i]) {

                    case 1: {
                        dor();
                        break;
                    }

                    case 2: {
                        re();
                        break;
                    }

                    case 3: {
                        mi();
                        break;
                    }

                    case 4: {
                        fa();
                        break;
                    }

                    case 5: {
                        so();
                        break;
                    }
                    case 6: {
                        la();
                        break;
                    }

                    case 7: {
                        si();
                        break;
                    }

                    case 8: {
                        douP();
                        break;
                    }

                    case 9: {
                        reP();
                        break;
                    }

                    case 10: {
                        miP();
                        break;
                    }

                    case 11: {
                        fa();
                        break;
                    }
                }
                if (pu[i]!=0){
                    z = !z;
                }
                p15 = z;
            }
            for (d = 0; d < 200; ++d) {

            }
        }
        if (P3 == 0xff) {
            break;
        }
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
            sing();
            break;
        }
        case '2':{
            flagForSpark = 0;
            break;
        }
        case '3':{
            flagForSpark = 0;
            break;
        }
    }
}