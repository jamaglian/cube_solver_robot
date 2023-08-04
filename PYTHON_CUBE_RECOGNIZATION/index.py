import cv2
import numpy as np
from skimage import color

#pip install opencv-python
#pip install numpy
#pip install scikit-image


#VERDE R:93 G:212 B:83
#LARANJA R:200 G:235 B:50
#AZUL R:25 G:145 B:190
#VERMELHO R:180 G:50 B:17
#BRANCO R:195 G:215 B:180
#AMARELO R:215 G:235 B:50

class MagicCube:
    def __init__(self, frame):
        self.frame = frame

    def process_frame(self):
        # convert the frame to grayscale
        grayFrame = cv2.cvtColor(self.frame, cv2.COLOR_BGR2GRAY)

        # blur the frame to remove noise
        blurredFrame = cv2.blur(grayFrame, (3, 3))

        # apply Canny Edge Detection to find edges in the image
        cannyFrame = cv2.Canny(blurredFrame, 30, 60, 3)

        # define a kernel for dilation
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (9, 9))

        # dilate the canny edges
        dilatedFrame = cv2.dilate(cannyFrame, kernel)

        return dilatedFrame

    def get_dominant_color(self, image):
                # Convert the image from BGR to RGB
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

        # Calculate the average color of each RGB channel
        average_color_per_row = np.average(image, axis=0)
        average_color = np.average(average_color_per_row, axis=0)
        
        # Return the average color
        return average_color
    
    def rgb2lab(self, inputColor):
        inputColor = inputColor/255.0
        numPyColor = np.array(inputColor).reshape(1,-1,3) 
        return color.rgb2lab(numPyColor)[0][0]

    def color_distance(self, color1, color2):
        color1_lab = self.rgb2lab(color1)
        color2_lab = self.rgb2lab(color2)
        return np.sqrt(np.sum((color1_lab - color2_lab)**2))
    
    def find_contours(self):
        # process the frame to prepare for contour detection
        processedFrame = self.process_frame()
        vermelho = np.array([180, 50, 17])#VERMELHO R:180 G:50 B:17
        verde = np.array([93, 212, 83])#VERDE R:93 G:212 B:83
        azul = np.array([25, 145, 190])#AZUL R:25 G:145 B:190
        laranja = np.array([200, 235, 50])#LARANJA R:200 G:235 B:50
        branco = np.array([195, 215, 180])#BRANCO R:195 G:215 B:180
        amarelo = np.array([215, 235, 50])#AMARELO R:215 G:235 B:50
        threshold = 30.0  # set your color distance threshold here
        # find contours in the image
        contours, _ = cv2.findContours(processedFrame, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        for contour in contours:
            perimeter = cv2.arcLength(contour, True)
            approx = cv2.approxPolyDP(contour, 0.1 * perimeter, True)
            if len (approx) == 4:
                area = cv2.contourArea(contour)
                (x, y, w, h) = cv2.boundingRect(approx)

                # Find aspect ratio of boundary rectangle around the contours.
                ratio = w / float(h)
                # Get the dominant color in the contour region
                region = self.frame[y:y+h, x:x+w]
                dominant_color = self.get_dominant_color(region)
                # Check if contour is close to a square.
                if ratio >= 0.8 and ratio <= 1.2 and w >= 30 and w <= 60 and area / (w * h) > 0.6:
                    if self.color_distance(dominant_color, azul) < threshold:
                        cv2.rectangle(self.frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
                        # Label the contour with the dominant color
                        label = 'R:{}, G:{}, B:{}'.format(int(dominant_color[0]), int(dominant_color[1]), int(dominant_color[2]))
                        #print(label)
                        cv2.putText(self.frame, label, (x, y+h+15), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1, cv2.LINE_AA)

        return self.frame

# open the webcam
cap = cv2.VideoCapture(0)

while True:
    # read a frame from the webcam
    ret, frame = cap.read()
    
    if ret:
        cube = MagicCube(frame)
        output_frame = cube.find_contours()
        
        # show the output frame
        cv2.imshow("Contours", output_frame)
    
    # if 'q' is pressed, break from the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
