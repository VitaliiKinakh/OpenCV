import numpy as np
import cv2
from matplotlib import pyplot as plt

# This algorithm can be applied to the variety of images, all you need to do is define another image and specific rectangle
if __name__ == "__main__":
    # Load some image
    filename = ""
    img = cv2.imread(filename)
    mask = np.zeros(img.shape[:2],np.uint8)

    # Create background and foreground models
    bgdModel = np.zeros((1,65),np.float64)
    fgdModel = np.zeros((1,65),np.float64)

    # Define rectangle
    rect = (161,79,150,150)

    # Main algorithm
    cv2.grabCut(img,mask,rect,bgdModel,fgdModel,5,cv2.GC_INIT_WITH_RECT)
    mask2 = np.where((mask==2)|(mask==0),0,1).astype('uint8')
    img = img*mask2[:,:,np.newaxis]

    # Show result
    plt.imshow(img)
    plt.colorbar()
    plt.show()