import sys
from PIL import Image

if len(sys.argv) == 2:
	texturePath = sys.argv[1]
	textureFile = open(texturePath, "rb")
	textureFile.seek(4)
	width = int.from_bytes(textureFile.read(4), "big")
	height = int.from_bytes(textureFile.read(4), "big")
	for i in range(6):
		pixels = textureFile.read(width * height * 4)
		output = Image.new("RGBA", (width, height), (0, 0, 0, 0))
		output.frombytes(pixels, "raw")
		output.save(texturePath.replace(".tex", str(i) + ".png"))
	textureFile.close()