# Ei pitempää riviä kuin 57 merkkiä. Muuten ei mahdu
# Windows padin puolelle ruudulle.

# Pohja naaman XYZ paikannukseen 2D kamerakuvasta

import cv2
import numpy as np

cap = cv2.VideoCapture(0)
face_cascade = \
    cv2.CascadeClassifier('haarcascade_frontalface_'+\
        'default.xml')
eye_cascade = \
    cv2.CascadeClassifier('haarcascade_eye.xml')

eye_distance = 0

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.3, 5,\
        0, (100, 100), (250, 250))
    
    for (x,y,w,h) in faces:
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)

        roi_gray = gray[y:y+h, x:x+w]
        roi_color = frame[y:y+h, x:x+w]

        eyes = eye_cascade.detectMultiScale(roi_gray,\
            1.3, 5, 0, (40,40), (70,70))
        eyes_x = []

        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color,(ex,ey),\
                (ex+ew,ey+eh),(0,255,0),2)
            eyes_x.append(ex)
        
        if len(eyes_x) == 2:
            if abs(eye_distance - abs(eyes_x[0] - \
                eyes_x[1])) < 10:
                print("Only noise and/or movement")
                print("Face coordinates[x,y,z]:")
                print(x,y,105-abs(eyes_x[0] - eyes_x[1]))
            else:
                print("A likely false detection, "+\
                    "not showing face coordinates")
            eye_distance = abs(eyes_x[0] - eyes_x[1])
        else:
            # Debuggaukseen, jos tulee väärä havainto
            # tai jos ei havaita silmiä
            print("Incorrect amount of eyes detected!"+\
                " Eyes x-coordinates:", eyes_x)
    
    cv2.imshow('Press ESC to exit', frame)
    key = cv2.waitKey(33)
    if key == 27:
        break

cv2.destroyAllWindows()