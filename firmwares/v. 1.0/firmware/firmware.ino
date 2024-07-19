#include <iarduino_RTC.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include "display.h"
#include <EEPROM.h>
#include <EncButton.h>

#define INIT_ADDR 1023
#define INIT_KEY 42

#define LEFT_BTN_PIN 2
#define CENTER_BTN_PIN 3
#define RIGHT_BTN_PIN 4
#define HUMIDITY_SENSOR_PIN 5
#define BUZZER_PIN 9
#define LIGHTSENSOR_PIN A1

iarduino_RTC watch(RTC_DS1302, 8, 6, 7);
DHT dht(HUMIDITY_SENSOR_PIN, DHT11);

String deviceName = "Clock";
uint8_t nameLength = sizeof(deviceName)/sizeof(deviceName[0]);
float deviceVersion = 1.0f;
float firmwareVersion = 1.0f;

Button leftBtn(LEFT_BTN_PIN);
Button centerBtn(CENTER_BTN_PIN);
Button rightBtn(RIGHT_BTN_PIN);

struct Settings {
  byte brightness = 255;
  bool quietMode = false;
};

Settings settings;

uint8_t displayShows = 0;
uint8_t choosedOption;
bool stepOnTimeSetup = 0;
uint8_t nowShow = 0;
uint8_t showPoints = 3;
unsigned long timer;
String options[] = {"Time Setting", "Date Setting", "Brightness", "Info", "Reset", "Exit"};
uint8_t options_max = sizeof(options)/sizeof(options[0]);
uint8_t parameterValue;
String parameter;
byte bright;

void check_buttons() {
  leftBtn.tick();
  centerBtn.tick();
  rightBtn.tick();

  if (displayShows == 0) {
    if (leftBtn.hold()) {
      displayShows = 5;
      settings.quietMode = !settings.quietMode;
      if (!settings.quietMode) {
        tone(BUZZER_PIN, 1500, 1000);
      }
      EEPROM.put(0, settings);
      bool workingFunc = show_quiet_mode(settings.quietMode, BUZZER_PIN);
      while (!workingFunc) {}
      displayShows = 0;
    }

    if (leftBtn.click()) {
      if (nowShow > 0) {
        clear();
        nowShow--;
        timer = 0;
        if (!settings.quietMode)
          tone(BUZZER_PIN, 1500, 100);
      }
    }

    if (centerBtn.hold()) {
      displayShows = 1;

      clear();
      choosedOption = 0;
      if (!settings.quietMode)
        tone(BUZZER_PIN, 1500, 500);
      show_settings(choosedOption, options, options_max);
    }

    if (rightBtn.click()) {
      if (nowShow < showPoints) {
        clear();
        nowShow++;
        timer = 0;
        if (!settings.quietMode)
          tone(BUZZER_PIN, 1500, 100);
      }
    }
  }
  else if (displayShows == 1) {
    if (leftBtn.click()) {
      if (choosedOption > 0) {
        choosedOption--;
        if (!settings.quietMode)
          tone(BUZZER_PIN, 1500, 100);
        show_settings(choosedOption, options, options_max);
      }
    }

    if (centerBtn.click()) {
      if (!settings.quietMode)
        tone(BUZZER_PIN, 1500, 100);
      
      String option = options[choosedOption];
      if (option == "Exit") {
        clear();
        displayShows = 0;
      }
      else if (option == "Reset") {
        displayShows = 3;
        clear();
        show_reset_menu(0);
      }
      else if (option == "Brightness") {
        displayShows = 2;
        clear();
        parameter = option;
        parameterValue = round(settings.brightness / 15.9375);
        bright = settings.brightness;

        show_parameter(parameter, parameterValue);
      }
      else if (option == "Time Setting") {
        displayShows = 6;
        clear();
        leftBtn.reset();
        centerBtn.reset();
        rightBtn.reset();
        set_time();
      }
      else if (option == "Date Setting") {
        displayShows = 7;
        clear();
        leftBtn.reset();
        centerBtn.reset();
        rightBtn.reset();
        set_date();
      }
      else if (option == "Info") {
        displayShows = 8;
        clear();
        leftBtn.reset();
        centerBtn.reset();
        rightBtn.reset();
        show_info(0, deviceName, nameLength, deviceVersion, firmwareVersion);
      }
    }
    if (rightBtn.click()) {
      if (choosedOption < options_max - 1) {
        choosedOption++;
        if (!settings.quietMode)
          tone(BUZZER_PIN, 1500, 100);
        show_settings(choosedOption, options, options_max);
      }
    }
  }
  else if (displayShows == 2) {
    static uint32_t holding_timer;

    if (leftBtn.click()) {
      if (parameterValue > 0) {
        parameterValue--;
        bright = (byte)(parameterValue * 15.9375);
        show_parameter(parameter, parameterValue);
        set_brightness(bright);
        if (!settings.quietMode) {
          tone(BUZZER_PIN, 1500, 100);
        }
      }
    }
    
    if (leftBtn.holding()) {
      if (parameterValue > 0 && millis() - holding_timer >= 100) {
        holding_timer = millis();
        parameterValue--;
        bright = (byte)(parameterValue * 15.9375);
        show_parameter(parameter, parameterValue);
        set_brightness(bright);
      }
    }
    
    if (centerBtn.click()) {
      if (!settings.quietMode)
        tone(BUZZER_PIN, 1500, 100);
      
      displayShows = 1;
      clear();
      show_settings(choosedOption, options, options_max);

      if (settings.brightness != bright) {
        settings.brightness = bright;
        EEPROM.put(0, settings);
      }
    }
    if (rightBtn.click()) {
      if (parameterValue < 16) {
        parameterValue++;
        bright = (byte)(parameterValue * 15.9375);
        show_parameter(parameter, parameterValue);
        set_brightness(bright);
        if (!settings.quietMode) {
          tone(BUZZER_PIN, 1500, 100);
        }
      }
    }
    if (rightBtn.holding()) {
      if (parameterValue < 16 && millis() - holding_timer >= 100) {
        holding_timer = millis();
        parameterValue++;
        bright = (byte)(parameterValue * 15.9375);
        show_parameter(parameter, parameterValue);
        set_brightness(bright);
      }
    }
  }
  else if (displayShows == 3) {
    static bool choosedValue;
    if (leftBtn.click()) {
      if (choosedValue == true);
        choosedValue = false;
      show_reset_menu(choosedValue);
      if (!settings.quietMode)
        tone(BUZZER_PIN, 1500, 100);
    }

    if (centerBtn.click()) {
      if (!settings.quietMode)
        tone(BUZZER_PIN, 1500, 100);

      if (choosedValue == true) {
        displayShows = 4;
        clear();
        show_reset_menu(2);
        EEPROM.update(INIT_ADDR, 0);
      }
      else {
        displayShows = 1;
        clear();
        show_settings(choosedOption, options, options_max);
      }
    }
    if (rightBtn.click()) {
      if (choosedValue == false);
        choosedValue = true;
      show_reset_menu(choosedValue);
      if (!settings.quietMode)
        tone(BUZZER_PIN, 1500, 100);
    }
  }
}

