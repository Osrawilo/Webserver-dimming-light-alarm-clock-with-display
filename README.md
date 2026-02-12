# Webserver dimming light alarm clock with display
## This project is about an alarm clock mechanism that uses a web server to trigger a dimmable LED light at a specified timestamp. The idea is to set a time with any HTTP-capable device that is connected to the web server. The web server will trigger the Shelly dimmer to dim the light slowly at the specified time. The display is just for checking the specified dimming time. It is made as an alarm clock to wake you up from sleep.

### used items:
-GC9A01 <br>
-Xiao ESP32C3 <br>
-PlatformIO as IDE in VSCode <br>
-Shelly DALI Dimmer Gen3

## Description of the used components:
### Shelly dimmer:
The Shelly DALI Dimmer Gen3 is a compact DALI gateway/dimmer that acts as a single-master application controller for DALI Part 207 LED control gear, driving connected devices as one group via broadcast commands. It runs from 110–240 V AC and includes an integrated DALI bus power supply (nominal 16 V, short-circuit current < 35 mA), allowing control of up to 5 DALI bus units (externally powered recommended).

### GC9A01 display
The GC9A01 is a compact round TFT LCD controller typically used with 240×240 pixel display and a SPI interface. It supports 16/18-bit color modes, uses standard command-based initialization, and is commonly driven by microcontrollers like ESP32/STM32 via SPI plus control lines (CS/DC/RST).

### ESP32-C3
The Seeed Studio XIAO ESP32C3 is a compact ESP32-C3 dev board featuring a 32-bit RISC-V core, 2.4 GHz Wi-Fi (802.11 b/g/n), and Bluetooth LE. It exposes GPIO for peripherals (e.g., I²C/SPI/UART/PWM) and includes USB-C for power/programming, making it suitable for space-constrained IoT prototyping.

# Warning: Not tested yet!!!
