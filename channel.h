init(CHANNEL)_PIN

private:
 data

 bool update
 if (update) {
    noInterrupts(); //
    unsigned long w = widthUs; //
    interrupts(); //

    // 1522 -> 2046 maps to 0 -> 100
    // so step size of 5.23, starting at 1523
    test.set_speed((w - 1522) / 5.23);
    Serial.println(w);
    //test.set_speed(0);
  }

  float getdata()