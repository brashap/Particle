unsigned long duration;

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    pinMode(D7, INPUT);

    // Pulse generator, connect D7 to D8
    // PWM output is 500Hz at 50% duty cycle
    // 1000us HIGH, 1000us LOW
    pinMode(D8, OUTPUT);
    analogWrite(D8, 64);
    Serial.println("Begin");
}

void loop()
{
    duration = pulseIn(D7, HIGH);
    Serial.printlnf("%d us", duration);
    delay(1000);
}