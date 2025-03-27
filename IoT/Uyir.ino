#include <Servo.h>

//Red Led
const int road_red_led1=25;
const int road_red_led2=26;
const int rail_red_led1=27;

//Yellow Led
const int road_yellow_led1=28;
const int road_yellow_led2=29;

//Green Led
const int road_green_led1=30;
const int road_green_led2=31;
const int rail_green_led1=32;

//Stop Light
const int stop_led1=33;
const int stop_led2=34;

//Buzzer
const int buzzer1=35;
const int buzzer2=36;

// Define Servo objects
Servo servo1, servo2, servo3, servo4;

// Ultrasonic Sensor Pins
const int trigPin1 = 7, echoPin1 = 6;
const int trigPin2 = 9, echoPin2 = 8;
const int trigPin3 = 11, echoPin3 = 10;
const int trigPin4 = 23, echoPin4 = 22;

// Function to get distance from ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2; // Speed of ultrasonic sound in air is 340 m/s, Convert to cm that is 0.034 cm.
}

void setup() {
    Serial.begin(9600);

    // Attach servos to pins
    servo1.attach(2);
    servo2.attach(3);
    servo3.attach(4);
    servo4.attach(5);

    // Set ultrasonic sensor pins as input/output
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);

    pinMode(road_red_led1, OUTPUT);
    pinMode(road_red_led2, OUTPUT);
    pinMode(rail_red_led1, OUTPUT);
    pinMode(road_yellow_led1, OUTPUT);
    pinMode(road_yellow_led2, OUTPUT);
    pinMode(road_green_led1, OUTPUT);
    pinMode(road_green_led2, OUTPUT);
    pinMode(rail_green_led1, OUTPUT);
    pinMode(stop_led1, OUTPUT);
    pinMode(stop_led2, OUTPUT);
    pinMode(buzzer1, OUTPUT);
    pinMode(buzzer2, OUTPUT);

    // Initialize servos to default positions
    servo1.write(90);
    servo2.write(90);
    servo3.write(0);
    servo4.write(0);
}

