import cv2
import superlibrary

# Read demo image
im = cv2.imread('demo_image.png')

# Use C++ coolFunction()
blur = superlibrary.cool_function(im)

# Use C++ CoolClass::toGray()
cc = superlibrary.CoolClass()
gray = cc.to_gray(im)

# Write output images
cv2.imwrite('blur.png', blur)
cv2.imwrite('gray.png', gray)
