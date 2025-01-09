import cv2


import torch
print(torch.cuda.device_count())
import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.bind(('localhost', 0))
    print(sock.getsockname())
    sock.close()



