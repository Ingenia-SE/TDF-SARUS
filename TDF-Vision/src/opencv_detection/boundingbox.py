import cv2
import matplotlib.pyplot as plt
import imutils
import numpy as np
img = cv2.imread('./images/wolf_dataset/thermal_imgs/left0600.jpg') #La camara RGB va adelantado 1 frame respecto a la termica
#original = img.copy()
original = cv2.imread('./images/wolf_dataset/rgb_imgs/left0600.jpg')
# cv2.imshow('image', img)
# cv2.waitKey()
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
# Elegimos el umbral del dron
umbral_bajo = (230, 230,230)
umbral_alto = (255,255,255)
# hacemos la mask y filtramos en la original
mask = cv2.inRange(img, umbral_bajo, umbral_alto)
res = cv2.bitwise_and(img, img, mask=mask)

cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)
cnts = sorted(cnts, key=cv2.contourArea, reverse=True)
rect_areas = []
for c in cnts:
    (x, y, w, h) = cv2.boundingRect(c)
    rect_areas.append(w * h)
avg_area = np.mean(rect_areas)

cv2.waitKey()
for c in cnts:
    (x, y, w, h) = cv2.boundingRect(c)
    mask[y:y + h+5, x:x + w+5] = 255
    cnt_area = w * h
    if cnt_area < 0.2 * avg_area:
      mask[y:y + h, x:x + w] = 0

cv2.imshow('mask', mask)
cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)
cnts = sorted(cnts, key=cv2.contourArea, reverse=True)
for c in cnts:
    (x, y, w, h) = cv2.boundingRect(c)
    # print(str(x) + ' ' + str(y) + ' ' + str(w) + ' ' + str(h))
    cv2.rectangle(original, (x, y), (x + w, y + h), (0,0,0), 2)

cv2.imshow('image', original)
cv2.waitKey()
