# PlcAux
## Auxiliary functions to use with Arduino PLC style
## V1.0 ©2023 Juan M. Uribe

---

Some functions commonly used in PLCs sometimes are needed in the Arduino platform.

Here you can find some of them.

---

NOTE: this library is already included in the [ESPPlcTimer](https://github.com/ojmuribe/ESPPlcTimer) library

---

## USAGE

Add the library **"PlcAux.h"** in your project.
Then you can use the follow functions:

### edgeUp //Rising edge detection

    bool edgeUp(bool input, bool &prev);

Returns a boolean value that is true one CPU cycle if the input have chanbe from false to true.
An auxiliary static bool must to be assigned to prev.

Example:

    static bool prev;
    if (edgeUp(digitalRead(GPIO_NUM_13), prev)){
        Serial.println("Rising edge detection");
    }

---

### edgeDown //Falling edge detection

    bool edgeDown(bool input, bool &prev);

Returns a boolean value that is true one CPU cycle if the input have changed form true to false.
An auxiliary static bool must to be assigned to prev.

Example:

    static bool prev;
    if (edgeDown(digitalRead(GPIO_NUM_13), prev)){
      Serial.println("Falling edge detection");
    }

---

### sqPulse //Symmetrical pulse 

    bool sqPulse(uint32_t interval);

Returns a boolean value that is true for half of the specified period
and false for the other half.

Example: blinking at 1Hz

    digitalWrite(LED_BUILDTIN, sqPulse(1000))

---

### asyncPulse //Asymmetrical pulse 

    bool asyncPulse(uint32_t tON, uint32_t tOFF);

Returns a boolean value that is true during the TON specified time
and false during the TOFF specified time.

Example: asymmetrical blinking of 1Hz, led on 300ms

    digitalWrite(LED_BUILDTIN, sqPulse(300, 700))

---

### setBool 

    void setBool(bool &in);

Set true the boolean value passed at in.
The in variable must to be global or have to be declared
static bool if local.

---

### resetBool 

    void resetBool(bool &in);

Set false the boolean value passed at in.
The in variable must to be global or have to be declared
static bool if local.

---

### Set-Reset flip-flop 

    bool setReset(bool setIn, bool resetIn, bool &prev);

When the setIn input is true, the output becomes true.
When the resetIn input is true, the output becomes false.
Reset have priority over set.
An auxiliary static bool must to be assigned to prev.

---

### Reset-Set flip-flop 

    bool ResetSet(bool setIn, bool resetIn, bool &prev);

Works like Set-Reset but here Set have the priority
over Reset.
An auxiliary static bool must to be assigned to prev.

---

### j-k flip-flop 

    bool jk(bool jIn, bool kIn, bool ckIn, bool &prev);

When ckIn is false the output is unchanged.
if ckIn is true, then works like a set-reset flip-flop:
j is set
k is reset
If j and k are both false the output is unchanged,
but if j and k are both true the output changes state.

Example: a push button changes state of an output

    void loop() {
      static bool aux, aux2;
      bool input = edgeUp(digitalRead(GPIO_NUM_12), aux);
      digitalWrite(LED_BUILTIN, jk(input, input, true, aux2));
    };

---

### t flip-flop 

    bool t(bool tIn, bool ckIn, bool &prev);

Works like a j-k flip-flop but with only one input
assigned to both j and k.
When ckIn is false the output is unchanged.
If ckIn is true then when t is false the output in unchanged,
but if t is true the output changes state.
Holding t true and applying a frequency signal to cK
we will obtain an output signal of half the frequency.
(often used as a frecuency divider by 2)

Example: a push button changes state of an output

    void loop() {
      static bool aux, aux2;
      bool input = edgeUp(!digitalRead(GPIO_NUM_12), aux);
      digitalWrite(LED_BUILTIN, t(input, true, aux2));
    };

---

