import cv2
import numpy as np
import matplotlib.pyplot as plt

# Read basic image
filename = "" # filename for image
img = cv2.imread(filename, cv2.IMREAD_GRAYSCALE)
# Basic show image
cv2.imshow('image', img)
# If any key is pressed - all windows will be closed
cv2.waitKey(0)
cv2.destroyAllWindows()

# Show image with matplotlib
plt.imshow(img, cmap="gray", interpolation='bicubic') # If cmap ="gray" is not specified - colors will be mixed
# We can plot something on images
plt.plot([25, 50, 64, 75], [51, 25, 75, 41], 'r', linewidth=3)
plt.show()
