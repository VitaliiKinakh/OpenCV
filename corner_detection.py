import cv2
import numpy as np

if __name__ == "__main__":
    # Load image
    filename = ""
    img = cv2.imread(filename)
    # Create gray image
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Convert
    img_gray = np.float32(img_gray)
    # Get corners
    corners = cv2.goodFeaturesToTrack(img_gray, 60, 0.01, 10)
    # Convert
    corners = np.int0(corners)
    # Draw corners as a circles
    for corner in corners:
        x, y = corner.ravel()
        cv2.circle(img, (x,y), 3, (0, 255, 0), -1) # Filled circle
    cv2.imshow("Corners", img)
    # Exit point
    cv2.waitKey(0)
    cv2.destroyAllWindows()

