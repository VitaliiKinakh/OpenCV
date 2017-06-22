import cv2
import numpy as np

# This algorithm reduces foreground and background.
# But really it  divides video into two parts: moving and stable part

if __name__ == "__main__":
    cap = cv2.VideoCapture(0) # Or your video 
    fgbg = cv2.createBackgroundSubtractorMOG2()

    # Infinite loop for video
    while True:
        ref, frame = cap.read()
        # Get moving part as a mask
        fgmask = fgbg.apply(frame)

        # Show frame and mask
        cv2.imshow("origenal", frame)
        #cv2.imshow("moving part", fgmask)

        # Make mask more correct
        kernel = np.ones((5, 5), np.uint8)
        closing = cv2.morphologyEx(fgmask, cv2.MORPH_CLOSE, kernel)

        # Show masked iamge
        res = cv2.bitwise_and(frame, frame, mask=fgmask)
        cv2.imshow("Masked image", res)

        # Show opening effect
        cl_res = cv2.bitwise_and(frame, frame, mask=closing)
        cv2.imshow("Closing image", cl_res)

        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break

    cap.release()
    cv2.destroyAllWindows()
