import cv2
from freetype import Face
import numpy as np


class DrawText(object):
    def __init__(self):
        self.face = Face(r'C:\Windows\Fonts\simsun.ttc')
        self.size = 6
        self.face.set_char_size(24 * (1 << self.size))

    def __call__(self, img, text, org, color):
        slot = self.face.glyph
        width, height, baseline = 0, 0, 0
        previous = 0
        for i, c in enumerate(text):
            self.face.load_char(c)
            bitmap = slot.bitmap
            height = max(height, bitmap.rows + max(0, -(slot.bitmap_top - bitmap.rows)))
            baseline = max(baseline, max(0, -(slot.bitmap_top - bitmap.rows)))
            kerning = self.face.get_kerning(previous, c)
            width += (slot.advance.x >> self.size) + (kerning.x >> self.size)
            previous = c

        Z = np.zeros((height, width), dtype=np.uint8)
        x, y = 0, 0
        previous = 0
        for c in text:
            self.face.load_char(c)
            bitmap = slot.bitmap
            top = slot.bitmap_top
            left = slot.bitmap_left
            w, h = bitmap.width, bitmap.rows
            y = height - baseline - top
            kerning = self.face.get_kerning(previous, c)
            x += (kerning.x >> self.size)
            mask = np.array(bitmap.buffer, dtype=np.uint8)
            Z[y:y + h, x + left:x + left + w] = mask.reshape(h, w)

            x += (slot.advance.x >> self.size)
            previous = c
        cv2.imshow("Z", Z)
        cv2.waitKey()
        mask = Z != 0
        x_, y_ = org
        img[y_:y_ + height, x_:x_ + width][mask] = (0, 255, 0)

if __name__ == '__main__':
    draw = DrawText()
    img = cv2.imread(r"00000302.jpg")
    draw(img, "已采集", (100, 100), (0, 255, 0))
    cv2.imshow("show", img)
    cv2.waitKey()

