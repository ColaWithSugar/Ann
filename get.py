import cv2
import numpy as np
import os
for n in range(10000):
  num = str(n)
  img_file_name = "graph/test_" + num + ".bmp"
  img = cv2.imread(img_file_name,0)
  width,height = img.shape
  txt_file_name = "train/test_" + num + ".txt"
  try:
    os.remove(txt_file_name)
  except Exception as e:
    print (e)
  txt = open(txt_file_name, "w")
  for i in range(height):
    for j in range(width):
      txt.write(str(round(img[i, j] / 255, 2)).rjust(4))
      txt.write(" ")
    txt.write("\n")
  txt.close()