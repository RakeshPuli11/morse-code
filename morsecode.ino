#include <Adafruit_NeoPixel.h>

// --- BEGIN DECLARATION (PINS, PIXELS, COLORS, ETC) ---

#define PIN 12 // Data pin number for the NeoPixels
#define NUMPIXELS 100 // Define how many pixels to use
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t red = pixels.Color(255, 63, 5);
uint32_t lightred = pixels.Color(140, 0, 0);
uint32_t off = pixels.Color(0, 0, 0);

uint8_t dit = 60;
uint8_t dah = 180;
uint8_t shogap = 180;
uint8_t medgap = 420;
uint8_t interchar = 60;

// --- END DECLARATION (PINS, PIXELS, COLORS, ETC) ---


int ledPin = 13;

//For letters
char* letters[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

//For Numbers
char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
"-....", "--...", "---..", "----."
};
int dotDelay = 200;

void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  pixels.begin(); // Initialize the NeoPixel library.
  pixels.show();
  pixels.setBrightness(55);

}

void loop() {
  // put your main code here, to run repeatedly:
   convert("Sample string"); // Write your message here!
  char ch;
if (Serial.available())
{
ch = Serial.read(); // read a single letter if (ch >= 'a' && ch <= 'z')
if (ch >= 'a' && ch <= 'z')
{
flashSequence(letters[ch - 'a']);
}
else if (ch >= 'A' && ch <= 'Z') {
flashSequence(letters[ch - 'A']); }
else if (ch >= '0' && ch <= '9') {
flashSequence(numbers[ch - '0']); }
else if (ch == ' ') {
delay(dotDelay * 4);
}
}

}

void flashSequence(char* sequence) {
int i = 0;
while (sequence[i] != NULL) {
        flashDotOrDash(sequence[i]);
i++; }
delay(dotDelay * 3);
}


void flashDotOrDash(char dotOrDash) {
digitalWrite(ledPin, HIGH); if (dotOrDash == '.')
{
    delay(dotDelay);
  }
else // must be a - 
{
delay(dotDelay * 3); }
digitalWrite(ledPin, LOW); delay(dotDelay);
}



/**
 * 
 * Convert messages to morse code
 * 
 */
void convert(String mCode) {
  for (int i = 0; i < mCode.length() + 1; i++) {
    switch (mCode.charAt(i)) {
      case 'a':
        mark(dit);
        mark(dah);
        break;
      case 'b':
        mark(dah);
        mark(dit);
        mark(dit);
        mark(dit);
        break;
      case 'c':
        mark(dah);
        mark(dit);
        mark(dah);
        mark(dit);
        break;
      case 'd':
        mark(dah);
        mark(dit);
        mark(dit);
        break;
      case 'e':
        mark(dit);
        break;
      case 'f':
        mark(dit);
        mark(dit);
        mark(dah);
        mark(dit);
        break;
      case 'g':
        mark(dah);
        mark(dah);
        mark(dit);
        break;
      case 'h':
        mark(dit);
        mark(dit);
        mark(dit);
        mark(dit);
        break;
      case 'i':
        mark(dit);
        mark(dit);
        break;
      case 'j':
        mark(dit);
        mark(dah);
        mark(dah);
        mark(dah);
        break;
      case 'k':
        mark(dah);
        mark(dit);
        mark(dah);
        break;
      case 'l':
        mark(dit);
        mark(dah);
        mark(dit);
        mark(dit);
        break;
      case 'm':
        mark(dah);
        mark(dah);
        break;
      case 'n':
        mark(dah);
        mark(dit);
        break;
      case 'o':
        mark(dah);
        mark(dah);
        mark(dah);
        break;
      case 'p':
        mark(dit);
        mark(dah);
        mark(dah);
        mark(dit);
        break;
      case 'q':
        mark(dah);
        mark(dah);
        mark(dit);
        mark(dah);
        break;
      case 'r':
        mark(dit);
        mark(dah);
        mark(dit);
        break;
      case 's':
        mark(dit);
        mark(dit);
        mark(dit);
        break;
      case 't':
        mark(dah);
        break;
      case 'u':
        mark(dit);
        mark(dit);
        mark(dah);
        break;
      case 'v':
        mark(dit);
        mark(dit);
        mark(dit);
        mark(dah);
        break;
      case 'w':
        mark(dit);
        mark(dah);
        mark(dah);
        break;
      case 'x':
        mark(dah);
        mark(dit);
        mark(dit);
        mark(dah);
        break;
      case 'y':
        mark(dah);
        mark(dit);
        mark(dah);
        mark(dah);
        break;
      case 'z':
        mark(dah);
        mark(dah);
        mark(dit);
        mark(dit);
        break;
      case ' ':
        pause(medgap);
        break;
    }
    pause(shogap);
  }
  eot();
}

/**
 *
 * Display short or long mark
 *
 */
void mark(uint8_t blip) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, red);
  }
  pixels.show();
  delay(blip);
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, off);
  }
  pixels.show();
  delay(1000);
}

/**
 *
 * Pause between a letter or word
 *
 */
void pause(uint8_t wait) {
  delay(600);
  Serial.print(wait);

}

/**
 *
 * Display end of transmission animation
 *
 */
void eot() {

  delay(20000); // 20 second delay after the finished message
}
