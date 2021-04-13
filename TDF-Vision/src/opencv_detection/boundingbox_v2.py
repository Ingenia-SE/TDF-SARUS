import cv2
import matplotlib.pyplot as plt
import numpy as np

img = cv2.imread('./images/cow_dataset/thermal_imgs/left0767.jpg') #La camara RGB va adelantado 1 frame respecto a la termica
cop = img.copy()
original = cv2.imread('./images/cow_dataset/rgb_imgs/left0767.jpg')
# cv2.imshow('image', img)
# cv2.waitKey()
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
# Elegimos el umbral del dron
umbral_bajo = (230, 230,230)
umbral_alto = (255,255,255)
# hacemos la mask y filtramos en la original
mask = cv2.inRange(img, umbral_bajo, umbral_alto)
res = cv2.bitwise_and(img, img, mask=mask)

num = np.unique(mask)
print(num)

# imprimimos los resultados
cv2.imshow('mask', mask)
# cv2.waitKey()
# cv2.imshow('res', res)
# cv2.waitKey()


cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
x,y,x2,y2 = 500,700,0,0
print(len(cnts))
# x,y,w,h = cv2.boundingRect(cnts[0])
# cv2.rectangle(original, (x, y), (x + w, y + h), (0,0,255), 2)
# roi = original[y:y+h, x:x+w]
# cv2.imwrite("roi.jpg", roi)
# cnts = cnts[0] if len(cnts) == 2 else cnts[1]
# print(len(cnts))

cnts = cnts[0] if len(cnts) == 2 else cnts[1]
# print(len(cnts))


for c in cnts:
    a, b, c, d = cv2.boundingRect(c)   
    a2 = a + c
    b2 = b + d
    if a < x:
        x = a
    if b < y:
        y = b
    if a2 > x2:
        x2 = a2
    if b2 > y2:
        y2 = b2
    w = x2 - x
    h = y2 - y
    
# print(str(x) + ' ' + str(y) + ' ' + str(w) + ' ' + str(h))
cv2.rectangle(original, (x, y), (x + w, y + h), (255,255,255), 2)
cv2.rectangle(cop, (x, y), (x + w, y + h), (0,0,255), 2)

    #roi = original[y:y+h, x:x+w]
    #cv2.imwrite("roi"+str(c)+".jpg", roi)
    
cv2.imshow('thermal', cop)
cv2.imshow('rgb', original)
cv2.waitKey()
