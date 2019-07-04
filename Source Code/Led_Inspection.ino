#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Defining Analog Pins
int analogpin0 = A0;  
int analogpin5 = A5;

// Defining other variables
float Vin,Vled,I,R,Vr,i;// variable to store the read value

void setup() {
    Serial.begin(9600);           //  setup serial
    pinMode(analogpin5, INPUT); // sets the pin as output
    //LCD identifier
    tft.reset();
    uint16_t identifier = tft.readID();
    if(identifier==0x0101)
    {     
      identifier=0x9341;
       //Serial.println(F("Found 0x9341 LCD driver"));
    }
    tft.begin(identifier);    
}

void loop() {
    for(i=100;i<=255;i=i+5)
    {
      analogWrite(analogpin0,i);   
      Vin = i*5/255;
      Serial.print("voltage input: "); 
      Serial.println(Vin);
      tft.println(" "); 
      Vled = analogRead(analogpin5); // read the input analog pin 5
      Vled= Vled*5/1023;
      Serial.print("voltage across LED: "); 
      Serial.println(Vled); 
      tft.println(" ");
          delay(1000);
  
      if(Vled>0)
      {
        Serial.print("voltage across Resistor: "); 
        Vr = Vin - Vled;
        Serial.println(Vr); 
        I = Vr/220;
        Serial.print("Current in Circuit: "); 
        Serial.println(I,4); 
        Serial.println(" ");       
        delay(1000);
      }
    }
    Serial.print("The resistor required for 20mA: ");
    R = (Vin-Vled)*1000/20;
    Serial.print(R);
    Serial.println(" Ω"); 
    Serial.println(" "); 
    Serial.println(" ");
    //LCD started
    tft.fillScreen(BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(RED);  
    tft.setTextSize(2);   
    tft.println("LED Inspection ");
    tft.println(" "); 
    tft.print("Voltage across LED: ");
    tft.print(Vled);
    tft.println(" V");
    tft.println(" ");
    tft.print("Current in Circuit: "); 
    tft.print(I,4); 
    tft.println(" A");
    tft.println(" ");
    tft.print("The resistor for 20mA current: ");
    tft.print(R);
    tft.println(" Ω");
    delay(2000);
}
