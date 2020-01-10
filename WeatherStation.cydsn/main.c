/* ========================================
 *
 * This program is 
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <string.h>

#define READ_LINE_TIMEOUT 1000
#define ESTABLISH_CONN_TIMEOUT 3000 //15000    - за ТСР

#define SLEEP_TIME 20000    // WiFI модула се приспива след като 
                            // изпрати данните и се събужда след това време ms
#define WAKEUP_ADVANCE 5000 // събуждането става предварително с този интервал милисекунди

#define BMP180_IS_PRESENT
#define RAIN_ENABLED
#define UBAT_ENABLED
#define TX20_ENABLED

#define CHN_ADC_UBAT    0

//Работа с WiFi модула
//Виж коментара в SetTimeout()
CY_ISR_PROTO(TimeoutISR);
uint8 timeoutFlag;
CY_ISR(TimeoutISR)
{
/* ISR Code here */
    timeoutFlag=1;
    Timeout_ClearInterrupt(Timeout_INTR_MASK_CC_MATCH);
}
void SetTimeout(uint16 miliseconds);
uint32 UartReadLine(char *line, uint16 timeout);

//Сензор за дъжд
CY_ISR_PROTO(RainISR);
uint rainCounter;
CY_ISR(RainISR)
{
    rainCounter++;    
}

//Функции за достъп до сензор за атм. налягане и температура
// Bosch BMP180. Интерфейса на сензора е I2C
void BMP180_ReadCalibrationCoefs();
long BMP180_ReadTemperature();
long BMP180_ReadPresure(long temperature, int oss);
uint32 BMP180_ReadReg(uint32 reg);
uint16 BMP180_ReadUInt(uint32 reg);
int16 BMP180_ReadInt(uint32 reg);
void BMP180_WriteByte(uint32 reg, uint32 b);
//Коефициенти за калибриране на BMP180. Стойностите им са фабрично заложени в сензора.
int16 AC1, AC2, AC3, B1, B2, MB, MC, MD;
uint16 AC4, AC5, AC6;

//AM2302
int AM2302_Read();
int16 AM2302_Humidity;
int16 AM2302_Temp;
int8  AM2302_CRC;

//TX20
uint16 windDirection; //0-15
uint16 windSpeed; //0-511

uint8 TX20_Read();

