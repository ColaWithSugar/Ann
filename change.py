import matplotlib.pyplot as plt
import numpy as np
import struct
from PIL import Image


def loadImageSet(filename):

    binfile = open(filename, 'rb')
    buffers = binfile.read()

    head = struct.unpack_from('>IIII', buffers, 0)

    offset = struct.calcsize('>IIII')
    imgNum = head[1]
    width = head[2]
    height = head[3]
    bits = imgNum * width * height
    bitsString = '>' + str(bits) + 'B'
    imgs = struct.unpack_from(bitsString, buffers, offset)
    binfile.close()
    imgs = np.reshape(imgs, [imgNum, width * height])
    return imgs, head


def loadLabelSet(filename):
    binfile = open(filename, 'rb')
    buffers = binfile.read()
    head = struct.unpack_from('>II', buffers, 0)
    labelNum = head[1]
    offset = struct.calcsize('>II')
    numString = '>' + str(labelNum) + "B"
    labels = struct.unpack_from(numString, buffers, offset)
    binfile.close()
    labels = np.reshape(labels, [labelNum])
    return labels, head


if __name__ == "__main__":

    file1 = 'MNIST/train-images.idx3-ubyte'
    file2 = 'MNIST/train-labels.idx1-ubyte'
    imgs, data_head = loadImageSet(file1)
    labels, labels_head = loadLabelSet(file2)

    for i in range(10000):
        img = imgs[i].reshape(28, 28)
        print(labels[i])
        img = np.array(img, dtype='uint8')
        img_save = Image.fromarray(img)
        num = labels[i]
        num = str(i)
        txt = open("ans/ans_" + num + ".txt", "w")
        txt.write(str(labels[i]))
        txt.close()
        Str = "test_" + num
        filename = "graph/" + Str + ".bmp"
        img_save.save(filename, "bmp")
    print("Done")