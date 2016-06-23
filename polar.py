import numpy as np
import cv2

img = cv2.imread('data/circle.png')

img2 = cv2.linearPolar(img,(128,128),128,flags=cv2.INTER_LINEAR+cv2.WARP_FILL_OUTLIERS)

cv2.imshow("img1",img)
cv2.imshow("img2",img2)
cv2.waitKey(0)