 /*
 * MAIN Generated Driver File
 *
 * @file main.c
 *
 * @defgroup main MAIN
 *
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip
    software and any derivatives exclusively with Microchip products.
    You are responsible for complying with 3rd party license terms
    applicable to your use of 3rd party software (including open source
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.?
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR
    THIS SOFTWARE.
*/
//---------------------------------------------------------------------------------------------------------------------------
/*
    Main application
*/
#include "mcc_generated_files/system/system.h"


int player=1;
int waits=0,win=0,winloop=0;
int count1=0,count2=0;
int limit1[3][2]={{3,3},{3,3},{3,3}};
int limit2[3][2]={{3,3},{3,3},{3,3}};

//盤面リセット
void reset(void){
    if(win==1||win==-1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                limit1[i][j]=3;
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                limit2[i][j]=3;
            }
        }
    }
    win=0;
}

//待機＆勝敗点灯
void wait(void){
    if(win==1&&winloop<300){
        LATBbits.LATB5=0;
        LATBbits.LATB3=0;
        LATBbits.LATB1=0;
    }
    else if(win==-1&&winloop<300){
        LATBbits.LATB4=0;
        LATBbits.LATB2=0;
        LATBbits.LATB0=0;
    }
    winloop+=1;
    if(winloop==600) winloop=0;
    for(long i=0;i<300;i++) waits=1;
}

//盤面消灯
void lightdown(void){
    LATAbits.LATA7=1;
    LATAbits.LATA0=1;
    LATBbits.LATB6=1;
    LATBbits.LATB7=1;
    LATBbits.LATB1=0;
    LATBbits.LATB3=0;
    LATBbits.LATB5=0;
    LATBbits.LATB4=0;
    LATBbits.LATB2=0;
    LATBbits.LATB0=0;
}

//順番LED点灯
void turn1(void){
    LATBbits.LATB4=0;
    LATBbits.LATB2=0;
    LATBbits.LATB0=0;
    LATAbits.LATA7=0;
    LATBbits.LATB1=1;
    LATBbits.LATB3=1;
    LATBbits.LATB5=1;
}
void turn2(void){
    LATBbits.LATB1=0;
    LATBbits.LATB3=0;
    LATBbits.LATB5=0;
    LATAbits.LATA7=0;
    LATBbits.LATB4=1;
    LATBbits.LATB2=1;
    LATBbits.LATB0=1;
}

//３つまで制限
void limitg(void){
    if(count1==3){
        limit1[0][0]=limit1[1][0];
        limit1[0][1]=limit1[1][1];
        limit1[1][0]=limit1[2][0];
        limit1[1][1]=limit1[2][1];
        count1--;
    }
}
void limitr(void){
    if(count2==3){
        limit2[0][0]=limit2[1][0];
        limit2[0][1]=limit2[1][1];
        limit2[1][0]=limit2[2][0];
        limit2[1][1]=limit2[2][1];
        count2--;
    }
}
void renewg(int i,int j){
    limitg();
    limit1[count1][0]=i;
    limit1[count1][1]=j;
    count1++;
}
void renewr(int i,int j){
    limitr();
    limit2[count2][0]=i;
    limit2[count2][1]=j;
    count2++;
}

