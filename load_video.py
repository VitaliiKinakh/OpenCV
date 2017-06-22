import cv2
import numpy as np
if __name__ == "__main__":
    # Get video
    cap = cv2.VideoCapture(0) # 0 - means get video from first webcam
    fourcc = cv2.VideoWriter_fourcc(*"XVID") # Object for loading video
    out = cv2.VideoWriter("output.avi", fourcc, 20.0, (640, 480))
    # Infinite loop for getting video
    while True:
        ret, frame = cap.read()
        # Create gray color image
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        out.write(frame) # Write into video
        cv2.imshow('frame', frame) # Show each frame which webcam read
        cv2.imshow('gray', gray) # Show gray image
        if cv2.waitKey(1) & 0xFF == ord('q'): # Create exit point
            break

    cap.release()
    out.release() # Save video
    cv2.destroyAllWindows()