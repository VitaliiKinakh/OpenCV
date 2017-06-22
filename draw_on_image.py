import cv2
import numpy as np

if __name__ == "__main__":
    filename = "" # Load image
    img = cv2.imread(filename, cv2.IMREAD_COLOR) # Load color image

    # Create line
    cv2.line(img, (60,60), (105, 105), (255, 0, 255), 12)

    # Create rectangle
    cv2.rectangle(img, (45, 45), (175, 175), (0, 255, 0), 4)

    # Create circle
    cv2.circle(img, (105, 105), 55, (0, 0, 255),-1)

    # Create points for polygon
    pts = np.array([[10,5], [45, 84], [120, 145], [15, 125]], np.int32)
    cv2.polylines(img, [pts], True, (0, 255, 255), 3) # True means connect first and last points

    # Create text
    font = cv2.FONT_HERSHEY_SIMPLEX
    cv2.putText(img, "OpenCV", (0, 120), font, 1, (0, 0, 0), 2, cv2.LINE_AA)

    cv2.imshow("Image with drawing", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()