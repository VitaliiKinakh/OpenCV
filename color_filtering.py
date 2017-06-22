import cv2
import numpy as np

if __name__ == "__main__":
    cap = cv2.VideoCapture(0)

    while True:
        _, frame = cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        upper_yellow = np.array([10,100,120])
        lower_yellow = np.array([0,20,20])

        # Creates mask where all pixel values are in range
        mask = cv2.inRange(frame, lower_yellow, upper_yellow)

        # Mask image
        res = cv2.bitwise_and(frame, frame, mask=mask)

        # Smoothing
        kernel = np.ones((15, 15), np.float32) / 225
        smoothed = cv2.filter2D(res, -1, kernel)

        # Blurring
        blur = cv2.GaussianBlur(res, (15,15), 0)

        # Median blur
        median = cv2.medianBlur(res, 15)

        # Bilateral filter
        bilateral = cv2.bilateralFilter(res, 15, 75, 75)

        # Morphological operations
        kernel1 = np.ones((5, 5), np.uint8)

        # Erosion - is where we will "erode" the edges.
        erosion = cv2.erode(mask, kernel, iterations=1)

        # The other version of this is Dilation, which basically does the opposite:
        # Slides around, if the entire area isn't black, then it is converted to white
        dilition = cv2.dilate(mask, kernel, iterations=1)

        # Opening - removes all the noise in the background
        opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel=kernel1)

        # Closing - removes all the noise in the object
        closing = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel=kernel1)

        #cv2.imshow("Smopthed", smoothed)
        #cv2.imshow("Blur", blur)
        #cv2.imshow("Median blur", median)
        #cv2.imshow("Bilateral filter", bilateral)
        #cv2.imshow("Erosion", erosion)
        #cv2.imshow("Dilition", dilition)
        cv2.imshow("Opening", opening)
        cv2.imshow("Closing", closing)
        cv2.imshow("Frame", frame)
        cv2.imshow("Masked", res)

        # Create exit point
        k = cv2.waitKey(30) & 0xFF
        if k == 27:
            break

    cv2.destroyAllWindows()
    cap.release()