int main()
{
    char rxbuf[64];
    char line[64];
    char macid[9];
    uint32 n;
    uint8 retry;
    char txbuf[240];    
    char str[32];
    int result;
    int16 mVolts;
    uint16 adc;
    uint16 uBat;

    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_Start();
    ADC_IRQ_Disable();
    I2C_Start();
    UART_Start();
    UART_ClearRxBuffer();
    Timeout_Start();
    isr_Timeout_StartEx(TimeoutISR);
    isr_Rain_StartEx(RainISR);
    PinWindCE_Write(1);
    timeoutFlag=0;
    LED_B_Write(1);
    LED_R_Write(0);
    LED_G_Write(1);
    CyDelay(3000);
    
    memset(txbuf, 0x00, sizeof(txbuf));
    rainCounter=0;
       
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //ВАЖНО!!! Ако сензора не работи или е разкачен програмата блокира при опит за четене в I2C_I2CMasterWriteByte()!
#ifdef BMP180_IS_PRESENT    
    BMP180_ReadCalibrationCoefs();    
    long temp, pressure;
#endif

    /*
    char buf[32];    

    for(;;)
    {        
        temp =  BMP180_ReadTemperature();
        pressure = BMP180_ReadPresure(temp,3);
        sprintf(buf,"BMP180: T=%2.0ldC P=%4.0ldhPa\r\n", temp/10, pressure/100);
        UART_UartPutString(buf);
        
        AM2302_Read();
        sprintf(buf,"AM2302: T=%d Rh=%d\r\n", AM2302_Temp/10, AM2302_Humidity/10);
        UART_UartPutString(buf);
    }
    */
    

    for(;;)
    {
CheckAT:        
        /* Проверка дали модула е достъпен
         * Изпраща се АТ команда и се очаква отговор ОК.
         * Ако няма такъв свети червен LED мига два пъти кратко.
         * Периодично през една секунда този опит се повтаря.
         */ 
        while(1)
        {
            UART_ClearRxBuffer();
            UART_PutString("ATE0\r\n"); //вместо АТ команда спирам ехото
            UartReadLine(rxbuf,READ_LINE_TIMEOUT);            
            UartReadLine(rxbuf,READ_LINE_TIMEOUT);//OK,2
            if(strcmp(rxbuf, "OK")==0)
            {
                LED_R_Write(1);
                break;
            }
            LED_R_Write(0);
            CyDelay(250);
            LED_R_Write(1);
            CyDelay(250);
            LED_R_Write(0);
            CyDelay(250);
            LED_R_Write(1);
        }
        
        /* Проверка за връзка към AccessPoint
         * ESP8266 е предварително конфигуриран и се свързва автоматично с AP при първа възможност
         * Ако модула не успява да се свърже с АР червения светодиод мига
         */
        retry=5;
        while(1)
        {
            UART_ClearRxBuffer();
            UART_PutString("AT+CWJAP?\r\n");
            UartReadLine(rxbuf,READ_LINE_TIMEOUT);//+CWJAP:"Etherino","20:55:.........",11,-29      ,44 chars
            if(strncmp(rxbuf, "+CWJAP:\"Etherino\"",17)==0)
            {
                LED_R_Write(1);
                CyDelay(500);
                break;
            }
            LED_R_Write(0);
            CyDelay(500);
            LED_R_Write(1);
            CyDelay(500);
            retry--;
            if(retry==0) goto CheckAT;
        }
        
        //До тук модула вече се е свързал с АР. Светва зелен светодиод
        //Прочитаме IP и MAC
        LED_G_Write(0);
        UART_ClearRxBuffer();
        UART_PutString("AT+CIFSR\r\n");
        UartReadLine(rxbuf,READ_LINE_TIMEOUT);
        UartReadLine(rxbuf,READ_LINE_TIMEOUT);
        if(strncmp(rxbuf,"+CIFSR:STAMAC",13)==0)
        {
            strncpy(macid,&rxbuf[24],8);
            macid[8]=0;
        }
        else strcpy(macid,"00:00:00");
        
        while(1)
        {
            CyDelay(SLEEP_TIME + WAKEUP_ADVANCE);    
            //Тук отново спирам ехото т.к. след DEEP SLEEP се активира само.
            UART_ClearRxBuffer();
            UART_PutString("ATE0\r\n"); //вместо АТ команда спирам ехото
            UartReadLine(rxbuf,READ_LINE_TIMEOUT);            
            UartReadLine(rxbuf,READ_LINE_TIMEOUT);//OK,2
            CyDelay(200);
            //Отваряне на TCP/UDP конекция
            retry=3;
EstablishConnection:            
            UART_ClearRxBuffer();
            /* 
                192.168.1.1 - рутер
                192.168.1.10 - концентратор, статичен IP
                192.168.1.100 - .254 - устройства, DHCP
            */
            //UART_PutString("AT+CIPSTART=\"TCP\",\"192.168.1.10\",8888\r\n"); //TCP
            UART_PutString("AT+CIPSTART=\"UDP\",\"224.0.0.120\",8888\r\n");
            n=3;
            LED_G_Write(1);
            while(UartReadLine(rxbuf,ESTABLISH_CONN_TIMEOUT)==0)
            {
                n--;
                if(n==0)
                {
                    LED_G_Write(1);
                    LED_B_Write(1);
                    LED_R_Write(0);
                    goto CheckAT;
                }
            }
            //CONNECT,7  или ALREADY CONNECTED,17 или no ip,5 или 0 ако не може да я отвори
            
            //CONNECT,7 - връзката е изградена. Обменят се данните и връзката се затваря.
            if(strncmp(rxbuf,"CONNECT",7)==0)
            {
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); //празен ред
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); //ОК
                LED_G_Write(1); //По време на обмен свети син LED
                LED_R_Write(1);
                LED_B_Write(0);
                //ИЗПРАЩАНЕ НА ДАННИ КЪМ КОНЦЕНТРАТОРА
                sprintf(txbuf,"MAC=%s\r\n",macid);
                //BMP180
#ifdef BMP180_IS_PRESENT                
                temp =  BMP180_ReadTemperature();
                pressure = BMP180_ReadPresure(temp,3);
                sprintf(str,"BMP180: T=%2.0ld P=%4.0ldhPa\r\n", temp/10, pressure/100);                
                strcat(txbuf,str);                
#endif                
                //AM2302
                result = AM2302_Read();
                if(result!=0)
                {
                    AM2302_Temp  = -1000;
                    AM2302_Humidity = -1000;
                }
                sprintf(str,"AM2302: T=%d Rh=%d\r\n", AM2302_Temp/10, AM2302_Humidity/10);
                strcat(txbuf, str);                
                //TX20 - вятър
#ifdef TX20_ENABLED                
                result = TX20_Read();
                if(result==0)  sprintf(str,"TX20: Dir=%d Speed=%d\r\n", windDirection, windSpeed);
                else strcpy(str,"TX20: Dir=ERR Speed=ERR\r\n");
                strcat(txbuf, str);                
#endif                
                //Стойноста на брояча за дъщд се праща и се нулира
#ifdef RAIN_ENABLED                
                sprintf(str,"RAIN: %d\r\n",rainCounter);
                strcat(txbuf, str);
                rainCounter=0;
#endif                
                //Напрежение на батерията
#ifdef UBAT_ENABLED
                ADC_StartConvert();
                ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
                adc = ADC_GetResult16(CHN_ADC_UBAT );
                mVolts = ADC_CountsTo_mVolts(CHN_ADC_UBAT, adc);
                uBat = mVolts * 16.0;
                sprintf(str,"Ubat: %d.%d V\r\n", uBat/1000, uBat%1000);                
                strcat(txbuf,str);                
#endif                
                //Изпращане на данните
                strcat(txbuf,"END\r\n");
                UART_ClearRxBuffer();
                sprintf(line,"AT+CIPSEND=%d\r\n",strlen(txbuf));
                UART_PutString(line);
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); //празен ред
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); //ОК
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); // > (курсор)
                UART_PutString(txbuf);
                CyDelay(200);
               
                //Прекратяване на TCP конекция
                UART_ClearRxBuffer();
                UART_PutString("AT+CIPCLOSE\r\n");
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); //празен ред
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); // > (курсор)
                //Приспиване на WIFI модула
                //!ВАЖНО За да се изпълни тази команда трябва да се свържат външно GPIO16 и RESET на ESP8266!
                UART_ClearRxBuffer();
                sprintf(txbuf,"AT+GSLP=%d\r\n",SLEEP_TIME);
                UART_PutString(txbuf);
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); //празен ред
                UartReadLine(rxbuf,READ_LINE_TIMEOUT); // > (курсор)
                        
                LED_G_Write(0);
                LED_B_Write(1);
                continue;
            }
            
            //ALREADY CONNECTED,17 - вече има изградена връзка. Това не би трябвало да е така.
            if(strncmp(rxbuf,"ALREADY CONNECTED",17)==0) 
            {//Затова се затваря и изгражда наново
                CyDelay(400);
                UART_ClearRxBuffer();
                UART_PutString("AT+CIPCLOSE\r\n");
                CyDelay(400);
                goto EstablishConnection;
            }
            //no ip - няма връзка с АР
            if(strncmp(rxbuf,"no ip",5)==0)
            {
                for(n=10 ; n!=0 ; n--)
                {
                    LED_R_Write(0);
                    CyDelay(100);                        
                    LED_R_Write(1);
                    CyDelay(100);                                                
                }
                LED_G_Write(1);
                goto CheckAT;
            }

            /* ESP8266 се опитва да изгради TCP връзка със концентратора. Това отнема по-дълго време ако концентратора не отговори бързо.
             * По време на изграждане на връзката, светва и червения LED. Заедно със зелен цвета става оранжев. 
             */
            LED_R_Write(0);
            if(strncmp(rxbuf,"ERROR",5)==0)
            {   //Опита да се изгради TCP връзка е неуспешен.
                //Мига бързо 10 пъти 
                for(n=10 ; n!=0 ; n--)
                {
                    LED_R_Write(0);
                    CyDelay(100);                        
                    LED_R_Write(1);
                    CyDelay(100);                                                
                }
                retry--;
                if(retry==0) 
                {// проверка дали отговаря на АТ команда

                    LED_G_Write(1);
                    goto CheckAT;            
                }
                goto EstablishConnection;
            }
        }
    }    
}


