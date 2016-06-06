#include <SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);


// connect motor controller pins to Arduino digital pins
// motor one
int enA = 5;
int in3 = 7;
int in4 = 6;

// motor two
int enB = 10;
int in1 = 9;
int in2 = 8;



void setup() {
  
  //Setup usb serial connection to computer
  Serial.begin(9600);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
 
  
 // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 

}

void forward()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  
}

void backword(){
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
}

void motorOff(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnRightForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 10);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
}

void turnLeftForward()
{
 
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 10);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
}



void loop() {
 // check if serial communication is available:
  if (bluetooth.available()){
    int toSend = (int)bluetooth.read();
    Serial.print(toSend);
    
    switch (toSend) {
      //case 1 move the motors forward
      case '1':
        forward();
        bluetooth.print("~forwards");
        break;
      case '2':
        //case 2 move the motors backwords
        backword();
        bluetooth.print("~backwords");
        break;
      
      case '3':
         //case three turn right
         turnRightForward();
         bluetooth.print("~right");
         break;
      case '4':
        //turn left
        turnLeftForward();
        bluetooth.print("~left");
        break;
        
      case '0':
        //turn off -- stop
        motorOff();
        bluetooth.print("~Turning off -- stop");
        break;
        
      default:
        motorOff();
        Serial.print("~Unkown command motors turned off");
        
    }
  }

}
