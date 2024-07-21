# ATTENTION!!!

This is my first project and I had to write some code at the expense of some crutches so PLEASE don't judge too harshly.

# Components for the project

This project was made on the Atmega328P microcontroller represented by the Arduino Nano board. This watch also uses the following list of parts:

* Real time module DS1302 (for time counting when power is off)
* DH11 temperature and humidity sensor module (to detect indoor temperature and humidity)
* Tact button x3 (to control the clock)
* Buzzer (squeaker)
* LCD 1602 display connected via I2C bus (to display time, date and any other information on it)

You will also need a 5V power adapter (you can use a regular smartphone charger), a soldering iron, wires and a case (in my case, cardboard).
We solder according to this scheme
![Scheme for the project](https://github.com/{username}/{repository}/raw/main/scheme/Arduino%20Clock%20Scheme.png)
and then upload [firmware](https://github.com/{username}/{repository}/tree/main/firmwares).

# Clock management

## Clock display

This clock is controlled using three clock buttons; by pressing the left and right buttons you can scroll through the display of time, date, temperature and humidity. Holding the left button turns on the quiet mode, in which the watch will not make a squeak when the button is pressed.

## Display settings

By holding the center button for 2 seconds, a settings menu opens where you can adjust the date and time, brightness, view information about the device and firmware, reset the settings to factory settings, and go back to the watch

## Also

When a new firmware version appears in the repository, the history will indicate which functions appeared in this version.

# History

## v. 1.1

Coming soon...

## v. 1.0

The first version of the firmware includes standard features such as:

* Time display (hours and minutes)
* Display date and time (hours:minutes:seconds in the first line, day-month-year and day of the week in the second)
* Displays indoor temperature and humidity

You can move between these items on the watch using the left and right buttons
This firmware also has settings that can be opened by pressing the middle button for 2 seconds.
The settings have the following options:

* Time setting
* Date setting
* Adjust display brightness
* Information about the device and firmware
* Factory reset
* Exit (well, of course, where would we be without it)

And there is also a hidden trick
If you hold down the left button for a second, the so-called Quiet Mode will turn on.
In this mode, the watch will not make sounds that occur when the button is pressed.

# ВНИМАНИЕ!!!

Это мой первый проект и мне пришлось написать код с некоторыми костылями поэтому, ПОЖАЛУЙСТА, не судите строго.

# Компоненты для проекта

Данный проект сделан на микроконтролере Atmega328P в лице платы Arduino Nano. В данных часах также используется следующий перечень деталей:

* Модуль реального времени DS1302 (для счета времени при отключенном питании)
* Модуль датчика темепературы и влажности DH11 (для определения темепературы и влажности в помещении)
* Тактовая кнопка x3 (для управления часами)
* Зуммер (пищалка)
* Дисплей LCD 1602 подключенный по шине I2C (для отображения на нем времени, даты и всякой другой информации)

Также понадобиться адаптер питания на 5V (можно использовать обычный зарядник для смартфона), паяльник, провода и корпус (в моем случае картон).
Паяем вот по этой схеме
![Схема для проекта](https://github.com/{username}/{repository}/raw/main/scheme/Arduino%20Clock%20Scheme.png)
а затем загружаем ![прошивку](https://github.com/{username}/{repository}/tree/main/firmwares).

# Управление часами

## Отображение часов

Данные часы управляются с помощью трех тактовых кнопок, нажимая левую и правую кнопки можно листать отображение времени, даты, температуры и влажности. Зажав левую кнопку включается тихий режим, в котором часы не будут издавать писк при нажатии кнопки.

## Отображение настроек

Зажав центральную кнопку на 2 секунды, открывается меню настроек в котором можно настроить дату и время, яркость, посмотреть информацию об устройстве и прошивке, сбросить настройки до заводских, и выйти обратно на часы

## Также

При появлении новой версии прошивки в репозитории, в истории будет написано какие функции появились в данной версии.

# История

## v. 1.1

Скоро...

## v. 1.0

Самая первая версия прошивки включает в себя стандартные функции такие как:

* Отображение времени (часы и минуты)
* Отображение даты и времени (часы:минуты:секунды в первой строке, день-номер месяца-год и день недели - во второй)
* Отображение температуры и влажности в помещении

Перемещаться между данными пунктами на часах возможно при помощи левой и правой кнопок
Также в данной прошивке есть настройки, которые можно открыть по зажатию средней кнопки на 2 секунды.
В настройках есть следующие параметры:

* Настройка времени
* Настройка даты
* Настройка яркости дисплея
* Информация о девайсе и прошивке
* Сброс до заводских настроек
* Выход (ну само собой куда без него)

А также есть скрытая фишка
Если зажать на секунду левую кнопку то включиться так называемый Тихий Режим.
В данном режиме часы не будут издавать звуков которые происходят при нажатии кнопки.