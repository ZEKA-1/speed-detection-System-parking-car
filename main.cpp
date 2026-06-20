#include <LiquidCrystal.h>
#include <Servo.h>

int lcd_pin_1 = 8;
int lcd_pin_2 = 9;
int lcd_pin_3 = 4;
int lcd_pin_4 = 5;
int lcd_pin_5 = 6;
int lcd_pin_6 = 7;

LiquidCrystal lcd(lcd_pin_1, lcd_pin_2, lcd_pin_3,
                  lcd_pin_4, lcd_pin_5, lcd_pin_6);

int trig1 = 22;
int echo1 = 23;

int trig2 = 24;
int echo2 = 25;

int buzzer = 32;

unsigned long t1 = 0;
unsigned long t2 = 0;

bool detected1 = false;
bool detected2 = false;

float distanceBetweenSensors = 0.10;
float speed = 0;
bool speedDetected = false;

Servo servo;

int ir_1 = 26;
int ir_2 = 27;

int pin_led = 31;

int carCount = 0;
int maxCars = 5;

bool ir1_old = 1;
bool ir2_old = 1;

void setup()
{
    Serial.begin(9600);

    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT);

    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT);

    pinMode(ir_1, INPUT);
    pinMode(ir_2, INPUT);

    pinMode(buzzer, OUTPUT);
    pinMode(pin_led, OUTPUT);

    servo.attach(30);
    servo.write(0);

    lcd.begin(16, 2);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Car is Ready");
    delay(2000);
}

void loop()
{

    // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed Detection");

    lcd.setCursor(0, 1);
    lcd.print("Speed: ");
    // lcd.print(speed);
    lcd.print(" m/s");

    digitalWrite(trig1, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);

    long duration1 = pulseIn(echo1, HIGH, 30000);
    float d1 = duration1 * 0.034 / 2;
    delay(10);

    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);

    long duration2 = pulseIn(echo2, HIGH, 30000);
    float d2 = duration2 * 0.034 / 2;

    if (d1 < 25 && detected1 == false)
    {
        t1 = millis();
        detected1 = true;
    }

    if (d2 < 25 && detected1 == true && detected2 == false)
    {
        t2 = millis();
        detected2 = true;

        float timeSec = (t2 - t1) / 1000.0;

        if (timeSec > 0)
        {
            speed = distanceBetweenSensors / timeSec;

            // lcd.clear();
            // lcd.setCursor(0,0);
            // lcd.print("Speed: ");
            // lcd.print(speed);
            // lcd.print(" m/s");

            if (speed < 0.2)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Speed: ");
                lcd.print(speed);
                lcd.print(" m/s");
                lcd.setCursor(0, 1);
                lcd.print("LOW SPEED");
                delay(1000);
            }
            else if (speed < 0.5)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Speed: ");
                lcd.print(speed);
                lcd.print(" m/s");
                lcd.setCursor(0, 1);
                lcd.print("NORMAL SPEED");
                delay(1000);
            }
            else
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Speed: ");
                lcd.print(speed);
                lcd.print(" m/s");
                lcd.setCursor(0, 1);
                lcd.print("HIGH SPEED");

                for (int i = 0; i < 5; i++)
                {
                    digitalWrite(buzzer, HIGH);
                    delay(40);
                    digitalWrite(buzzer, LOW);
                    delay(40);
                }
                delay(1000);
            }

            speedDetected = true;
        }

        delay(1500);

        detected1 = false;
        detected2 = false;
    }

    int ir1 = digitalRead(ir_1);
    int ir2 = digitalRead(ir_2);

    if (ir1 == 0 && ir1_old == 1 && speedDetected == true && carCount < maxCars)
    {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate Opening");

        lcd.setCursor(0, 1);
        lcd.print("Cars:");
        lcd.print(carCount);
        lcd.print("/");
        lcd.print(maxCars);

        for (int a = 0; a <= 90; a++)
        {
            servo.write(a);
            delay(10);
        }

        delay(2000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate Closing");

        lcd.setCursor(0, 1);
        lcd.print("Cars:");
        lcd.print(carCount);
        lcd.print("/");
        lcd.print(maxCars);

        for (int a = 90; a >= 0; a--)
        {
            servo.write(a);
            delay(10);
        }

        carCount++;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate Closing");

        lcd.setCursor(0, 1);
        lcd.print("Cars:");
        lcd.print(carCount);
        lcd.print("/");
        lcd.print(maxCars);

        delay(1000);

        speedDetected = false;
    }

    if (carCount == maxCars)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate not opening!!");
        lcd.setCursor(0, 1);
        lcd.print("garage is full");
        digitalWrite(pin_led, HIGH);
        delay(1000);
        digitalWrite(pin_led, LOW);
    }

    if (ir2 == 0 && ir2_old == 1 && carCount > 0)
    {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate Opening");

        lcd.setCursor(0, 1);
        lcd.print("Cars:");
        lcd.print(carCount);
        lcd.print("/");
        lcd.print(maxCars);

        for (int a = 0; a <= 90; a++)
        {
            servo.write(a);
            delay(10);
        }

        delay(2000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate Closing");

        lcd.setCursor(0, 1);
        lcd.print("Cars:");
        lcd.print(carCount);
        lcd.print("/");
        lcd.print(maxCars);

        for (int a = 90; a >= 0; a--)
        {
            servo.write(a);
            delay(10);
        }

        carCount--;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gate Closing");

        lcd.setCursor(0, 1);
        lcd.print("Cars:");
        lcd.print(carCount);
        lcd.print("/");
        lcd.print(maxCars);

        delay(1000);
    }

    if (ir2 == 0 && carCount == 0)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("not opening Gate");
        lcd.setCursor(0, 1);
        lcd.print("garage is empty");
        delay(1000);
    }

    ir1_old = ir1;
    ir2_old = ir2;

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Cars:");
    lcd.print(carCount);
    lcd.print("/");
    lcd.print(maxCars);
}
