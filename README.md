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


## Day 2: Working with servos