int AM2302_Read()
{
    int i;
    int timer;
    uint16 mask;
    uint16 humidity, temperature;
    
    //Стартира се запитване към сензора
    HUM_Write(0);
    CyDelay(10);
    HUM_Write(1);
    
    timer = 0;
    //Линията е в 1. Чакаме 20-40мс сензора да свали 0
    while(HUM_Read()==1)
    {
        timer++;
        if(timer>200) return 1; // Сензора не отговаря.
    }
    //Линията е в 0. Чакаме сензора да качи 1 за 80 мс
    timer=0;
    while(HUM_Read()==0)
    {
        timer++;
        if(timer>200) return 1; // Сензора не отговаря.
    }
    //Линията е в 1. Чакаме сензора да започне предаване
    timer=0;
    while(HUM_Read()==1)            //Сензора сваля линията за 50 us
    {
        timer++;
        if(timer>200) return 1;
    }
    //Прочитане на влажност
    humidity=0;
    mask=0x8000;
    for(i=0; i!=16 ; i++)
    {
        //Чакам да се вдигне в 1 - да започне преддаване на бит
        timer=0;
        while(HUM_Read()==0)
        {
            timer++;
            if(timer==200) return 1;
        }
        //Прочитане на бит. Стойност 0 е задържане за 26-28 мс. Стойност 1 е 70 мс.
        timer=0;       
        while(HUM_Read()==1)
        {
            timer++;
            if(timer>200) return 1;
        }
        if(timer>55) humidity |= mask;
        mask = mask>>1;
    }    
    //Прочитане на температура
    temperature=0;
    mask=0x8000;
    for(i=0; i!=16 ; i++)
    {
        //Чакам да се вдигне в 1 - да започне преддаване на бит
        timer=0;
        while(HUM_Read()==0)
        {
            timer++;
            if(timer==200) return 1;
        }
        //Прочитане на бит. Стойност 0 е задържане за 26-28 мс. Стойност 1 е 70 мс.
        timer=0;       
        while(HUM_Read()==1)
        {
            timer++;
            if(timer>200) return 1;
        }
        if(timer>55) temperature |= mask;
        mask = mask>>1;
    }    

    AM2302_Humidity = humidity;
    AM2302_Temp = temperature;
    return 0;
}

