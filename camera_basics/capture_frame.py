import numpy as np
import cv2

cap = cv2.VideoCapture(1)
if(cap.isOpened()!= True):
  print "Cannot open camera"

while(1):
    # Capture frame-by-frame
    ret,frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    hsv= cv2.cvtColor (frame,cv2.COLOR_BGR2HSV)
    # Display the resulting frame
    cv2.imshow('BGR colorspace',frame)
    cv2.imshow('GRAY colorspace',gray)
    cv2.imshow('HSV colorspace',hsv)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
