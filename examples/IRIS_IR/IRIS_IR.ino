#include <IRremote.h>

int RECV_PIN = 23;
IRrecv irrecv(RECV_PIN);
decode_results results;

//------------------------------------------------------------
//Codes for Infrared Remote Control
//COM-11759 https://www.sparkfun.com/products/retired/11759
//Note: Uncomment out this section if you are using this w/ the older remote.


#define POWER 0x10EFD827
#define A 0x10EFF807
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF
//------------------------------------------------------------

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
  {
    if (results.value == POWER)
    {
      Serial.println("POWER");
    }
    else if (results.value == A)
    {
      Serial.println("A");
    }
    else if (results.value == B)
    {
      Serial.println("B");
    }
    else if (results.value == C)
    {
      Serial.println("C");
    }
    else if (results.value == UP)
    {
      Serial.println("UP");
    }
    else if (results.value == DOWN)
    {
      Serial.println("DOWN");
    }
    else if (results.value == LEFT)
    {
      Serial.println("LEFT");
    }
    else if (results.value == RIGHT)
    {
      Serial.println("RIGHT");
    }
    else if (results.value == SELECT)
    {
      Serial.println("SELECT");
    }
    else {
      Serial.println("IR RECV Code Value Not Defined or Button was Held Down");
    }

    Serial.print("IR RECV Code = 0x ");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}
