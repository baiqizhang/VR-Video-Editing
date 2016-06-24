import numpy as np
import cv2

visualize = True#False

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
dim = (1280,120)
resized = cv2.resize(rotated, dim, interpolation = cv2.INTER_AREA)



cap = cv2.VideoCapture('data/bird.mp4')

if cap.isOpened():
    ret, frame = cap.read()
    rows, cols = frame.shape[:2]
    print rows,cols

    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    out = cv2.VideoWriter('data/output.mov',fourcc, 15.0, (cols,rows))

    if visualize:
        cv2.namedWindow('frame', cv2.WINDOW_NORMAL)

while(cap.isOpened()):
    ret, frame = cap.read()

    frame[rows-120:rows,:] = resized
    out.write(frame)

    if visualize:
        cv2.imshow('frame',frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
out.release()
cv2.destroyAllWindows()