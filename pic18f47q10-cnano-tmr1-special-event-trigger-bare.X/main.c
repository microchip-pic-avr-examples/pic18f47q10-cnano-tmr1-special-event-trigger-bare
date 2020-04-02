/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

/* WDT operating mode->WDT Disabled */
#pragma config WDTE = OFF
/* Low voltage programming enabled, RE3 pin is MCLR */
#pragma config LVP = ON 

#include <xc.h>

static void CLK_Initialize(void);
static void PPS_Initialize(void);
static void PORT_Initialize(void);
static void TMR1_Initialize(void);
static void CCP1_Initialize(void);

/* Clock initialization function */
static void CLK_Initialize(void)
{
    /* set HFINTOSC as new oscillator source */
    OSCCON1bits.NOSC = 0x6;

    /* set Clock Div by 32 */
    OSCCON1bits.NDIV = 0x5;      
    
    /* set HFFRQ to 32MHz */
    OSCFRQbits.HFFRQ = 0x6; 
}

/* PPS initialization function */
static void PPS_Initialize(void)
{
    /* Configure RB0 for CCP1 output */
    RB0PPS = 0x05;
}

/* Port initialization function */
static void PORT_Initialize(void)
{
    /* Set RB0 as output */
    TRISBbits.TRISB0 = 0;
}

/* TMR1 initialization function */
static void TMR1_Initialize(void)
{
    /* Set timer Source Clock to FOSC/4 */
    T1CLKbits.CS = 0x1;

    /* Enable timer */
    T1CONbits.ON = 1;
}

/* CCP1 initialization function */
static void CCP1_Initialize(void)
{
    /* Select TMR1 as input for CCP1*/
    CCPTMRSbits.C1TSEL = 0x1;

    /* Set the high value for compare */
    CCPR1H = 0x0F;

    /* Set the low value for compare */
    CCPR1L = 0xFF;

    /* Compare mode with toggle*/
    CCP1CONbits.CCP1MODE = 0x2;

    /* Enable CCP1 */
    CCP1CONbits.EN = 1;             
}

void main(void)
{
    CLK_Initialize();
    PPS_Initialize();
    PORT_Initialize();
    TMR1_Initialize();
    CCP1_Initialize();

    while (1)
    {
        ;
    }
}
