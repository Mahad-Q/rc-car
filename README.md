# esp32-rc-rover

Prototype of a remote-controlled car built around an ESP32. Team project: Mahad Qureshi and Teran Li are designing the vehicle themselves in SolidWorks, 3D printing it, and writing the firmware. The longer-term goal is a rover that drives itself and maps the areas it travels through.

This is an early prototype, so things change often.

## What works so far

- ESP32 set up with PlatformIO in VS Code
- Drive motors purchased
- First design: car-style layout, rear-wheel drive with front wheels
- Manual control scheme planned: right trigger forward, left trigger reverse, B to brake, with an arming step before it moves

Here is an image of the prototype built and programmed by Mahad:
![Click here to see the image of the first prototype](images/rover1-v1.jpeg)

I decided to use this prototype as a way to test the motor functions, controller connections, and overall hardware connections
- It can be seen how cardboard and tape was used, I decided not to commit to 3D printing a chassis as this was just an initial test
- I did not have any axels for the front wheels so I had to improvise...
    - This resulted in me attaching the wheels to 2 other motors which were not running since, this prototype is a two wheel drive
    - The two 'dead' motors added a lot of resistance to turning so in the video demonstration it can be seen how the front wheels don't really spin

 Here is the video showing some of the basic movement and what was mentioned above:

https://github.com/user-attachments/assets/9a13e001-6e2b-411d-aa3b-0041651c5a4d


## Currently working on

Mahad:
- New chassis design and 3D-printed parts in SolidWorks
- Servo-steering mechanism for the front wheels

Teran
- Adding and programming sensors (ambient temperature, humidity, particulate matter, motion/distance) to the rc-car which can collect environmental data
- This data will be used for the autonomous progamming

## Tech

ESP32, C++ (Arduino framework, PlatformIO), SolidWorks, 3D printing

## Repository layout

```
src/         firmware
docs/        notes
hardware/    parts list
cad/         SolidWorks files
```

## Build and upload

1. Install VS Code and the PlatformIO extension.
2. Open this folder in VS Code.
3. Connect the ESP32 over USB.
4. Build and upload from the PlatformIO toolbar.