//ボタン判定
void catchbutton(void){
        LATAbits.LATA1=1;
        if(PORTAbits.RA3==1){
            while(PORTAbits.RA3==1){
                waits=1;
            }
            if(player==1){
                renewg(0,0);
            }
            else if(player==-1){
                renewr(0,0);
            }
            player*=-1;
            reset();
        }
        LATAbits.LATA1=1;
        if(PORTAbits.RA4==1){
            while(PORTAbits.RA4==1){
                waits=1;
            }
            if(player==1){
                renewg(1,0);
            }
            else if(player==-1){
                renewr(1,0);
            }
            player*=-1;
            reset();
        }

        LATAbits.LATA1=1;
        if(PORTAbits.RA5==1){
            while(PORTAbits.RA5==1){
                waits=1;
            }
            if(player==1){
                renewg(2,0);
            }
            else if(player==-1){
                renewr(2,0);
            }
            player*=-1;
            reset();
        }
        LATAbits.LATA1=0;

        LATAbits.LATA2=1;
        if(PORTAbits.RA3==1){
            while(PORTAbits.RA3==1){
                waits=1;
            }
            if(player==1){
                renewg(0,1);
            }
            else if(player==-1){
                renewr(0,1);
            }
            player*=-1;
            reset();
        }
        LATAbits.LATA2=1;
        if(PORTAbits.RA4==1){
            while(PORTAbits.RA4==1){
                waits=1;
            }
            if(player==1){
                renewg(1,1);
            }
            else if(player==-1){
                renewr(1,1);
            }
            player*=-1;
            reset();
        }

        LATAbits.LATA2=1;
        if(PORTAbits.RA5==1){
            while(PORTAbits.RA5==1){
                waits=1;
            }
            if(player==1){
                renewg(2,1);
            }
            else if(player==-1){
                renewr(2,1);
            }
            player*=-1;
            reset();
        }
        LATAbits.LATA2=0;

        LATAbits.LATA6=1;
        if(PORTAbits.RA3==1){
            while(PORTAbits.RA3==1){
                waits=1;
            }
            if(player==1){
                renewg(0,2);
            }
            else if(player==-1){
                renewr(0,2);
            }
            player*=-1;
            reset();
        }
        LATAbits.LATA6=1;
        if(PORTAbits.RA4==1){
            while(PORTAbits.RA4==1){
                waits=1;
            }
            if(player==1){
                renewg(1,2);
            }
            else if(player==-1){
                renewr(1,2);
            }
            player*=-1;
            reset();
        }

        LATAbits.LATA6=1;
        if(PORTAbits.RA5==1){
            while(PORTAbits.RA5==1){
                waits=1;
            }
            if(player==1){
                renewg(2,2);
            }
            else if(player==-1){
                renewr(2,2);
            }
            player*=-1;
            reset();
        }
        LATAbits.LATA6=0;
}