uint32 BMP180_ReadReg(uint32 reg)
{
    //Прочита един регистър от ВМР180 сензора за температура и налягане.
    //За да работи i2c трябва глобално да е разрешено прекъсване
    uint32 res;
    I2C_I2CMasterClearStatus(); /* Clear any previous status */
    I2C_I2CMasterSendStart(0x77,I2C_I2C_WRITE_XFER_MODE); //0x77 е i2c адреса на сензора
    I2C_I2CMasterWriteByte(reg);//Toва е адреса на регистъра който да бъде прочетен
    I2C_I2CMasterSendRestart(0x77,I2C_I2C_READ_XFER_MODE);
    res = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    I2C_I2CMasterSendStop();
    return res;
}

int16 BMP180_ReadInt(uint32 reg)
{
    //Прочита цяло число със знак прочитайки 2 регистъра reg и reg+1
    int16 value;
    uint16 msb,lsb;

    msb = (uint16) BMP180_ReadReg(reg);
    lsb = (uint16) BMP180_ReadReg(reg+1);
    value = (msb << 8) | lsb;
    return value;
}

uint16 BMP180_ReadUInt(uint32 reg)
{
    //Прочита цяло число със знак прочитайки 2 регистъра reg и reg+1
    uint16 value;
    uint16 msb,lsb;

    msb = (uint16) BMP180_ReadReg(reg);
    lsb = (uint16) BMP180_ReadReg(reg+1);
    value = (msb << 8) | lsb;
    return value;
}

void BMP180_WriteByte(uint32 reg, uint32 b)
{
    I2C_I2CMasterClearStatus(); /* Clear any previous status */
    I2C_I2CMasterSendStart(0x77,I2C_I2C_WRITE_XFER_MODE); //0x77 е i2c адреса на сензора
    I2C_I2CMasterWriteByte(reg);//Toва е адреса на регистъра който да бъде прочетен
    I2C_I2CMasterWriteByte(b);
    I2C_I2CMasterSendStop();
}

long BMP180_ReadTemperature()
{
    //Връща компенсирана температура в 0.1С
    int16 adc;
    BMP180_WriteByte(0xf4, 0x2e);
    CyDelay(6);
    adc = BMP180_ReadInt(0xF6);
    
    long X1 = ((long)AC5 * ((long)adc - (long)AC6))/32768;
    long X2 = ((long)MC * 2048)/(X1 + (long)MD);
    long T = (X1+X2+8)/16;
    return T;
}

