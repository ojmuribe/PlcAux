//PlcAux.h
//Auiliary functions to use with Arduino PLC style
//  V1.0 (c)2023 Juan M. Uribe

// Rising edge of a boolean input
bool edgeUp(bool input, bool &prev);

// Falling edge of a boolean input
bool edgeDown(bool input, bool &prev);

// Change status detection
bool changeStatus(bool input, bool &prev);

// Symmetrical pulse of interval ms
bool sqPulse(uint32_t interval);

// Asymmetrical pulse of interval ms
bool asyncPulse(uint32_t tON, uint32_t tOFF);

// Set bit function
void setBool(bool &in);

// Reset bit function
void resetBool(bool &in);

// Set-Reset flip-flop
bool setReset(bool setIn, bool resetIn, bool &prev);

// Reset-Set flip-flop
bool ResetSet(bool setIn, bool resetIn, bool &prev);

// j-k flip-flop
bool jk(bool jIn, bool kIn, bool ckIn, bool &prev);

// t flip-flop
bool t(bool tIn, bool ckIn, bool &prev);

/**********************************************
            Auxiliary functions
***********************************************/

// Rising edge of a boolean
bool edgeUp(bool input, bool &prev)
{
  bool out;

  out = false;
  if ((input != prev) && input)
  {
    out = true;
  }
  prev = input;
  return out;
}

// Falling edge of a boolean
bool edgeDown(bool input, bool &prev)
{
  bool out;

  out = false;
  if ((input != prev) && !input)
  {
    out = true;
  }
  prev = input;
  return out;
}

// Change status detection
bool changeStatus(bool input, bool &prev)
{
  bool out;

  out = false;
  if (input != prev)
    out = true;
  prev = input;
  return out;
}

// Generates a symmetrical pulse of a period of interval ms
bool sqPulse(uint32_t interval)
{
  uint32_t counter = millis() % interval;
  return counter < interval / 2;
}

// Generates an asymmetrical pulse with an ON time of tONms and an OFF time of tOFF ms
bool asyncPulse(uint32_t tON, uint32_t tOFF)
{
  uint32_t counter = millis() % (tON + tOFF);
  return counter < tON;
}

// Set bit function
void setBool(bool &in)
{
  in = true;
}

// Reset bit function
void resetBool(bool &in)
{
  in = false;
}

// Set-Reset flip-flop
bool setReset(bool setIn, bool resetIn, bool &prev)
{
  if (setIn)
    prev = true;

  if (resetIn)
    prev = false;

  return prev;
}

// Reset-Set flip-flop
bool ResetSet(bool setIn, bool resetIn, bool &prev)
{
  if (resetIn)
    prev = false;
  if (setIn)
    prev = true;
  return prev;
}

// j-k flip-flop
bool jk(bool jIn, bool kIn, bool ckIn, bool &prev)
{
  if (ckIn)
  {
    if (jIn && !kIn)
      prev = true;
    if (!jIn && kIn)
      prev = false;
    if (jIn && kIn)
      prev = !prev;
  }
  return prev;
}

// t flip-flop
bool t(bool tIn, bool ckIn, bool &prev)
{
  return jk(tIn, tIn, ckIn, prev);
}
