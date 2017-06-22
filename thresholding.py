import cv2
import numpy as np

if __name__ == "__main__":
    # Load basic image
    filename = ""
    img = cv2.imread(filename)

    # Create coloured threshold
    retval, threshold = cv2.threshold(img, 12, 255, cv2.THRESH_BINARY) # Values can be changed to specific image

    # Create black-white threshold
    # Get gray image
    grayscaled = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    retval_g, threshold_g = cv2.threshold(grayscaled, 12, 255, cv2.THRESH_BINARY)

    # Create adaptive Gaussian threshold
    gaussian_threshold = cv2.adaptiveThreshold(grayscaled, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 115, 1)

    # Create OTSU  threshold
    retval_otsu, threshold_otsu = cv2.threshold(grayscaled, 125, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    # Show original image and threshold
    cv2.imshow('Original',img)
    cv2.imshow('Threshold', threshold)
    cv2.imshow('Gray threshold', threshold_g)
    cv2.imshow('Gaussian threshold', gaussian_threshold)
    cv2.imshow("Otsu threshhold", threshold_otsu)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
