import numpy as np
import cv2
if __name__ == "__main__":
    filename = ""
    img = cv2.imread(filename, cv2.IMREAD_COLOR)

    # Get value of pixel
    px = img[105, 105]
    cv2.imshow('Image', img)
    print(px)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Change pixel value
    img[105, 105] = [255, 0, 0]
    cv2.imshow('Image cahnged', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Region of image
    roi = img[100:150, 100:150]
    cv2.imshow('Region of image', roi)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Change all values in region
    img[100:150, 100:150] = [255, 255, 255] # White square
    cv2.imshow('Image region changed', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Copy and paste some region
    some_region = img[45:175, 45:175]
    img[0:130, 0:130] = some_region
    cv2.imshow('Image with copy paste', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()