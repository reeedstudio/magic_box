// demo of magic box

#include <Streaming.h>
#include <ChainableLED.h>

#define CTRL_I2C    A3
#define CTRL_LED    A2


#define LED_ON()    digitalWrite(CTRL_LED, HIGH)
#define LED_OFF()   digitalWrite(CTRL_LED, LOW)


ChainableLED leds(5, 6, 1);

int state = 0;

int getLight()
{
    int sum = 0;
    
    for(int i=0; i<32; i++)
    {
        sum += analogRead(A5);
    }
    
    cout << (sum>>5) << endl;
    return sum>>5;
}

void setRgb(int r, int g, int b)
{
    leds.setColorRGB(0, r, g, b); 
}

void setup()
{
    Serial.begin(115200);
    
    pinMode(CTRL_I2C, OUTPUT);
    pinMode(CTRL_LED, OUTPUT);
    
    digitalWrite(CTRL_I2C, LOW);
    digitalWrite(CTRL_LED, LOW);
    
    cout << "hello world" << endl;
    
    
    if(getLight() < 120)
    {
        state = 1;
    }
    else
    {
        state = 0;
        setRgb(0, 0, 0);        
    }
}



void loop()
{
    if(getLight() < 120)
    {
        state = 1;
    }
    else
    {
        state = 0;
        setRgb(0, 0, 0);        
    }
    
    lightOn();
}

void lightOn()
{

    if(!state)return;
    
    for(int i=0; i<256; i++)
    {
        setRgb(i, 0, 0);
        delay(10);
    }
    
    for(int i=0; i<256; i++)
    {
        setRgb(255-i, i, 0);
        delay(10);
    }
    
    for(int i=0; i<256; i++)
    {
        setRgb(0, 255-i, i);
        delay(10);
    }
    
    for(int i=0; i<256; i++)
    {
        setRgb(i, 0, 255-i);
        delay(10);
    }
    
    for(int i=0; i<256; i++)
    {
        setRgb(255-i, 0, 0);
        delay(10);
    }
    
    delay(100);
   
    
}

// end file