uint8_t get_weekday_from_date(uint8_t day, uint8_t month, uint8_t year) {
  uint8_t codes_months[12] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

  uint8_t code_month;
  if ((year % 4 == 0) && (month == 1 || month == 2))
    code_month = codes_months[month - 1] - 1;
  else
    code_month = codes_months[month - 1];
  uint8_t year_code = (6 + year + year / 4) % 7;
  uint8_t weekday = ((day + code_month + year_code) % 7) - 1;
  return weekday;
}

void list_info() {
  static uint8_t point;
  static uint8_t points_count = 3;

  if (leftBtn.click() && point > 0) {
    point--;
    if (!settings.quietMode)
      tone(BUZZER_PIN, 1500, 100);
    clear();
    show_info(point, deviceName, nameLength, deviceVersion, firmwareVersion);
  }
  if (centerBtn.click()) {
    displayShows = 1;
    clear();
    leftBtn.reset();
    centerBtn.reset();
    rightBtn.reset();
    if (!settings.quietMode)
      tone(BUZZER_PIN, 1500, 100);
    show_settings(choosedOption, options, options_max);
  }
  if (rightBtn.click() && point < points_count - 1) {
    point++;
    if (!settings.quietMode) 
      tone(BUZZER_PIN, 1500, 100);
    clear();
    show_info(point, deviceName, nameLength, deviceVersion, firmwareVersion);
  }
}

