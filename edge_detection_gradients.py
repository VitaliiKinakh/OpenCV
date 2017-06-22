import cv2
import numpy as np

if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    while True:
        _, frame = cap.read()
        # Laplacian gradient
        laplacian = cv2.Laplacian(frame, cv2.CV_64F)

        # Sobel x and y gradients
        sobelx = cv2.Sobel(frame, cv2.CV_64F, 1, 0, ksize=5)
        sobely = cv2.Sobel(frame, cv2.CV_64F, 0, 1, ksize=5)

        # Canny edge detection
        edges = cv2.Canny(frame,50, 50)

        cv2.imshow('Original', frame)
        cv2.imshow("Canny edge detection", edges)
        #cv2.imshow('Sobelx', sobelx)
        #cv2.imshow('Sobely', sobely)
        #cv2.imshow("Laplacian", laplacian)
        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break

    cv2.destroyAllWindows()
    cap.release()