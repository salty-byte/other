#coding:utf-8
from PIL import Image

#画像の読み込み
im = Image.open("./image.png")

#RGBに変換
rgb_im = im.convert('RGB')

#画像サイズを取得
size = rgb_im.size

#取得したサイズと同じ空のイメージを新規に作成
im2 = Image.new('RGBA',size)

#loop
for x in range(size[0]):
    for y in range(size[1]):
        #ピクセルを取得
        r,g,b = rgb_im.getpixel((x,y))

        if b == 255:
	        im2.putpixel((x,y),(0,0,255))
        else:
            im2.putpixel((x,y),(255,255,255))

#show
im2.save('solve.png')