void set_date() {
  uint8_t days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  static uint8_t day = watch.day;
  static uint8_t month = watch.month;
  static uint8_t year = watch.year;
  static uint8_t nowSet;
  static uint32_t timer;
  static bool isShowing;
  static bool blink;

  if (nowSet == -1) {
    nowSet = 0;
  }

  if (leftBtn.click()) {
    if (!settings.quietMode) 
      tone(BUZZER_PIN, 1500, 100);
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 1:
        if (month > 1) {
          month--;
        }
        break;
      case 2:
        if (day > 1) {
          day--;
        }
        break;
      case 0:
        if (year > 24) {
          year--;
        }
        break;
    }
  }
  if (leftBtn.holding()) {
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 1:
        if (month > 1) {
          month--;
        }
        break;
      case 2:
        if (day > 1) {
          day--;
        }
        break;
      case 0:
        if (year > 24) {
          year--;
        }
        break;
    }
  }
  if (centerBtn.click()) {
    if (!settings.quietMode) 
      tone(BUZZER_PIN, 1500, 100);
    if (nowSet < 2) {
      nowSet++;
    }
    else if (nowSet == 2) {
      nowSet = -1;
      displayShows = 1;
      watch.settime(watch.seconds, watch.minutes, watch.Hours, day, month, year, get_weekday_from_date(day, month, year));
      clear();
      show_settings(choosedOption, options, options_max);
    }
  }
  if (rightBtn.click()) {
    if (!settings.quietMode) 
      tone(BUZZER_PIN, 1500, 100);
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 1:
        if (month < 12) {
          month++;
        }
        break;
      case 2:
        if (year % 4 == 0) {
          if (month == 2) {
            if (day < days_in_months[month - 1] + 1) {
              day++;
            }
          }
          else if (days_in_months[month - 1]) {
            day++;
          }
        }
        else if (day < days_in_months[month - 1]) {
          day++;
        }
        break;
      case 0:
        if (year < 99) {
          year++;
        }
        break;
    }
  }
  if (rightBtn.holding()) {
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 1:
        if (month < 12) {
          month++;
        }
        break;
      case 2:
        if (year % 4 == 0) {
          if ((day < days_in_months[month - 1]) || (month == 2 && day)) {
            day++;
          }
        }
        else if (day < days_in_months[month - 1]) {
          day++;
        }
        break;
      case 0:
        if (year < 99) {
          year++;
        }
        break;
    }
  }
  if (millis() - timer >= 500 && blink) {
    timer = millis();
    isShowing = !isShowing;
  }
  if (millis() - timer >= 500 && !blink) {
    timer = millis();
    blink = true;
  }
  show_date_set(day, month, year, nowSet, isShowing);
}

void set_time() {
  static uint8_t hours = watch.Hours;
  static uint8_t minutes = watch.minutes;
  static uint8_t nowSet;
  static uint32_t timer;
  static bool isShowing;
  static bool blink;

  if (nowSet == -1) {
    nowSet = 0;
  }

  if (leftBtn.click()) {
    if (!settings.quietMode)
      tone(BUZZER_PIN, 1500, 100);
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 0:
        if (hours > 0)
          hours--;
      case 1:
        if (minutes > 0)
          minutes--;
    }
  }
  if (leftBtn.holding()) {
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 0:
        if (hours > 0)
          hours--;
        break;
      case 1:
        if (minutes > 0)
          minutes--;
        break;
    }
  }
  if (centerBtn.click()) {
    if (!settings.quietMode)
      tone(BUZZER_PIN, 1500, 100);
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 0:
        nowSet++;
        break;
      case 1:
        nowSet = -1;
        displayShows = 1;
        watch.settime(0, minutes, hours, watch.day, watch.month, watch.year, watch.weekday);
        clear();
        show_settings(choosedOption, options, options_max);
        break;
    }
  }
  if (rightBtn.click()) {
    if (!settings.quietMode)
      tone(BUZZER_PIN, 1500, 100);
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 0:
        if (hours < 23) 
          hours++;
        break;
      case 1:
        if (minutes < 59) 
          minutes++;
        break;
    }
  }
  if (rightBtn.holding()) {
    blink = false;
    isShowing = true;
    switch (nowSet) {
      case 0:
        if (hours < 23) 
          hours++;
        break;
      case 1:
        if (minutes < 59) 
          minutes++;
        break;
    }
  }
  if (millis() - timer >= 500 && blink) {
    timer = millis();
    isShowing = !isShowing;
  }
  if (millis() - timer >= 500 && !blink) {
    timer = millis();
    blink = true;
  }
  show_time_set(hours, minutes, nowSet, isShowing);
}

void setup() {
  Serial.begin(9600);

  leftBtn.setHoldTimeout(1000);
  centerBtn.setHoldTimeout(2000);
  rightBtn.setHoldTimeout(1000);

  pinMode(HUMIDITY_SENSOR_PIN, INPUT);

  watch.begin();
  dht.begin();
  disp_init();

  show_logo();

  delay(3000);

  clear();
  clock_init();

  if (EEPROM.read(INIT_ADDR) != INIT_KEY) {
    EEPROM.write(INIT_ADDR, INIT_KEY);

    settings.brightness = 255;
    settings.quietMode = 0;
    EEPROM.put(0, settings);

    watch.settime(0, 0, 0, 1, 1, 24, 1);
  }
  else {
    EEPROM.get(0, settings);
  }
  set_brightness(settings.brightness);
}

void loop() {
  check_buttons();
  
  if (displayShows == 0) {
    switch (nowShow) {
      case 0:
        if (millis() - timer >= 500) {
          timer = millis();
          show_time(watch.gettime("H"), watch.gettime("i"));
        }
        break;
      case 1:
        if (millis() - timer >= 1000) {
          timer = millis();
          show_datetime(watch.gettime("H:i:s"), watch.gettime("d-m-Y, D"));
        }
        break;
      case 2:
        if (millis() - timer >= 100) {
          timer = millis();
          show_degrees(dht.readTemperature(), dht.readHumidity());
        }
        break;
    }
  }
  else if (displayShows == 6) {
    set_time();
  }
  else if (displayShows == 7) {
    set_date();
  }
  else if (displayShows == 8) {
    list_info();
  }
}