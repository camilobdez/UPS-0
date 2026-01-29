// ============================================================
// Microsecond-Accurate Multi-LED Flicker
// Same Brightness, Different Frequencies
// Pins: 3,5,6,9,10
// ============================================================

const int ledPins[] = {9, 3, 5, 6, 10};
const int numLEDs = 5;

// Global brightness (0-255)
float brightness[] = {35.0, 0.0, 35.0, 0.0, 35.0};

// Frequencies in Hz
float freqs[] = {30.0, 37.0, 40.0, 53.0, 50.0};

// Half-periods in microseconds
unsigned long halfPeriodsUs[numLEDs];

unsigned long lastToggleUs[numLEDs];
bool ledState[numLEDs];

void setup() {
    for (int i = 0; i < numLEDs; i++) {
        pinMode(ledPins[i], OUTPUT);

        // Convert frequency to half-period in microseconds
        halfPeriodsUs[i] = (unsigned long)(1e6 / (2.0 * freqs[i]));

        lastToggleUs[i] = micros();
        ledState[i] = false;

        analogWrite(ledPins[i], 0); // start OFF
    }
}

void loop() {
    unsigned long nowUs = micros();

    for (int i = 0; i < numLEDs; i++) {
        if (nowUs - lastToggleUs[i] >= halfPeriodsUs[i]) {
            lastToggleUs[i] = nowUs;

            ledState[i] = !ledState[i];

            if (ledState[i]) {
                analogWrite(ledPins[i], brightness[i]);
            } else {
                analogWrite(ledPins[i], 0);
            }
        }
    }
}