long BMP180_ReadPresure(long temperature, int oss)
{
    uint32 msb, lsb, xlsb;
    long up;

    uint32 delay;
    
    switch (oss)
    {
    case 0:
        delay=6; //ultra low power, 4.5ms
        break;
    case 1:
        delay=9; //standart, 7.5ms
        break;
    case 2:
        delay=15; //high resolution, 13.5ms
        break;
    case 3:
        delay=27; //ultra high resolution, 25.5ms
        break;        
    default:
        delay=32;
    }
    //Записва 0x74 в регистър 0xf4
    BMP180_WriteByte(0xf4, 0x34+(oss<<6)); //oss=1 0 standart oversample
    CyDelay(delay);
    msb = BMP180_ReadReg(0xF6);
    lsb = BMP180_ReadReg(0xF7);
    xlsb = BMP180_ReadReg(0xF8);
    up = (long)(((msb<<16) + (lsb<<8) + xlsb)>>(8-oss));
    
    long B5 = (temperature * 16) - 8; 
    long B6 = B5-4000;
    long X1 = ((long)B2 * ((B6*B6)/4096))/2048;
    long X2 = ((long)AC2*B6)/2048;
    long X3 = (X1+X2);
    long B3 = ((((long)AC1*4+X3)<<oss)+2)/4;
    unsigned long B4 = (unsigned long)AC4 * (unsigned long)(X3+32768)/32768;
    unsigned long B7 = ((unsigned long)up-B3)*(50000>>oss);
    long p;
    if(B7<0x80000000) p=(B7*2)/B4;
    else p = (B7/B4)*2;
    X1 = (p/256)*(p/256);
    X1 = (X1* 3038)/65536;
    X2 = (-7357*p)/65536;
    p=p+(X1+X2+3791)/16;
    
    return p;
}

void BMP180_ReadCalibrationCoefs()
{
    AC1 = BMP180_ReadInt(0xAA);
    AC2 = BMP180_ReadInt(0xAC);
    AC3 = BMP180_ReadInt(0xAE);
    AC4 = BMP180_ReadUInt(0xB0);
    AC5 = BMP180_ReadUInt(0xB2);
    AC6 = BMP180_ReadUInt(0xB4);
    B1 = BMP180_ReadInt(0xB6);
    B2 = BMP180_ReadInt(0xB8);
    MB = BMP180_ReadInt(0xBA);
    MC = BMP180_ReadInt(0xBC);
    MD = BMP180_ReadInt(0xBE);
}

void SetTimeout(uint16 miliseconds)
{
    /*
     * Таймера-брояч Timeout се инкрементира всяка милисекунда. При достигане на стойността зададена с Timeout_WriteCompare() се генерира
     * прекъсване което се отработва в TimeoutISR .  Там флага timeoutFlag става 1. Това е критерия за изтекло време зададено с аргумента miliseconds
     */
        Timeout_Stop();
        timeoutFlag=0;
        Timeout_WriteCompare(miliseconds);
        Timeout_WriteCounter(0);
        Timeout_Start();
}

uint32 UartReadLine(char *line, uint16 timeout)
{
    uint32 rxcounter=0;
    uint8 c;
    
    SetTimeout(timeout);
    //CyGlobalIntEnable;
    while(1)
    {
        c = UART_GetChar();
        if(timeoutFlag) break;
        
        if(c==0) continue;
        if(c=='\n') break;
        if(c=='\r') continue;
        
        *line = c;
        line++;
        rxcounter++;
    }
    *line = 0;
    //CyGlobalIntDisable;
    return rxcounter;
}

