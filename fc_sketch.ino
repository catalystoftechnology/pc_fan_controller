// 4-pin PWM Fan Controller
//
// Author: Sky
//
// Created: 2015-1-1
//
// Updated: 2015-1-3
//
//////////////////////////////////////////////////////////////////

int fanMode = 0;

// Initial Fan Speeds
int frontSpeed = 0;
int rearSpeed = 0;
int radiatorSpeed = 0;

// Button Input Pin
int buttonPin = 2;

// Led Ring Pin (PWM)
int ringPin = 11;
// Default Brightness for LED Ring
int ringBrightness = 225;

// PWM Pins
int rear = 3;
int front_a = 5;
int front_b = 6;
int radiator_a = 9;
int radiator_b = 10;

// Speaker Pin
int speakerPin = A5;

void setup() {
	// led ring output
	pinMode(ringPin, OUTPUT);
	//turn led ring on
	analogWrite(ringPin, ringBrightness);

	//button input
	pinMode(buttonPin, INPUT);

	//pwm pins
	pinMode(rear, OUTPUT);   //rear 120mm
	pinMode(front_a, OUTPUT);   //front 140mm
	pinMode(front_b, OUTPUT);   //front 140mm
	pinMode(radiator_a, OUTPUT);   //radiator 140mm
	pinMode(radiator_b, OUTPUT);  //radiator 140mm

	Serial.begin(9600);
}

void loop() {
	if ( digitalRead(buttonPin) == HIGH ) {

		// Increment the fan mode
		if ( fanMode < 2 ) {
			fanMode++;
		} else {
			fanMode = 0;
		}

		// Set the speed depending on the mode
		switch ( fanMode ) {
			case 0:
				// Silent
				frontSpeed = 40;
				rearSpeed = 150;
				radiatorSpeed = 100;
				break;
			case 1:
				// Optimal
				frontSpeed = 150;
				rearSpeed = 255;
				radiatorSpeed = 200;
				break;
			case 2:
				// Max
				frontSpeed = 255;
				rearSpeed = 255;
				radiatorSpeed = 255;
				break;
			default:
				// Default
				frontSpeed = 0;
				rearSpeed = 0;
				radiatorSpeed = 0;
		}

		// Serial output for debugging
		Serial.print("Front: "); Serial.println(frontSpeed);
		Serial.print("Rear: "); Serial.println(rearSpeed);
		Serial.print("Radiator: "); Serial.println(radiatorSpeed);
		Serial.print("Mode: "); Serial.println(fanMode+1);
		Serial.println();

		// Write the changes to the PWM pins
		analogWrite(front_a, frontSpeed);
		analogWrite(front_b, frontSpeed);
		analogWrite(rear, rearSpeed);
		analogWrite(radiator_a, radiatorSpeed);
		analogWrite(radiator_b, radiatorSpeed);

		// Blink led ring for visual output (also beeps)
		for ( int i = 0; i <= fanMode; i++ ) {
			analogWrite(ringPin, 0);
			for ( int ii = 0; ii < 60; ii++ ) {
				digitalWrite(speakerPin, HIGH);
				delayMicroseconds(400);
				digitalWrite(speakerPin, LOW);
				delayMicroseconds(400);
			}
			delay(18);
			analogWrite(ringPin, 255);
			delay(100);
		}

		// turn led ring back to original state so it's not too bright
		analogWrite(ringPin, ringBrightness);

		// Catch until button released for software debounce
		while ( digitalRead(buttonPin) == HIGH ) {}
		delay(20);
	}
}























