import cv2
import numpy as np
import cv2

vid = cv2.VideoCapture(0)

detect = cv2.QRCodeDetector()


def read_qr_code(img):
    """Read an image and read the QR code.

    Args:
        filename (string): Path to file

    Returns:
        qr (string): Value from QR code
    """

    try:
        value, points, straight_qrcode = detect.detectAndDecode(img)
        img = cv2.polylines(img, points.astype(int), True, (0, 255, 0), 3)

        return value, img
    except:
        return "", img


while True:
    # Capture the video frame
    # by frame
    ret, frame = vid.read()

    # Display the resulting frame

    if detect.detect(frame):
        value, change_frame = read_qr_code(frame.copy())
        split_value = value.split(";")

        create_dic = {}
        try:
            for values in split_value:
                splitted_list = values.split(":")
                length = len(splitted_list)
                if length >= 2:
                    create_dic[splitted_list[length - 2]] = splitted_list[length - 1]
            if len(create_dic) > 0:
                frame = change_frame
                print(create_dic)

        except Exception as e:
            print(e)
    # the 'q' button is set as the
    # quitting button you may use any
    # desired button of your choice
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()