//盤面点灯制限付き
void lightenlimit(void){
    lightdown();

    if(limit1[0][1]==0){
        switch(limit1[0][0]){
            case 0:LATAbits.LATA0=0,LATBbits.LATB5=1;break;
            case 1:LATAbits.LATA0=0,LATBbits.LATB3=1;break;
            case 2:LATAbits.LATA0=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit1[1][1]==0){
        switch(limit1[1][0]){
            case 0:LATAbits.LATA0=0,LATBbits.LATB5=1;break;
            case 1:LATAbits.LATA0=0,LATBbits.LATB3=1;break;
            case 2:LATAbits.LATA0=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit1[2][1]==0){
        switch(limit1[2][0]){
            case 0:LATAbits.LATA0=0,LATBbits.LATB5=1;break;
            case 1:LATAbits.LATA0=0,LATBbits.LATB3=1;break;
            case 2:LATAbits.LATA0=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[0][1]==0){
        switch(limit2[0][0]){
            case 0:LATAbits.LATA0=0,LATBbits.LATB4=1;break;
            case 1:LATAbits.LATA0=0,LATBbits.LATB2=1;break;
            case 2:LATAbits.LATA0=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[1][1]==0){
        switch(limit2[1][0]){
            case 0:LATAbits.LATA0=0,LATBbits.LATB4=1;break;
            case 1:LATAbits.LATA0=0,LATBbits.LATB2=1;break;
            case 2:LATAbits.LATA0=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[2][1]==0){
        switch(limit2[2][0]){
            case 0:LATAbits.LATA0=0,LATBbits.LATB4=1;break;
            case 1:LATAbits.LATA0=0,LATBbits.LATB2=1;break;
            case 2:LATAbits.LATA0=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    lightdown();
    if(limit1[0][1]==1){
        switch(limit1[0][0]){
            case 0:LATBbits.LATB6=0,LATBbits.LATB5=1;break;
            case 1:LATBbits.LATB6=0,LATBbits.LATB3=1;break;
            case 2:LATBbits.LATB6=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit1[1][1]==1){
        switch(limit1[1][0]){
            case 0:LATBbits.LATB6=0,LATBbits.LATB5=1;break;
            case 1:LATBbits.LATB6=0,LATBbits.LATB3=1;break;
            case 2:LATBbits.LATB6=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit1[2][1]==1){
        switch(limit1[2][0]){
            case 0:LATBbits.LATB6=0,LATBbits.LATB5=1;break;
            case 1:LATBbits.LATB6=0,LATBbits.LATB3=1;break;
            case 2:LATBbits.LATB6=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[0][1]==1){
        switch(limit2[0][0]){
            case 0:LATBbits.LATB6=0,LATBbits.LATB4=1;break;
            case 1:LATBbits.LATB6=0,LATBbits.LATB2=1;break;
            case 2:LATBbits.LATB6=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[1][1]==1){
        switch(limit2[1][0]){
            case 0:LATBbits.LATB6=0,LATBbits.LATB4=1;break;
            case 1:LATBbits.LATB6=0,LATBbits.LATB2=1;break;
            case 2:LATBbits.LATB6=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[2][1]==1){
        switch(limit2[2][0]){
            case 0:LATBbits.LATB6=0,LATBbits.LATB4=1;break;
            case 1:LATBbits.LATB6=0,LATBbits.LATB2=1;break;
            case 2:LATBbits.LATB6=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    lightdown();
    if(limit1[0][1]==2){
        switch(limit1[0][0]){
            case 0:LATBbits.LATB7=0,LATBbits.LATB5=1;break;
            case 1:LATBbits.LATB7=0,LATBbits.LATB3=1;break;
            case 2:LATBbits.LATB7=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit1[1][1]==2){
        switch(limit1[1][0]){
            case 0:LATBbits.LATB7=0,LATBbits.LATB5=1;break;
            case 1:LATBbits.LATB7=0,LATBbits.LATB3=1;break;
            case 2:LATBbits.LATB7=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit1[2][1]==2){
        switch(limit1[2][0]){
            case 0:LATBbits.LATB7=0,LATBbits.LATB5=1;break;
            case 1:LATBbits.LATB7=0,LATBbits.LATB3=1;break;
            case 2:LATBbits.LATB7=0,LATBbits.LATB1=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[0][1]==2){
        switch(limit2[0][0]){
            case 0:LATBbits.LATB7=0,LATBbits.LATB4=1;break;
            case 1:LATBbits.LATB7=0,LATBbits.LATB2=1;break;
            case 2:LATBbits.LATB7=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[1][1]==2){
        switch(limit2[1][0]){
            case 0:LATBbits.LATB7=0,LATBbits.LATB4=1;break;
            case 1:LATBbits.LATB7=0,LATBbits.LATB2=1;break;
            case 2:LATBbits.LATB7=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    if(limit2[2][1]==2){
        switch(limit2[2][0]){
            case 0:LATBbits.LATB7=0,LATBbits.LATB4=1;break;
            case 1:LATBbits.LATB7=0,LATBbits.LATB2=1;break;
            case 2:LATBbits.LATB7=0,LATBbits.LATB0=1;break;
            default:break;
        }
        wait();
    }
    lightdown();
}

//勝利判定
void judge(void){
    if(limit1[2][0]==0){
        if(limit1[1][0]==0&&limit1[0][0]==0){
            win=1;
        }
        else if(limit1[1][1]==limit1[2][1]&&limit1[0][1]==limit1[2][1]){
            win=1;
        }
    }
    else if(limit1[2][0]==1){
        if(limit1[1][0]==1&&limit1[0][0]==1){
            win=1;
        }
        else if(limit1[1][1]==limit1[2][1]&&limit1[0][1]==limit1[2][1]){
            win=1;
        }
    }
    else if(limit1[2][0]==2){
        if(limit1[1][0]==2&&limit1[0][0]==2){
            win=1;
        }
        else if(limit1[1][1]==limit1[2][1]&&limit1[0][1]==limit1[2][1]){
            win=1;
        }
    }

    if(limit2[2][0]==0){
        if(limit2[1][0]==0&&limit2[0][0]==0){
            win=-1;
        }
        else if(limit2[1][1]==limit2[2][1]&&limit2[0][1]==limit2[2][1]){
            win=-1;
        }
    }
    else if(limit2[2][0]==1){
        if(limit2[1][0]==1&&limit2[0][0]==1){
            win=-1;
        }
        else if(limit2[1][1]==limit2[2][1]&&limit2[0][1]==limit2[2][1]){
            win=-1;
        }
    }
    else if(limit2[2][0]==2){
        if(limit2[1][0]==2&&limit2[0][0]==2){
            win=-1;
        }
        else if(limit2[1][1]==limit2[2][1]&&limit2[0][1]==limit2[2][1]){
            win=-1;
        }
    }

    if(limit1[2][0]==0){
        if(limit1[2][1]==0){
            if(((limit1[1][0]==1&&limit1[1][1]==1)&&(limit1[0][0]==2&&limit1[0][1]==2))||((limit1[1][0]==2&&limit1[1][1]==2)&&(limit1[0][0]==1&&limit1[0][1]==1))){
                win=1;
            }
        }
        else if(limit1[2][1]==2){
            if(((limit1[1][0]==1&&limit1[1][1]==1)&&(limit1[0][0]==2&&limit1[0][1]==0))||((limit1[1][0]==2&&limit1[1][1]==0)&&(limit1[0][0]==1&&limit1[0][1]==1))){
                win=1;
            }
        }
    }
    else if(limit1[2][0]==1){
        if(limit1[2][1]==1){
            if(((limit1[1][0]==0&&limit1[1][1]==2)&&(limit1[0][0]==2&&limit1[0][1]==0))||((limit1[1][0]==2&&limit1[1][1]==0)&&(limit1[0][0]==0&&limit1[0][1]==2))){
                win=1;
            }
            else if(((limit1[1][0]==2&&limit1[1][1]==2)&&(limit1[0][0]==0&&limit1[0][1]==0))||((limit1[1][0]==0&&limit1[1][1]==0)&&(limit1[0][0]==2&&limit1[0][1]==2))){
                win=1;
            }
        }
    }
    else if(limit1[2][0]==2){
        if(limit1[2][1]==0){
            if(((limit1[1][0]==1&&limit1[1][1]==1)&&(limit1[0][0]==0&&limit1[0][1]==2))||((limit1[1][0]==0&&limit1[1][1]==2)&&(limit1[0][0]==1&&limit1[0][1]==1))){
                win=1;
            }
        }
        else if(limit1[2][1]==2){
            if(((limit1[1][0]==1&&limit1[1][1]==1)&&(limit1[0][0]==0&&limit1[0][1]==0))||((limit1[1][0]==0&&limit1[1][1]==0)&&(limit1[0][0]==1&&limit1[0][1]==1))){
                win=1;
            }
        }
    }
    if(limit2[2][0]==0){
        if(limit2[2][1]==0){
            if(((limit2[1][0]==1&&limit2[1][1]==1)&&(limit2[0][0]==2&&limit2[0][1]==2))||((limit2[1][0]==2&&limit2[1][1]==2)&&(limit2[0][0]==1&&limit2[0][1]==1))){
                win=-1;
            }
        }
        else if(limit2[2][1]==2){
            if(((limit2[1][0]==1&&limit2[1][1]==1)&&(limit2[0][0]==2&&limit2[0][1]==0))||((limit2[1][0]==2&&limit2[1][1]==0)&&(limit2[0][0]==1&&limit2[0][1]==1))){
                win=-1;
            }
        }
    }
    else if(limit2[2][0]==1){
        if(limit2[2][1]==1){
            if(((limit2[1][0]==0&&limit2[1][1]==2)&&(limit2[0][0]==2&&limit2[0][1]==0))||((limit2[1][0]==2&&limit2[1][1]==0)&&(limit2[0][0]==0&&limit2[0][1]==2))){
                win=-1;
            }
            else if(((limit2[1][0]==2&&limit2[1][1]==2)&&(limit2[0][0]==0&&limit2[0][1]==0))||((limit2[1][0]==0&&limit2[1][1]==0)&&(limit2[0][0]==2&&limit2[0][1]==2))){
                win=-1;
            }
        }
    }
    else if(limit2[2][0]==2){
        if(limit2[2][1]==0){
            if(((limit2[1][0]==1&&limit2[1][1]==1)&&(limit2[0][0]==0&&limit2[0][1]==2))||((limit2[1][0]==0&&limit2[1][1]==2)&&(limit2[0][0]==1&&limit2[0][1]==1))){
                win=-1;
            }
        }
        else if(limit2[2][1]==2){
            if(((limit2[1][0]==1&&limit2[1][1]==1)&&(limit2[0][0]==0&&limit2[0][1]==0))||((limit2[1][0]==0&&limit2[1][1]==0)&&(limit2[0][0]==1&&limit2[0][1]==1))){
                win=-1;
            }
        }
    }
}


//メインループ
int main(void)
{
    SYSTEM_Initialize();
    LATA=0b11000001;
    LATB=0b11000000;

    while(1){
        //ボタン判定
        catchbutton();

        //順番LED点灯
        if(player==1){
            turn1();
        }
        else if(player==-1){
            turn2();
        }
        wait();

        //盤面点灯制限付き
        lightenlimit();

        //勝利判定
        judge();
        lightdown();

    }
    //---------------------------------------------------------------------------------------------------------------------




    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();


    while(1)
    {
    }
}
