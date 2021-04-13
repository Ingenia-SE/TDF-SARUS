import cv2
import os
import numpy as np

## Editable parameters based on dataset ##

threshold_low=(230, 230, 230)
threshold_up=(255, 255, 255)

samples=600  # Number of examples (images)
digits=4      # Gazebo name number of difgits
dataset_digits=6	# Dataset name number of digits

#Camera resolution
hres = 1024   
vres = 768

obj = 'person' #Object in image. Example: person

## End ##

count_imgs = 0


for s in range (samples):

	name =''
	res=s
	for i in range (digits):
		name = str(int(res%10)) + name
		res = res/10	
	name_gazebo = 'left' + name + '.jpg'

	img_thermal = cv2.imread('./images/thermal_imgs/'+ name_gazebo) 
	img_rgb = cv2.imread('./images/rgb_imgs/'+ name_gazebo)    
	img_thermal = cv2.cvtColor(img_thermal, cv2.COLOR_BGR2RGB)
	mask = cv2.inRange(img_thermal, threshold_low, threshold_up)
	num = np.unique(mask)
	# print(num)

	# If there at least one living thing in the image
	if len(num) > 1:

		name =''
		res = count_imgs
		for i in range (dataset_digits):
			name = str(int(res%10)) + name
			res = res/10
		name_dataset = name + '.jpg'
		name_txt= name + '.txt'
		count_imgs += 1

		# Open text file to save labels
		path = os.path.normpath('./images/labels/' + name_txt)
		f = open(path, "w")

		cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
		cnts = cnts[0] if len(cnts) == 2 else cnts[1]
		for c in range(len(cnts)):
			x,y,w,h = cv2.boundingRect(cnts[c])
			#print(str(x) + ' ' + str(y) + ' ' + str(w) + ' ' + str(h))
			# Avoid little bboxes
			if w > 3 and h > 3:
				cv2.rectangle(img_rgb, (x, y), (x + w, y + h), (0,0,255), 2)
				param = obj + ' ' + str(x) + ' ' + str(y) + ' ' + str(w) + ' ' + str(h) + '\n'
				f.write(param)
		f.close()
		
		path = os.path.normpath('./images/thermal_imgs/' + name_dataset)                
		img = cv2.imread('./images/thermal_imgs/' + name_gazebo)
		cv2.imwrite(path, img)
		
		path = os.path.normpath('./images/rgb_imgs/' + name_dataset)                
		img = cv2.imread('./images/rgb_imgs/' + name_gazebo)
		cv2.imwrite(path, img)
		
		path = os.path.normpath('./images/bbox_imgs/' + name_dataset)                
		cv2.imwrite(path, img_rgb)
