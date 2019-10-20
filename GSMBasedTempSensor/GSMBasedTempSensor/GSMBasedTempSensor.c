/******************************************************************************

GSM (SMS) Based Remote Temperature Monitoring System.

Send SMS with content

GET T

To mobile number, you will receive a reply as

Current Temperature XXX C

Where XXX Stands stands for room temperature.

For example if room temperature is 29 degree C then you will receive

Current Temperature 029 C


                                     NOTICE
                                                                        --------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN 
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.

Change Log

29 Mar 2013 -        First Public Version.

WRITTEN BY:
ragilraj

*******************************************************************************/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include <string.h>
#include <stdio.h>

#include "lib/lcd/lcd.h"
#include "lib/adc/adc.h"
#include "lib/lm35/lm35.h"

#include <progsm.h>

void Halt();

int main(void)
{

        //Initialize LCD Module
        LCDInit(LS_NONE);
        
        //Show Intro Message
        LCDWriteFStringXY(0,1,PSTR("By Avinash Gupta"));
        
        LCDWriteFStringXY(0,0,PSTR("GSM (SMS) Based "));
        _delay_ms(1500);
        
        LCDWriteFStringXY(0,0,PSTR("Temperature     "));
        _delay_ms(1500);
        
        LCDWriteFStringXY(0,0,PSTR("Monitoring      "));
        _delay_ms(1500);
        
        LCDClear();
        
        
        //Initialize SIM300 module
        LCDWriteFString(PSTR("Initializing ..."));
        int8_t r= SIM300Init();
        
        _delay_ms(1000);
        
        //Check the status of initialization
        switch(r)
        {
                case SIM300_OK:
                        LCDWriteFStringXY(0,1,PSTR("OK !"));
                        break; 
                case SIM300_TIMEOUT:
                        LCDWriteFStringXY(0,1,PSTR("No response"));
                        Halt();
                case SIM300_INVALID_RESPONSE:
                        LCDWriteFStringXY(0,1,"Inv response");
                        Halt();
                case SIM300_FAIL:
                        LCDWriteFStringXY(0,1,"Fail");
                        Halt();
                default:
                        LCDWriteFStringXY(0,1,"Unknown Error");
                        Halt();        
        }
        
        _delay_ms(1000);
        
        
        
        //Set message format to text
        r= SIM300SetTextMode();
        
        LCDClear();
        LCDWriteFString(PSTR("Set Text Mode .."));
        
        _delay_ms(1000);
        
        //Check the result of above operation
        switch(r)
        {
                case SIM300_OK:
                LCDWriteFStringXY(0,1,PSTR("OK !"));
                break;
                
                case SIM300_TIMEOUT:
                LCDWriteFStringXY(0,1,PSTR("No response"));
                Halt();
                
                case SIM300_FAIL:
                LCDWriteFStringXY(0,1,PSTR("Fail"));
                Halt();
                
                default:
                LCDWriteFStringXY(0,1,PSTR("Unknown Error"));
                Halt();
        }
        
        _delay_ms(1000);
        
        
        //IMEI No display
        LCDClear();
        
        char imei[16];
        
        r=SIM300GetIMEI(imei);
        
        if(r==SIM300_TIMEOUT)
        {
                LCDWriteFString(PSTR("Comm Error !"));
                Halt();
        }
        
        LCDWriteFString(PSTR("Device IMEI:"));
        LCDWriteStringXY(0,1,imei);
        
        _delay_ms(1000);
        
        //Manufacturer ID
        LCDClear();
        
        char man_id[48];
        
        r=SIM300GetManufacturer(man_id);
        
        if(r==SIM300_TIMEOUT)
        {
                LCDWriteFString(PSTR("Comm Error !"));
                Halt();
        }
        
        LCDWriteFString(PSTR("Manufacturer:"));
        LCDWriteStringXY(0,1,man_id);
        
        _delay_ms(1000);
        
        //Model ID
        LCDClear();
        
        char model[48];
        
        r=SIM300GetModel(model);
        
        if(r==SIM300_TIMEOUT)
        {
                LCDWriteFString(PSTR("Comm Error !"));
                Halt();
        }
        
        LCDWriteFString(PSTR("Model:"));
        LCDWriteStringXY(0,1,model);
        
        _delay_ms(1000);
        

        
        //Check Sim Card Presence
        LCDClear();
        LCDWriteFString(PSTR("Checking SIMCard"));
        
        _delay_ms(1000);
        
        r=SIM300IsSIMInserted();
        
        if (r==SIM300_SIM_NOT_PRESENT)
        {
                //Sim card is NOT present
                LCDWriteFStringXY(0,1,PSTR("No SIM Card !"));
                
                Halt();
        }
        else if(r==SIM300_TIMEOUT)
        {
                //Communication Error
                LCDWriteFStringXY(0,1,PSTR("Comm Error !"));
                
                Halt();
        }
        else if(r==SIM300_SIM_PRESENT)
        {
                //Sim card present
                LCDWriteFStringXY(0,1,PSTR("SIM Card Present"));
                        
                _delay_ms(1000);
        }
        
        
        
        //Network search
        LCDClear();
        LCDWriteFStringXY(0,0,PSTR("SearchingNetwork"));
        
        uint8_t                nw_found=0;
        uint16_t        tries=0;
        uint8_t                x=0;
        
        while(!nw_found)
        {
                r=SIM300GetNetStat();
                
                if(r==SIM300_NW_SEARCHING)
                {
                        LCDWriteFStringXY(0,1,PSTR("%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0"));
                        LCDWriteFStringXY(x,1,PSTR("%1"));
                        LCDGotoXY(17,1);
                        
                        x++;
                        
                        if(x==16) x=0;
                        
                        _delay_ms(50);
                        
                        tries++;
                        
                        if(tries==600)        
                                break;
                }
                else
                        break;        
                 
        }
        LCDClear();
        
        if(r==SIM300_NW_REGISTERED_HOME || r==SIM300_NW_REGISTED_ROAMING)
        {
                LCDWriteFString(PSTR("Network Found"));
        }
        else
        {
                LCDWriteFString(PSTR("Cant Connt to NW!"));
                Halt();
        }
        
        _delay_ms(1000);
        
        LCDClear();
        
        //Show Service Provider Name
        char pname[32];
        r=SIM300GetProviderName(pname);
        
        if(r==0)
        {
                LCDWriteFString(PSTR("Comm Error !"));
                Halt();
        }
        
        LCDWriteString(pname);
                
        _delay_ms(1000);
        
        //Temp Sensor
        
        //Init Analog to digital Converter
        InitADC();
        
        LCDClear();
        
        uint8_t id; //holds the slot number where latest msg arrived.
        char oa[20];//Origin Address: the number from where the msg came
        uint8_t ref;//Ref number of msg just sent as reply.
        
        while(1)
        {
                LCDWriteFStringXY(0,0,PSTR("Temperature:    "));
                LCDWriteFStringXY(3,1,PSTR("%5C             "));//Degree Symbol
                
                //Read temperature from sensor
                uint8_t temp = ReadTemperature();
                
                //Display the temperature
                LCDWriteIntXY(0,1,temp,3);
                
                //Wait for request.
                //Show a beating heart on LCD to tell I am alive !
                while(SIM300WaitForMsg(&id)!=SIM300_OK)
                {
                        if(x)
                        {
                                //Draw filled heart
                                LCDWriteStringXY(15,0,"%3");
                                
                                //Change heart state to empty
                                x=0;
                        }
                        else
                        {
                                //Draw empty heart
                                LCDWriteStringXY(15,0,"%4");
                                
                                //Change heart state to full
                                x=1;
                        }
                }

                //Show a down arrow to indicate incoming msg
                LCDWriteStringXY(15,0,"%2");

                _delay_ms(1000);

                //Now read the msg
                char msg[30];

                r=SIM300ReadMsg(id,msg,oa);

                if(r==SIM300_OK)
                {
                        //Request to get temperature
                        if(strcasecmp(msg,"GET T")==0)
                        {
                                char reply_text[40];
                                
                                //Prepare reply
                                sprintf_P(reply_text,PSTR("Current Temperature: %03d C"),temp);
                                
                                //Show up arrow in LCD to indicate msg sending.
                                LCDWriteStringXY(15,0,"%6");
                                
                                //Send reply
                                r=SIM300SendMsg(oa,reply_text,&ref);
                        
                                if(r==SIM300_OK)
                                {
                                        //Show tick mark to indicate msg send success.
                                        LCDWriteStringXY(15,0,"%7");
                                        
                                }
                                else if(r==SIM300_TIMEOUT)
                                {
                                        LCDClear();
                                        LCDWriteFStringXY(0,0,PSTR("Can't Send Reply!"));
                                        LCDWriteFStringXY(0,1,PSTR("Time out !"));
                                        
                                        _delay_ms(3000);                                        
                                }
                                else
                                {
                                        LCDClear();
                                        LCDWriteFStringXY(0,0,PSTR("Can't Send Reply!"));
                                        LCDWriteFStringXY(0,1,PSTR("Fail  !"));
                                        
                                        _delay_ms(3000);                                
                                }
                                
                        }// "Get T" Request Handler END
                        
                        else
                        {
                                //Show up arrow in LCD to indicate msg sending.
                                LCDWriteStringXY(15,0,"%6");
                                
                                //Invalid Choice
                                //Send reply
                                r=SIM300SendMsg(oa,"Invalid Request !",&ref);
                        
                                if(r==SIM300_OK)
                                {
                                        //Show tick mark to indicate msg send success.
                                        LCDWriteStringXY(15,0,"%7");
                                }
                                else if(r==SIM300_TIMEOUT)
                                {
                                        LCDClear();
                                        LCDWriteFStringXY(0,0,PSTR("Can't Send Reply!"));
                                        LCDWriteFStringXY(0,1,PSTR("Time out !"));
                                        
                                        _delay_ms(3000);
                                        
                                        
                                }
                                else
                                {
                                        LCDClear();
                                        LCDWriteFStringXY(0,0,PSTR("Can't Send Reply!"));
                                        LCDWriteFStringXY(0,1,PSTR("Fail  !"));
                                        
                                        _delay_ms(3000);
                                        
                                        
                                }
                        }//Invalid Request Handler END

                }
                else
                {
                        LCDClear();
                        LCDWriteFString(PSTR("Err Reading Msg !"));

                        _delay_ms(3000);

                }

                //Finally delete the msg
                if (SIM300DeleteMsg(id)!=SIM300_OK)
                {
                        LCDWriteFString(PSTR("Err Deleting Msg !"));

                        _delay_ms(3000);
                }
        
                
                _delay_ms(250);
        }
        
        Halt();
}

void Halt()
{
        while(1);
}