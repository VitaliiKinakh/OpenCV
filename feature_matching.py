import cv2
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    # Load image and template as grayscaled images
    # When we use both matplotlib and cv2 it is important to remember
    # that matplotlib stores images in RGB and cv2 stores images in BGR
    image = ""
    template = ""
    img = cv2.imread(template, 0)
    templ= cv2.imread(image, 0)

    # Create orb for matching
    orb = cv2.ORB_create()

    kp1, des1 = orb.detectAndCompute(img,None)
    kp2, des2 = orb.detectAndCompute(templ, None)

    bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

    # Get all the matches
    matches = bf.match(des1, des2)

    # Sort matches - important to sort them - results will be better
    matches = sorted(matches, key = lambda x :x.distance)

    img3 = cv2.drawMatches(img, kp1, templ, kp2, matches[:12], None, flags=2)

    # Show matches with plt
    plt.imshow(img3)
    plt.show()

