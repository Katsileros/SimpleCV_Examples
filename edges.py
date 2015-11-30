import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('index.jpeg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

#apply Canny edge detection
canny_edges = cv2.Canny(gray,100,200)

#apply laplacian edge detection
laplacian_edges = cv2.Laplacian(gray,cv2.CV_64F)

#apply sobelx, sobely
sobelx = cv2.Sobel(gray,cv2.CV_64F,1,0,ksize=5)
sobely = cv2.Sobel(gray,cv2.CV_64F,0,1,ksize=5)

while(1):
  cv2.imshow('Frozen',img)
  cv2.imshow('Canny',canny_edges)
  cv2.imshow('Laplacian',laplacian_edges)
  cv2.imshow('Sobelx',sobely)
  cv2.imshow('Sobely',sobelx)
  if cv2.waitKey(1) & 0xFF == ord('q'):
        break