void loop() 
{
    int count,i;
    digitalWrite(road_red_led1, LOW);
    digitalWrite(road_red_led2, LOW);
    digitalWrite(rail_red_led1, HIGH);
    digitalWrite(road_yellow_led1, LOW);
    digitalWrite(road_yellow_led2, LOW);  
    digitalWrite(road_green_led1, HIGH);
    digitalWrite(road_green_led2, HIGH);
    digitalWrite(rail_green_led1, LOW);
    noTone(buzzer1); 
    noTone(buzzer2); 
    digitalWrite(stop_led1, LOW);
    digitalWrite(stop_led2, LOW); 

    servo1.write(90);
    servo2.write(90);
    servo3.write(0);
    servo4.write(0);
    delay(2000);
    long distance1 = getDistance(trigPin1, echoPin1);
    count=0;
    if (distance1 < 8) // Sensor 1 detected object - Train's arrival.
    { 
        Serial.println("Object detected, closing all the four LC gates.");
        //Lights Off
        digitalWrite(rail_red_led1, LOW);
        digitalWrite(road_green_led1, LOW);
        digitalWrite(road_green_led2, LOW);
        //Lights On
        digitalWrite(road_yellow_led1, HIGH);
        digitalWrite(road_yellow_led2, HIGH); 
        delay(500);
        //Lights Off
        digitalWrite(road_yellow_led1, LOW);
        digitalWrite(road_yellow_led2, LOW); 
        //Lights On
        digitalWrite(road_red_led1, HIGH);
        digitalWrite(road_red_led2, HIGH);
        digitalWrite(rail_green_led1, HIGH);
        servo1.write(0);
        servo2.write(0);
        servo3.write(90);
        servo4.write(90);

        
        while(count==0)
        {
          delay(2000);
          long distance2 = getDistance(trigPin2, echoPin2);
        
        if (distance2 < 8) // Check Sensor 2 - Object detection between the LC gates.
        {
            Serial.println("Object detected by Ultrasonic Sensor 2, infront of LC GATE 1.\nLC Gate 4 opens to make the object move out from there.");           
            servo4.write(0);
            Serial.println("LC GATE 4 Opened!.");
            delay(5000);
            servo4.write(90);
            Serial.println("LC GATE 4 Closed!.");
            if (getDistance(trigPin2, echoPin2) < 8) 
            {
              Serial.println("still object is detected by Ultrasonic Sensor 2, infront of LC GATE 1, Might be immovable object!.");
              Serial.println("Loco-Pilot Vikram STOP the train Immediately, object stuck at THENI LC");
              Serial.println("Station master Santhanam, object stuck on Track1 at THENI LC delay all the upcoming trains");
              digitalWrite(road_red_led1, HIGH);
              digitalWrite(road_red_led2, HIGH);
              digitalWrite(rail_green_led1, LOW);
              digitalWrite(rail_red_led1, HIGH);
              digitalWrite(stop_led1, HIGH);
              digitalWrite(stop_led2, HIGH); 
              for(i=0; i<3; i++)
              {
                tone(buzzer, 1000);  
                delay(5000);  
                noTone(buzzer);  
                delay(1000); 
              }

            }
            count++;
        } 
        else 
        {
          delay(2000);
          long distance3 = getDistance(trigPin3, echoPin3);
          if (distance3 < 8)  // Check Sensor 3 - Object detection between the LC gates.
          {
            Serial.println("Object detected by Ultrasonic Sensor 3, infront of LC GATE 3.\nLC Gate 2 opens to make the object move out from there.");
            servo2.write(90);
            Serial.println("LC GATE 2 Opened!.");
            delay(5000);
            servo2.write(0);
            Serial.println("LC GATE 2 Closed!.");
            if (getDistance(trigPin3, echoPin3) < 8)
            {
              Serial.println("still object is detected by Ultrasonic Sensor 3, infront of LC GATE 3, Might be immovable object!.");
              Serial.println("Loco-Pilot Vikram STOP the train Immediately, object stuck at THENI LC");
              Serial.println("Station master Santhanam, object stuck on Track1 at THENI LC delay all the upcoming trains");
              digitalWrite(road_red_led1, HIGH);
              digitalWrite(road_red_led2, HIGH);
              digitalWrite(rail_green_led1, LOW);
              digitalWrite(rail_red_led1, HIGH);
              digitalWrite(stop_led1, HIGH);
              digitalWrite(stop_led2, HIGH); 
              for(i=0; i<3; i++)
              {
                tone(buzzer, 1000);  
                delay(5000);  
                noTone(buzzer);  
                delay(1000); 
              }

            }
            count++;
          }
          else
          {
            delay(2000);
            long distance4 = getDistance(trigPin4, echoPin4);
            if (distance4 < 8) // Train's Departure.
            {
              Serial.println("No object is detected by neither Ultrasonic Sensor 2 infront of LC GATE 1 nor Ultrasonic Sensor 3 infront of LC GATE 3.");
              Serial.println("Train 150822 left the THENI LC safely.\nAll the four LC gates opens.");
              digitalWrite(road_red_led1, LOW);
              digitalWrite(road_red_led2, LOW);
              digitalWrite(rail_green_led1, LOW);
              //Lights On
              digitalWrite(road_yellow_led1, HIGH);
              digitalWrite(road_yellow_led2, HIGH); 
              delay(500);
              //Lights Off
              digitalWrite(road_yellow_led1, LOW);
              digitalWrite(road_yellow_led2, LOW); 
              //All gates opened
              servo1.write(90);
              servo2.write(90);
              servo3.write(0);
              servo4.write(0);
              Serial.println("All the four LC gates opened.");
              //Lights On
              digitalWrite(road_green_led1, HIGH);
              digitalWrite(road_green_led2, HIGH);
              digitalWrite(rail_red_led1, HIGH);
              count++;
            }
          }

        }

      }
    }
    delay(500);
}
