//
// Created by Lenovo on 2020-11-24.
//
#include "MusicTool.h"
#include <reg52.h>

sbit p15 = P1 ^5;
int pu[] = {6, 7, 8, 8, 7, 8, 8, 10, 10, 7, 7, 0, 0, 0, 3, 6, 6, 5, 6, 6, 8, 8, 5};
int i, j, z, d;
int playFlag = 1;

//覆写方法
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

void play() {
    while (playFlag){
        for (i = 0; i < 23; ++i) {
            z = 0;
            for (j = 0; j < 500; ++j) {
                //选择频谱
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
                if (pu[i] != 0) {
                    z = !z;//高低电平转换
                }
                p15 = z;
            }
            //休止符
            for (d = 0; d < 200; ++d) {

            }
        }
    }
}

void stop(){
    playFlag = 0;
}
