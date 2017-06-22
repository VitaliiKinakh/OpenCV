import cv2
import numpy as np
if __name__ == "__main__":
    # Load some images
    filename1 = ""
    filename2 = ""
    filename3 = ""
    img1 = cv2.imread(filename1)
    img2 = cv2.imread(filename2)

    # Add two images
    add = img1 + img2 # Using this method we just put one image over other
    cv2.imshow('Add', add)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Add images using builtin function
    add_builtin = cv2.add(img1, img2)
    cv2.imshow('Add builtin', add_builtin) # Using this method we add each pixel value
    # For example (125, 240, 123) + (25, 205, 154) = (150, 445, 277) - will be converted into (150, 255, 255)
    # very bright image
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Add weighted images
    weighted = cv2.addWeighted(img1, 0.2, img2, 0.9, 0)
    cv2.imshow("Weighted add image", weighted)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Masking
    img3 = cv2.imread(filename3)
    # Get info from img3
    rows, cols, channels = img3.shape
    # Get some region of image
    roi = img1[0:rows,0:cols]
    img3gray = cv2.cvtColor(img3, cv2.COLOR_BGR2GRAY)
    ret, mask = cv2.threshold(img3gray, 220, 255, cv2.THRESH_BINARY_INV)
    cv2.imshow('mask', mask)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    # Work with mask - add logo to image 1
    mask_inv = cv2.bitwise_not(mask)
    img1_bg = cv2.bitwise_and(roi, roi,mask=mask_inv)
    img3_fg = cv2.bitwise_and(img3, img3, mask=mask)
    dst = cv2.add(img1_bg, img3_fg)
    img1[0:rows,0:cols] = dst
    cv2.imshow('result', img1)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
