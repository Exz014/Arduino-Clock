#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "display.h"

#define LCD_BRIGHTNESS_PIN 10

static LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t LT[8] = {0b00111,  0b01111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
uint8_t UB[8] = {0b11111,  0b11111,  0b11111,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000};
uint8_t RT[8] = {0b11100,  0b11110,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
uint8_t LL[8] = {0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b01111,  0b00111};
uint8_t LB[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111};
uint8_t LR[8] = {0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11110,  0b11100};
uint8_t UMB[8] = {0b11111,  0b11111,  0b11111,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111};
uint8_t LMB[8] = {0b11111,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111};

uint8_t LTL[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00111, 0b01111};
uint8_t MTL[8] = {0b00100, 0b01110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t RTL[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b11100, 0b11110};
uint8_t LBL[8] = {0b01111, 0b00111, 0b00011, 0b00001, 0b00000, 0b00000, 0b00000, 0b00000};
uint8_t MBL[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b01110, 0b00100};
uint8_t RBL[8] = {0b11110, 0b11100, 0b11000, 0b10000, 0b00000, 0b00000, 0b00000, 0b00000};

void show_logo() {
  lcd.createChar(0, LTL);
  lcd.createChar(1, MTL);
  lcd.createChar(2, RTL);
  lcd.createChar(3, LBL);
  lcd.createChar(4, MBL);
  lcd.createChar(5, RBL);

  lcd.setCursor(1, 0);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.print("Exz0");
  lcd.setCursor(1, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.print("Technologies");
}

void draw_number(uint8_t num, uint8_t column) {
  switch (num) {
    case 0:
      lcd.setCursor(column, 0);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.write(3);
      lcd.write(4);
      lcd.write(5);
      break;
    case 1:
      lcd.setCursor(column, 0);
      lcd.print(" ");
      lcd.write(1);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.print(" ");
      lcd.print(" ");
      lcd.write(5);
      break;
    case 2:
      lcd.setCursor(column, 0);
      lcd.write(6);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.write(3);
      lcd.write(7);
      lcd.write(7);
      break;
    case 3:
      lcd.setCursor(column, 0);
      lcd.write(6);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.write(7);
      lcd.write(7);
      lcd.write(5);
      break;
    case 4:
      lcd.setCursor(column, 0);
      lcd.write(3);
      lcd.write(4);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.print(" ");
      lcd.print(" ");
      lcd.write(5);
      break;
    case 5:
      lcd.setCursor(column, 0);
      lcd.write(0);
      lcd.write(6);
      lcd.write(6);
      lcd.setCursor(column, 1);
      lcd.write(7);
      lcd.write(7);
      lcd.write(5);
      break;
    case 6:
      lcd.setCursor(column, 0);
      lcd.write(0);
      lcd.write(6);
      lcd.write(6);
      lcd.setCursor(column, 1);
      lcd.write(3);
      lcd.write(7);
      lcd.write(5);
      break;
    case 7:
      lcd.setCursor(column, 0);
      lcd.write(1);
      lcd.write(1);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.print(" ");
      lcd.write(0);
      lcd.print(" ");
      break;
    case 8:
      lcd.setCursor(column, 0);
      lcd.write(0);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.write(3);
      lcd.write(7);
      lcd.write(5);
      break;
    case 9:
      lcd.setCursor(column, 0);
      lcd.write(0);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(column, 1);
      lcd.write(7);
      lcd.write(7);
      lcd.write(5);
      break;
  }
}

void clock_init() {
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
}

void disp_init() {
  lcd.init();
  lcd.backlight();
  pinMode(LCD_BRIGHTNESS_PIN, OUTPUT);
  set_brightness(255);
  lcd.clear();
}

void clear() {
  lcd.clear();
}

bool show_quiet_mode(bool turned_on, uint8_t buzzierPin) {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Quiet mode");
  switch (turned_on) {
    case 0:
      lcd.setCursor(4, 1);
      lcd.print("DISABLED");
      break;
    case 1:
      lcd.setCursor(5, 1);
      lcd.print("ENABLED");
      break;
  }
  delay(1500);
  lcd.clear();
  return true;
}

void show_settings(uint8_t choosedOption, String options[], uint8_t options_size) {
  lcd.setCursor(4, 0);
  lcd.print("SETTINGS");
  
  lcd.setCursor(0, 1);
  if (choosedOption > 0) {
    lcd.print("<");
  }
  else {
    lcd.print(" ");
  }
  uint8_t x = (uint8_t)((16 - options[choosedOption].length()) / 2);
  for (int i = 0; i < x; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(x, 1);
  lcd.print(options[choosedOption]);
  for (int i = 0; i < (x + options[choosedOption].length()) - 1; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(15, 1);
  if (choosedOption < options_size - 1) {
    lcd.print(">");
  }
  else {
    lcd.print(" ");
  }
}

void show_reset_menu(uint8_t value) {
  if (value < 2) {
    lcd.setCursor(0, 0);
    lcd.print("Reset to defaults");
    lcd.setCursor(1, 1);
    lcd.print("No");
    lcd.setCursor(12, 1);
    lcd.print("Yes");
    if (!value) {
      lcd.setCursor(0, 1);
      lcd.write(126);
      lcd.setCursor(3, 1);
      lcd.write(127);
      lcd.setCursor(11, 1);
      lcd.print(" ");
      lcd.setCursor(15, 1);
      lcd.print(" ");
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(3, 1);
      lcd.print(" ");
      lcd.setCursor(11, 1);
      lcd.write(126);
      lcd.setCursor(15, 1);
      lcd.write(127);
    }
  }
  else if (value >= 2) {
    lcd.setCursor(1, 0);
    lcd.print("Please restart");
    lcd.setCursor(3, 1);
    lcd.print("your clock");
  }
}

void show_parameter(String parameter, uint8_t value) {
  uint8_t x = (uint8_t)((16 - parameter.length()) / 2);
  lcd.setCursor(x, 0);
  lcd.print(parameter);
  lcd.setCursor(0, 1);
  for (int i = 0; i < value; i++) {
    lcd.write(255);
  }
  for (int i = 0; i < 16 - value; i++) {
    lcd.print(" ");
  }
}

void set_brightness(byte value) {
  analogWrite(LCD_BRIGHTNESS_PIN, value);
}

void show_date_set(uint8_t day, uint8_t month, uint8_t year, uint8_t nowSet, bool isShowing) {
  switch (nowSet) {
    case 1:
      if (isShowing) {
        if (month < 10) {
          draw_number(0, 1);
          draw_number(month, 5);
        } else {
          draw_number((uint8_t)(month / 10), 1);
          draw_number(month % 10, 5);
        }
      } else {
        lcd.setCursor(0, 0);
        for (int i = 0; i < 9; i++) {
          lcd.print(" ");
        }
        lcd.setCursor(0, 1);
        for (int i = 0; i < 9; i++) {
          lcd.print(" ");
        }
      }
      lcd.setCursor(8, 1);
      lcd.print(".");
      if (day < 10) {
        draw_number(0, 9);
        draw_number(day, 13);
      }
      else {
        draw_number((uint8_t)(day / 10), 9);
        draw_number(day % 10, 13);
      }
      break;
    case 2:
      if (month < 10) {
        draw_number(0, 1);
        draw_number(month, 5);
      }
      else {
        draw_number((uint8_t)(month / 10), 1);
        draw_number(month % 10, 5);
      }
      lcd.setCursor(8, 1);
      lcd.print(".");
      if (isShowing) {
        if (day < 10) {
          draw_number(0, 9);
          draw_number(day, 13);
        }
        else {
          draw_number((uint8_t)(day / 10), 9);
          draw_number(day % 10, 13);
        }
      }
      else {
        lcd.setCursor(9, 0);
        for (int i = 0; i < 8; i++) {
          lcd.print(" ");
        }
        lcd.setCursor(9, 1);
        for (int i = 0; i < 8; i++) {
          lcd.print(" ");
        }
      }
      break;
    case 0:
      draw_number(2, 1);
      draw_number(0, 5);
      draw_number((uint8_t)(year / 10), 9);
      draw_number(year % 10, 13);
      break;
  }
}

void show_time_set(uint8_t hours, uint8_t minutes, uint8_t nowSet, bool isShowing) {
  switch (nowSet) {
    case 0:
      if (isShowing) {
        if (hours < 10) {
          draw_number(0, 1);
          draw_number(hours, 5);
        }
        else {
          draw_number((uint8_t)(hours / 10), 1);
          draw_number(hours % 10, 5);
        }
      }
      else {
        lcd.setCursor(0, 0);
        for (int i = 0; i < 9; i++) {
          lcd.print(" ");
        }
        lcd.setCursor(0, 1);
        for (int i = 0; i < 9; i++) {
          lcd.print(" ");
        }
      }
      lcd.setCursor(8, 0);
      lcd.print(".");
      lcd.setCursor(8, 1);
      lcd.print(".");
      if (minutes < 10) {
        draw_number(0, 9);
        draw_number(minutes, 13);
      }
      else {
        draw_number((uint8_t)(minutes / 10), 9);
        draw_number(minutes % 10, 13);
      }
      break;
    case 1:
      if (hours < 10) {
        draw_number(0, 1);
        draw_number(hours, 5);
      }
      else {
        draw_number((uint8_t)(hours / 10), 1);
        draw_number(hours % 10, 5);
      }
      lcd.setCursor(8, 0);
      lcd.print(".");
      lcd.setCursor(8, 1);
      lcd.print(".");
      if (isShowing) {
        if (minutes < 10) {
          draw_number(0, 9);
          draw_number(minutes, 13);
        }
        else {
          draw_number((uint8_t)(minutes / 10), 9);
          draw_number(minutes % 10, 13);
        }
      }
      else {
        lcd.setCursor(9, 0);
        for (int i = 0; i < 8; i++) {
          lcd.print(" ");
        }
        lcd.setCursor(9, 1);
        for (int i = 0; i < 8; i++) {
          lcd.print(" ");
        }
      }
      break;
  }
}

void show_time(String hours, String minutes) {
  static bool isDotEnabled;
  if (hours.toInt() < 10) {
    draw_number(0, 1);
    draw_number(hours.toInt(), 5);
  }
  else {
    draw_number((uint8_t)(hours.toInt() / 10), 1);
    draw_number(hours.toInt() % 10, 5);
  }
  
  if (minutes.toInt() < 10) {
    draw_number(0, 9);
    draw_number(minutes.toInt(), 13);
  }
  else {
    draw_number((uint8_t)(minutes.toInt() / 10), 9);
    draw_number(minutes.toInt() % 10, 13);
  }

  if (isDotEnabled) {
    lcd.setCursor(8, 0);
    lcd.print(".");
    lcd.setCursor(8, 1);
    lcd.print(".");
  }
  else {
    lcd.setCursor(8, 0);
    lcd.print(" ");
    lcd.setCursor(8, 1);
    lcd.print(" ");
  }
  isDotEnabled = !isDotEnabled;
}
void show_datetime(String time, String date) {
  lcd.setCursor(4, 0);
  lcd.print(time);

  lcd.setCursor(1, 1);
  lcd.print(date);
}
void show_degrees(uint8_t degrees, uint8_t humidity) {
  draw_number((uint8_t)(degrees / 10), 0);
  draw_number(degrees % 10, 3);
  lcd.setCursor(6, 0);
  lcd.print("oC");
  lcd.setCursor(7, 1);
  lcd.print("%");
  if (humidity == 100) {
    draw_number(1, 8);
    draw_number(0, 11);
    draw_number(0, 14);
  }
  else if (humidity >= 10 && humidity <= 99) {
    draw_number((uint8_t)(humidity / 10), 8);
    draw_number(humidity % 10, 11);
  }
}

void show_info(uint8_t point, String deviceName, uint8_t nameLength, float deviceVersion, float firmwareVersion) {
  switch (point) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("Device");
      lcd.setCursor(0, 1);
      lcd.print(deviceName);
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Device");
      lcd.setCursor(0, 1);
      lcd.print("v.");
      lcd.print(deviceVersion, 1);
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Firmware");
      lcd.setCursor(0, 1);
      lcd.print("v.");
      lcd.print(firmwareVersion, 1);
  }
}