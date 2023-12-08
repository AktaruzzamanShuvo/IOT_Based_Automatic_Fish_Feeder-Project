#define BLYNK_TEMPLATE_ID "TMPL6mbYlZwy4"
#define BLYNK_TEMPLATE_NAME "FISH FEEDER"
#define BLYNK_AUTH_TOKEN "8OfoadxsRyOIAgdQTnqwcZ8d7loT35wC"


#define BLYNK_PRINT Serial
#include <time.h>
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

char auth[] = "8OfoadxsRyOIAgdQTnqwcZ8d7loT35wC";

char ssid[] = "Connecting.... Bro";
char pass[] = "114d.bau";
//BTS driver
int r_en1 = D1;
int l_en1 = D2;
int r_pwm1 = D3;
int l_pwm1 = D4;

//time scheduler
int tpin = D5;
int timezone = 6 * 3600;
int dst = 0;


//relay control
int rpin = D6;


// FOR BLYNK APP CONTROL
BLYNK_WRITE(V0)
{
  int value = param.asInt();

  if(value == 1)
  {
    //motor 1
    digitalWrite(r_en1, HIGH);
    digitalWrite(l_en1, HIGH);
    analogWrite(r_pwm1, 60);     // "60" is set to speed down the motor rpm where 255 provides maximum rpm
    analogWrite(l_pwm1, LOW);

    //motor 2
    digitalWrite(rpin, LOW);
    Serial.println("motor ON");
  }
  else if(value == 0)
  {
      //motor 1
     digitalWrite(r_en1, LOW);
     digitalWrite(l_en1, LOW);
     analogWrite(r_pwm1, LOW);     // "60" is set to speed down the motor rpm where 255 provides maximum rpm
     analogWrite(l_pwm1, LOW);

    //motor 2
     digitalWrite(rpin, HIGH);
     Serial.println("motor OFF");
  }
}



void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  //pin define
  pinMode(r_en1, OUTPUT);
  pinMode(l_en1 , OUTPUT);
  pinMode(r_pwm1, OUTPUT);
  pinMode(l_pwm1, OUTPUT);
  pinMode(rpin, OUTPUT);
  
  // real time clock
  pinMode(tpin,OUTPUT);
  digitalWrite(tpin,LOW);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,pass);
  Serial.println();
  
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK"); 

}

void loop()
{
  
  //real time clock function
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

// set time for morning
int a=11 ; //hour
int b= 33 ; //min
int c=1 ; //delay min
//set time for afternoon
int d=11 ;//hour
int e=35 ;//min
int f=1 ;//delay min example if motor will run for 1 min then set f=1;



 // tm_hour== ** and t_min==** ,these star should be changed according to your time
  if( (p_tm->tm_hour == a && p_tm->tm_min >= b && p_tm->tm_min<= b+c))  
  {
     // motor 1 controlling
    digitalWrite(r_en1, HIGH);
    digitalWrite(l_en1, HIGH);
    analogWrite(r_pwm1, 60);     // "60" is set to speed down the motor rpm where 255 provides maximum rpm
    analogWrite(l_pwm1, LOW);
    // motor 2 controlling
    digitalWrite(rpin, LOW);
    Serial.println("motor ON");
    delay(120000);
    digitalWrite(r_en1, LOW);
    digitalWrite(l_en1, LOW);
    analogWrite(r_pwm1,LOW);
    analogWrite(l_pwm1, LOW);  
    digitalWrite(rpin, HIGH);
    Serial.println("motor OFF"); 
  }
  else if((p_tm->tm_hour == d && p_tm->tm_min >= e && p_tm->tm_min<= e+f))
  {
     // motor 1 controlling
    digitalWrite(r_en1, HIGH);
    digitalWrite(l_en1, HIGH);
    analogWrite(r_pwm1, 60);     // "60" is set to speed down the motor rpm where 255 provides maximum rpm
    analogWrite(l_pwm1, LOW);
    // motor 2 controlling
    digitalWrite(rpin, LOW);
    Serial.println("motor ON");

    delay(120000);

    digitalWrite(r_en1, LOW);
    digitalWrite(l_en1, LOW);
    analogWrite(r_pwm1,LOW);
    analogWrite(l_pwm1, LOW);  
    digitalWrite(rpin, HIGH);
    Serial.println("motor OFF"); 
  }

  Blynk.run();
  delay(1000);

}
