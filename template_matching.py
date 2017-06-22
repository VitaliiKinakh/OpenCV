import cv2
import numpy as np

if __name__ == "__main__":
    # Load main image
    img_bgr = cv2.imread("opencv-template-matching-python-tutorial.jpg")

    # Get gray image
    img_gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)

    # Load template
    template = cv2.imread("opencv-template-for-matching.jpg", 0)

    # Get width and height of template
    width, height = template.shape[::-1]

    # Get result of matching
    res = cv2.matchTemplate(img_gray, template, cv2.TM_CCOEFF_NORMED)
    threshold = 0.79

    # Find location where template match
    loc = np.where(res >= threshold)
    # Draw rectangle near every match
    for pt in zip(*loc[::-1]):
        cv2.rectangle(img_bgr, pt, (pt[0]+width, pt[1]+height), (0, 0, 255), 2)

    cv2.imshow("Matches",img_bgr)
    cv2.waitKey(0)
    cv2.destroyAllWindows()