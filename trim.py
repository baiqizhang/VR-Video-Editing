import numpy as np
import cv2

cap = cv2.VideoCapture('bird.mp4')


if cap.isOpened():
    ret, frame = cap.read()
    rows, cols = frame.shape[:2]
#    cv2.namedWindow('frame', cv2.WINDOW_NORMAL)

    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    out = cv2.VideoWriter('output.mov',fourcc, 15.0, (cols,rows))

while(cap.isOpened()):
    ret, frame = cap.read()

#    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    frame[(4*rows/5):rows,:]=0
    
    out.write(frame)
    
#    cv2.imshow('frame',frame)
#    if cv2.waitKey(1) & 0xFF == ord('q'):
#        break

cap.release()
out.release()
cv2.destroyAllWindows()