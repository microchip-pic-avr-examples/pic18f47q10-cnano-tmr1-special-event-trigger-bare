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

#define COMPARE_VALUE_HIGH              0x0F
#define COMPARE_VALUE_LOW               0xFF

#define PPS_CONFIG_RB0_CCP1_OUT         0x05

static void CLK_init(void);
static void PPS_init(void);
static void PORT_init(void);
static void TMR1_init(void);
static void CCP1_init(void);

/* Clock initialization function */
static void CLK_init(void)
{
    /* set HFINTOSC as new oscillator source */
    OSCCON1 = _OSCCON1_NOSC1_MASK | _OSCCON1_NOSC2_MASK;

    /* set Clock Div by 32 */
    OSCCON1 |= _OSCCON1_NDIV0_MASK | _OSCCON1_NDIV2_MASK;

    /* set HFFRQ to 32MHz */
    OSCFRQ = _OSCFRQ_FRQ1_MASK | _OSCFRQ_FRQ2_MASK;
}

/* PPS initialization function */
static void PPS_init(void)
{
    /* Configure RB0 for CCP1 output */
    RB0PPS = PPS_CONFIG_RB0_CCP1_OUT;
}

/* Port initialization function */
static void PORT_init(void)
{
    /* Set RB0 as output */
    TRISB &= ~(_TRISB_TRISB0_MASK);
}

/* TMR1 initialization function */
static void TMR1_init(void)
{
    /* Set timer Source Clock to FOSC/4 */
    T1CLK = _T1CLK_T1CS0_MASK;

    /* Enable timer */
    T1CON = _T1CON_TMR1ON_MASK;
}

/* CCP1 initialization function */
static void CCP1_init(void)
{
    /* Select TMR1 as input for CCP1*/
    CCPTMRS |= _CCPTMRS_C1TSEL0_MASK;

    /* Set the high value for compare */
    CCPR1H = COMPARE_VALUE_HIGH;

    /* Set the low value for compare */
	CCPR1L = COMPARE_VALUE_LOW;

	CCP1CON = _CCP1CON_CCP1MODE1_MASK       /* Compare mode with toggle*/
            | _CCP1CON_EN_MASK;             /* Enable CCP1 */
}

void main(void)
{
    CLK_init();
    PPS_init();
    PORT_init();
    TMR1_init();
    CCP1_init();

    while (1)
    {
        ;
    }
}
