import numpy as np
import cv2

logo = cv2.imread('data/circle.png')

warped = cv2.linearPolar(logo,(128,128),120,flags=cv2.INTER_LINEAR+cv2.WARP_FILL_OUTLIERS)

# grab the dimensions of the image and calculate the center
# of the image
(h, w) = warped.shape[:2]
center = (w / 2, h / 2)

# rotate the image by 180 degrees
M = cv2.getRotationMatrix2D(center, 90, 1.0)
rotated = cv2.warpAffine(warped, M, (w, h))


# perform the actual resizing of the image and show it
dim = (1280,320)
resized = cv2.resize(rotated, dim, interpolation = cv2.INTER_AREA)

cv2.imshow("logo",logo)
cv2.imshow("rotated",resized)
cv2.waitKey(0)