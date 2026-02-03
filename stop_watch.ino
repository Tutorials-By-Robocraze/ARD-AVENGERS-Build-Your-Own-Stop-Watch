#include &lt;Wire.h&gt;
#include &lt;LiquidCrystal_I2C.h&gt;
// Define LCD (I2C address, width, height)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Address is 0x27, 16 columns, 2 rows
// Pin for the button
const int buttonPin = 2;
bool buttonState = false;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
// Stopwatch variables
unsigned long previousMillis = 0;
unsigned long elapsedTime = 0;
bool running = false; // To track if the stopwatch is running
void setup() {
// Start the LCD
lcd.begin(16, 2);
lcd.print(&quot;Stopwatch&quot;);
delay(1000); // Show title for a second
// Set up button pin
pinMode(buttonPin, INPUT_PULLUP); // Button connected to ground, with internal pull-up
// Initial state of stopwatch
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(&quot;00:00:00&quot;);
}
void loop() {
// Read the button state
bool reading = digitalRead(buttonPin);
// Debounce button press
if (reading != lastButtonState) {
lastDebounceTime = millis(); // Reset debounce timer
}
if ((millis() - lastDebounceTime) &gt; debounceDelay) {
if (reading != buttonState) {
buttonState = reading;
// If button is pressed (active low, so we check for LOW)
if (buttonState == LOW) {

if (running) {
// Stop the stopwatch if it&#39;s running
running = false;
} else {
// Start or reset the stopwatch if it&#39;s not running
if (elapsedTime == 0) {
elapsedTime = 0; // Reset time if it&#39;s zero
}
running = true;
}
}
}
}
lastButtonState = reading; // Save the last button state
// Update the stopwatch if it&#39;s running
if (running) {
unsigned long currentMillis = millis();
elapsedTime = currentMillis - previousMillis;
// Convert elapsed time to hours, minutes, seconds
int hours = elapsedTime / 3600000;
int minutes = (elapsedTime % 3600000) / 60000;
int seconds = (elapsedTime % 60000) / 1000;
// Display the time on the LCD
lcd.setCursor(0, 1);
lcd.print(String(hours).padLeft(2, &#39;0&#39;) + &quot;:&quot; +
String(minutes).padLeft(2, &#39;0&#39;) + &quot;:&quot; +
String(seconds).padLeft(2, &#39;0&#39;));
} else {
// Update display when stopwatch is stopped
lcd.setCursor(0, 1);
lcd.print(&quot;Stopped&quot;);
}
}