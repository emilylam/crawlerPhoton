# crawlerPhoton

Basic remote control of an 1/8th crawler using the Particle Photon, a Node.js server,
and a basic html/javascript web interface. (Demo code for EC544 at Boston University.)

## Particle Photon
Compile and flash crawler.ino onto the photon. As for wiring:

|Photon | Crawler|
|:-----:|:------:|
|GND    | GND    |
|VIN    | 5V     |
|D0     | Wheel  | 3.3V logic
|D1     | ESC    | 3.3V logic

The photon also needs to connect to the internet via WiFi. When the Photon connects
to WiFi and the Particle Cloud, the onboard LED breathes cyan. It then calibrates the ESC,
which will beep when calibrated.

## Node.js Server
The server pulls private information from a .env file. Create a
.env file that contains your secrete keys and parameters for Particle:

```
# Secret sauce

DEVICEID=your-photon-id
ACCESSTOKEN=your-particle-access-token
```
Then install dependencies and run the server:
```
npm install
node test.js
```
Code can be modified to run without the html and instead just the terminal interface.

## HTML
The html code should be in the same directory as the node.js server. The server
will pull the html webpage and host it on localhost:3000.
