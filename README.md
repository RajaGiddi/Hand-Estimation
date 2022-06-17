# Hand Estimation Trial
The following is an attempt to create a program that can track both hand motions simply by diplaying them in front of the camera of a laptop. This is my 1st attempt at using **OpenCV** and **Mediapipe** and I hope to use this in future projects such as robotic surgery, prosthetics, sign language processing, and more.

## Summary of modules

- **OpenCV** - A machine learning module that is used for visual processing and applications. Can be used to track movement, detect objects and people, create 3D models of objects based on images, and more. In this case I used OpenCV to connect to my webcam feed to get real-time feed.
- **Mediapipe** - I found about this when looking into ML libraries for Arduino. This library is cross-platform and can be used to for ML image processing. It uses 21 landmarks to track hand movements from a single frame. For information check out:
    - https://learnopencv.com/introduction-to-mediapipe/
    - https://google.github.io/mediapipe/solutions/hands

<img src= "https://google.github.io/mediapipe/images/mobile/hand_landmarks.png">

- **uuid** - Generates a random string for each image so that there are no overlaps between each image
- **os** - I've seen this many times and from what I know it is just an operating system library that makes it easier for cross-platform

# Progress
Just for me to look back and see how far I have come, I will keep track of my progress on **hopefully** a daily basis.

## Day 1: Uhhh...Hand tracking
- ```drawing utilis``` essentially renders the landmarks to your hand.
- ```solutions.hands``` brings in the hands model. 
- ```cv2.cvtColor()``` is a function that you to recolor an image
- ```mpHandsModel.HAND_CONNECTIONS ``` tells what parts are connected (wrist it connected to palm, etc...)
The following is common code to connect to webcam using OpenCV:
```
ss = cv2.VideoCapture(0)   #Might need to play around with this on other devices

while ss.isOpened():   #While connected to the webcam
    ret, frame = ss.read() #reading each frame
    cv2.imshow("Hand Tracking", frame)  #Rendering the image
    
    if cv2.waitKey(10) & 0xFF == ord('q'):  #If I hit 'q', it closes
        break
ss.release()
cv2.destroyAllWindows()
```

So one thing I noticed is that when I set "n" in ```cv2.VideoCapture(n)``` to 0, it opens the back camera on my Surface Pro, however setting n to 1 opened the front camera.

NOTE: Set the frame in ```cv2.imshow("Hand Tracking", frame)``` to img to see the tracking being rendered or else you will see normal feed

Overall, I was able to implement the hand tracking following Nicholas's video + mediapipe documentation


## Day 2: Building a test motor housing model
Tbh, I didn't do much today. I tried, but I got lazy lol. I did make a quick housing model for 5 servos (using FreeCAD). I plan on implementing the code for the servos tommorow and print the model to test it but we shall see. Not as productive as I hoped.

## Day 3: Building the code for motors and WOW MY MIND HURTS
I looked around to see if I can find a template code to work with, turns out a lot of people have been doing it (to which I wasn't surprised) and I was watching this link : https://www.youtube.com/watch?v=7KV5489rL3c to learn more. I already have a 3D model I built with Joseph Rajasekaran so I will use that model and probably include wrist mobility as well to expand on the template provided. Additionally I might also add other features such as force sensation and haptic sensation but that's for a later time. The basic logic for the code is to have a "$" tag that acts as an identifier for the string. So once the "$" is detected, the code will begin to run.
- 0 = close
- 1 = open

### A LOT of ERRORS:
Okay so a lot of things happened and tbh my mind is too fried at the moment to recollect what exactly happened. For starters a lot of errors came. From what I recalled, I did the following things to resolve:
- Had trouble connecting thr right port to the Arduino UNO so I re-routed it COM3 rather than whatever it was set to. This caused errors intitally when I tried to run, verify, or upload any code (https://support.arduino.cc/hc/en-us/articles 360016420140-COM-port-number-changes-when-connecting-board-on-different-ports-or-in-bootloader-mode ; https://forums.engineersgarage.com/forums/topic/avrdude-ser_open-cant-open-device-com4/#:~:text=w%3Aon_off1.hex-,avrdude%3A%20ser_open()%3A%20can't%20open%20device%20%E2%80%9Ccom4%E2%80%9D,semaphore%20timeout%20period%20has%20expired.&text=Hi%2C,number%20accordingly%20in%20the%20avrdude.)
- downgraded opencv to version 4.5.1.48 (https://code.luasoftware.com/tutorials/python/python-pip-downgrade-package/)
- downgraded mediapipe to version 0.8.3.1
- installed cvzone using pip rather than conda (https://pythonlang.dev/repo/cvzone-cvzone/)
- Had trouble importing cvzone modules so I had to downgrade this to version 1.4.1
- Still had trouble with cvzone modules so I imported them as the following way by looking at the github Repo (https://github.com/cvzone/cvzone):
``` from cvzone.{Whatever the module I needed} import {the function I needed}```
- had trouble with openCV in connecting it to camera (https://www.codingforentrepreneurs.com/comments/14722)
```
Rather than:
ss = cv2.VideoCapture(0)
It was:
ss = cv2.VideoCapture(0,cv2.CAP_DSHOW)
```
- ModuleError came for serial and another serial.tools.list_ports module, so I did (https://stackoverflow.com/questions/14108428/pyserial-no-module-named-tools):
```pip install serial``` AND ```pip install pyserial```
- Modified the code to close once I click 'q'

### The Successes:
- Was able to see a 1D array that kept updating hand movement
- Was able to connect the servos to the code
- Was able to modify the handtrack code a bit to fit needs
- Was able to understand a majority of the coding done (had to reference once to https://www.arduino.cc/reference/en/language/variables/data-types/array/ to understand how arrays worked)

## Day 4: Connecting multiple servos
I was able to connect multiple servos to the board and control each servo individual using cvzone. Next, I tried to work with the model I have but it did not work as intended but better than intended. I did have an error initially where it was like:
```
void loop() {

  recievedData();
  if (valsRec[0] == 1) {servoThumb.write(180); }else{ servoThumb.write(0);}
  if (valsRec[0] == 1) {servoIndex.write(180); }else{ servoIndex.write(0);}
  if (valsRec[0] == 1) {servoMiddle.write(180); }else{ servoMiddle.write(0);}
  if (valsRec[0] == 1) {servoRing.write(180); }else{ servoRing.write(0);}
  if (valsRec[0] == 1) {servoPinky.write(180); }else{ servoPinky.write(0);}
  }
```
Rather than this:
```
void loop() {

  recievedData();
  if (valsRec[0] == 1) {servoThumb.write(180); }else{ servoThumb.write(0);}
  if (valsRec[1] == 1) {servoIndex.write(180); }else{ servoIndex.write(0);}
  if (valsRec[2] == 1) {servoMiddle.write(180); }else{ servoMiddle.write(0);}
  if (valsRec[3] == 1) {servoRing.write(180); }else{ servoRing.write(0);}
  if (valsRec[4] == 1) {servoPinky.write(180); }else{ servoPinky.write(0);}
  }
```

After fixing this, the other fingers were routed to work with the motors rather than only the thumb. I believe this is great progress for what I have done so far for the past 4-5 days and will try to do a remodel of the arm in the following months. Till then, signing off (6/10/22 - 6/16/2022)