import cv2
import numpy as np

if __name__ == "__main__":
    # Get video from webcam
    cap = cv2.VideoCapture(0)
    # Define cascades
    face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
    eye_casacade = cv2.CascadeClassifier("haarcascade_eye.xml")

    # Infinite loop for processing image
    while True:
        ret, img = cap.read()
        # Convert image to gray
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # Find faces
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)

        # Draw faces on the image
        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x+w, x+h), (255, 255, 255), 2)
            # Find eyes on the face
            roi_gray = gray[y:y+h, x:x+w]
            roi_color = img[y:y+h, x:x+w]
            eyes = eye_casacade.detectMultiScale(roi_gray)
            for (ex, ey, ew, eh) in eyes:
                # Draw rectangles near eyes
                cv2.rectangle(roi_color, (ex, ey), (ex+ew, ey+eh), (0,0,255), 1)

        # Show images
        cv2.imshow("Detect face and eyes", img)

        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break

    cap.release()
    cv2.destroyAllWindows()
