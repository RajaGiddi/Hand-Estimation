import cv2
from cvzone.HandTrackingModule import HandDetector
#import cvzone
from cvzone.SerialModule import SerialObject

#Connecting to the camera using OpenCV
ss = cv2.VideoCapture(0,cv2.CAP_DSHOW)   #0 = back camera, 1 = front camera ; play around on other devices
detector = HandDetector(maxHands = 2, detectionCon = 0.7)
mySerial = SerialObject("COM3", 9600, 1)
 
while True:
    success, img = ss.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    if lmList:
        fingers = detector.fingersUp()
        print(fingers)
        mySerial.sendData(fingers)
    cv2.imshow("Image", img)
    if cv2.waitKey(10) & 0xFF == ord('q'):  #If I hit 'q', it closes
        break
ss.release()
cv2.destroyAllWindows()