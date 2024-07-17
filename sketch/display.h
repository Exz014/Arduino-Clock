#include <stdint.h>
#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

void disp_init();
void clear();
bool show_quiet_mode(bool turned_on, uint8_t buzzierPin);
void show_settings(uint8_t choosedOption, String options[], uint8_t options_size);
void show_parameter(String parameter, uint8_t value);
void show_time(String hours, String minutes);
void show_datetime(String time, String date);
void show_degrees(uint8_t degrees, uint8_t humidity);
void set_brightness(byte value);
void show_reset_menu(uint8_t value);
void show_time_set(uint8_t hours, uint8_t minutes, uint8_t nowSet, bool isShowing);
void show_date_set(uint8_t day, uint8_t month, uint8_t year, uint8_t nowSet, bool isShowing);
void show_logo();
void clock_init();