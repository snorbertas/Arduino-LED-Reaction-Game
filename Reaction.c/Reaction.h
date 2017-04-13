// Definitions

// MAX_LEDS is the amount of LED lights you're connecting.
#define MAX_LEDS 9

/* LED_OFFSET is the starting pin for the first LED.
   By default I chose MAX_LED 9 (nine LED lights).
   This means the pins 4, 5, 6, 7, 8, 9, 10, 11, 12.
   are gonna be the 9 output pins for LED lights. */
#define LED_OFFSET 4

/* BUTTON_PIN is the pin for button input.
   By default I chose LED_OFFSET - 1. This means the previous
   pin before the first LED is the button input (in default
   case it's pin #3) */
#define BUTTON_PIN (LED_OFFSET - 1)

#if BUTTON_PIN < 0
#error "The BUTTON_PIN is invalid (less than 0), please fix it before compiling."
#endif

// Pattern types
#define PATTERN_FORWARD 0
#define PATTERN_BACKWARD 1

// Reaction-game goal
#define CENTER_LED 4
#define DEFAULT_TIMER 500

// Global Variables
int pattern_mode = PATTERN_FORWARD;		// Pattern Mode
unsigned long previousMillis = 0;		// Millisecond value from last tick
bool button_pressed = false;			// True if button is pressed
LEDLight leds[MAX_LEDS];				// Array of LED objects
int partic_1, partic_2;					// Position values for 2 particles
int timerMillis = DEFAULT_TIMER;		// Millisecond interval between each tick

// Functions
void UpdatePinStates();					// Updates output pin states
void ResetLEDs();						// Toggles all LED lights OFF
void HandleButton();					// Handle voltage received from button pin
void HandleTick();						// Handles timer tick

// These are self-explanatory
void HandlePatternForward();
void HandlePatternBackward();
