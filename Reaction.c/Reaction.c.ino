/* NOTE: This is a slightly modified "Patterns.c" code.
   Here's the original: https://github.com/snorbertas/Arduino-LED-Train
   I removed some patterns, kept the forward and backward patterns.
   I also rearranged the colour arrangement and changed the button's
   functionality. */

#include "LED.h"
#include "Reaction.h"

void setup() {
	// Initiate button pin as input mode
	pinMode(BUTTON_PIN, INPUT);
	
	// Initiate LED lights
	for(int i = 0; i < MAX_LEDS; i++){
		// Set pin mode as output for each LED.
		pinMode(i + LED_OFFSET, OUTPUT);
		
		/* Set LED colours
		   This is used to group the LEDs according to their physical colour.
		   You may change this according to your preference/physical arrangement. */
		int colour = YELLOW;
		if(i < CENTER_LED){
			colour = RED;
		} else if (i > CENTER_LED){
			colour = GREEN;
		}
		leds[i].colour = colour;
	}
	leds[0].ToggleOn();
}

void loop() {
	// Get current milliseconds time.
	unsigned long currentMillis = millis();
	
	// Handle voltage received from button pin.
	HandleButton();
	
	// Handle tick (timer).
	if(previousMillis + timerMillis < currentMillis){
		// Remember this as our previous tick.
		previousMillis = currentMillis;
		
		// Handle the patterns.
		HandleTick();
	}
	
	// Update output pin states.
	UpdatePinStates();
}

void UpdatePinStates(){
	// Update states for pins.
	for(int i = 0; i < MAX_LEDS; i++){
		digitalWrite(i + LED_OFFSET, leds[i].state);
	}
}

void ResetLEDs(){
	// Loop trough all LED objects and toggle them off.
	for(int i = 0; i < MAX_LEDS; i++){
		leds[i].ToggleOff();
	}
}

void HandleButton(){
	if(digitalRead(BUTTON_PIN) == HIGH){
		if(button_pressed == false){
			// Button is pressed.
			button_pressed = true;
			if(leds[CENTER_LED].IsOn()){
				// Score! Green light for one second to indicate success			
				ResetLEDs();
				for(int i = 0; i < MAX_LEDS; i++){
					if(leds[i].colour == GREEN){
						leds[i].ToggleOn();
					}
				}
				UpdatePinStates();
				delay(1000);
				
				/* Increase score (speed).
				   By decreasing the timer interval we increase the speed. */
				timerMillis -= 50;
				
				if(timerMillis <= 0){
					// Won :)
					delay(4000);
					ResetLEDs();
				} else {
					// Continue
					ResetLEDs();
					leds[(int)random(0, MAX_LEDS)].ToggleOn();
					pattern_mode = PATTERN_FORWARD;
				}
				
			} else {
				// Fail - Red light for one second to indicate failure
				ResetLEDs();
				for(int i = 0; i < MAX_LEDS; i++){
					if(leds[i].colour == RED){
						leds[i].ToggleOn();
					}
				}
				UpdatePinStates();
				delay(5000);
				
				// Reset score (speed)
				timerMillis = DEFAULT_TIMER;
				
				// Continue
				ResetLEDs();
				leds[(int)random(0, MAX_LEDS)].ToggleOn();
				pattern_mode = PATTERN_FORWARD;
			}
		}
	} else {
		// No voltage received, thus button is no longer pressed.
		button_pressed = false;
	}
}

void HandleTick(){	
	// Handle the patterns according to current mode.
	if(pattern_mode == PATTERN_FORWARD){
		HandlePatternForward();
	} else if(pattern_mode == PATTERN_BACKWARD){
		HandlePatternBackward();
	}
}

void HandlePatternForward(){
	for(int i = 0; i < MAX_LEDS; i++){
		if(leds[i].IsOn()){
			// Turn this LED off.
			leds[i].ToggleOff();
			
			// Turn the next one on
			int next_led = i + 1;
			if(next_led >= MAX_LEDS){
				// Reverse the pattern
				next_led = MAX_LEDS - 2;
				pattern_mode = PATTERN_BACKWARD;
			}
			leds[next_led].ToggleOn();
			
			// Break loop.
			break;
		}
	}
}

void HandlePatternBackward(){
	for(int i = MAX_LEDS - 1; i >= 0; i--){
		if(leds[i].IsOn()){
			// Turn this LED off.
			leds[i].ToggleOff();
			
			// Turn the next one on.
			int next_led = i - 1;
			if(next_led < 0){
				// Reverse the pattern
				next_led = 1;
				pattern_mode = PATTERN_FORWARD;
			}
			leds[next_led].ToggleOn();
			
			// Break loop.
			break;
		}
	}
}