uint8 TX20_Read()
{
    /*
    Прочита сензора за сила и посока на вятъра. Сензора връща данните като пакет от 41 бита. Линията стои в нула и предаването почва с преден фронт.
    Времето за един бит е 1.22ms . Битовете са инвертирани. Линията стои в 0В. и става 3.3В което е 0 - стартов бит.
    https://www.esp8266.com/viewtopic.php?f=32&t=10246
    https://www.john.geek.nz/2011/07/la-crosse-tx20-anemometer-communication-protocol/ !!!!!
    http://blog.bubux.de/windsensor-tx20-mit-esp8266/    
    
    функцията връща 0 ако е ок. Тогава прочетените стойности са в глобални променливи.
    връща 1 ако няма отговор от сензора
    връща 2 ако линията за данни е в 1 преди да е подаден Chip Enable
    връща 3 при грешка в данните - start of frame, инвертирани стойности за посока и сила
    връща 4 при  контролана сума
    */    
    uint16 divFor1kHz, speed1, speed2, mask16;
    uint8 frameStart, dir1, dir2, chkSum, chkSumCalc,  n, mask8;

    //Чака се начало на данни от ветромера (преден фронт)
    if(PinWindRX_Read()) return 2; //ГРЕШКА - линията е в 1 преди Chip Enable
    //При липса на таймаут да се излиза с грешка за връзка с ветромера
    SetTimeout(7000);
    PinWindCE_Write(0);
    //CyGlobalIntEnable;        
    while(PinWindRX_Read()==0)
    {
        if(timeoutFlag)
        {
            //Сензора не връща данни - връща 1
            PinWindCE_Write(1);
            return 1;
        }
    }
    //Имаме преден фронт
    //Променя се честотата на ClockTO от 1kHz (Т=1mS) на 1MHz(T=1uS)
    divFor1kHz = ClockTO_GetDividerRegister();
    ClockTO_SetDivider(23);

    //Изчаква се 0.61мс за да сме на средата на първия бит.
    SetTimeout(600); // 0.61 ms
    while(timeoutFlag==0);
    //Приемат се първите 5 бита - Start of Frame. Винаги са 00100
    mask8=1;
    frameStart=0;
    for(n=0; n!=5 ; n++)
    {
        if(PinWindRX_Read()==0)   frameStart |= mask8;
        mask8=mask8<<1;
        SetTimeout(1200); // 1.22 ms
        while(timeoutFlag==0);        
    }
    // Приемат се 4 бита за посока ня вятъра. Първо пристига най-старшият
    mask8=1;
    dir1=0;
    for(n=0; n!=4 ; n++)
    {
        if(PinWindRX_Read()==0)   dir1 |= mask8;
        mask8=mask8<<1;
        SetTimeout(1200); // 1.22 ms
        while(timeoutFlag==0);        
    }
    //Приемат се 12 бита за скорост на вятъра.
    //Старшите 3 бита са винаги 0. Приетата стойност е в 0.1 metre/sec т.е. при макс 511 това е 51.1 м/с
    mask16=1;
    speed1=0;
    for(n=0; n!=12 ; n++)
    {
        if(PinWindRX_Read()==0)   speed1 |= mask16;
        mask16=mask16<<1;
        SetTimeout(1200); // 1.22 ms
        while(timeoutFlag==0);        
    }
    // Приемат се 4 бита за контролна сума. 
    mask8=1;
    chkSum=0;
    for(n=0; n!=4 ; n++)
    {
        if(PinWindRX_Read()==0)   chkSum |= mask8;
        mask8=mask8<<1;
        SetTimeout(1200); // 1.22 ms
        while(timeoutFlag==0);        
    }
    // Приемат се 4 бита за посока ня вятъра, инвертитани. Първо пристига най-старшият
    mask8=1;
    dir2=0;
    for(n=0; n!=4 ; n++)
    {
        if(PinWindRX_Read()==1)   dir2 |= mask8;
        mask8=mask8<<1;
        SetTimeout(1200); // 1.22 ms
        while(timeoutFlag==0);        
    }    
    //Приемат се 12 бита за скорост на вятъра. Първо е най-старшият.
    //Старшите 3 бита са винаги 0. Приетата стойност е в 0.1 metre/sec т.е. при макс 511 това е 51.1 м/с
    mask16=1;
    speed2=0;
    for(n=0; n!=12 ; n++)
    {
        if(PinWindRX_Read()==1)   speed2 |= mask16;
        mask16=mask16<<1;
        SetTimeout(1200); // 1.22 ms
        while(timeoutFlag==0);        
    }
    
    //CyGlobalIntDisable;
    PinWindCE_Write(1);
    windDirection = dir1;
    windSpeed = speed1;    
    //Връща се честотата на 1kHZ
    ClockTO_SetDivider(divFor1kHz);    
    //Проверки    
    if((dir1!=dir2) || (speed1!=speed2)) return 3;
    chkSumCalc = dir1 + (speed1&0x0F) + ((speed1>>4)&0x0F) + ((speed1>>8)&0x0F);
    chkSumCalc &= 0x0F;
    if(chkSum!=chkSumCalc) return 4;
    
    return 0;
}
/* [] END OF FILE */
