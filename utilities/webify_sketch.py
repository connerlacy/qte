#!/usr/bin/python

import os
import shutil
import datetime

sketch = "001"
screenCapSrcDir = "/Users/connerlacy/Desktop/untitled folder"
rootDir = "/Users/connerlacy/Documents/emergent.io/website/emergent.io/sketches/" + sketch


### ----------------------------------- IMAGES
imagesDir = rootDir + "/images"
thumbsDir = rootDir + "/thumbs"

# Create rootDir
if not os.path.exists(rootDir):
	os.makedirs(rootDir)
else:
	print("Cannot create. " + rootDir + " Destination directory already exists.")
	
# Create rootDir/images
if not os.path.exists(imagesDir):
	os.makedirs(imagesDir)
else:
	print("Cannot create. " + imagesDir + " Destination directory already exists.")
		
# Create rootDir/thumbs
if not os.path.exists(thumbsDir):
	os.makedirs(thumbsDir)
else:
	print("Cannot create. " + thumbsDir + " Destination directory already exists.")	


### Rename, format, and copy screencaps into rootDir/images and rootDir/thumbs
i = 0;
for file in os.listdir(screenCapSrcDir):
	
	srcFile = os.path.join(screenCapSrcDir, file)
	srcExt = os.path.splitext(srcFile)
	
	if srcExt[1] == ".png":
		dstFileThumb = os.path.join(thumbsDir, "emergentio_sketch_" + sketch + "_thumb_" + str(i).zfill(3) + ".png")
		dstFileImage = os.path.join(imagesDir, "emergentio_sketch_" + sketch + "_image_" + str(i).zfill(3) + ".png")

		shutil.copyfile(srcFile, dstFileThumb)
		shutil.copyfile(srcFile, dstFileImage)
	
		i += 1
		
### ----------------------------------- HTML
EIO_HTML_MACRO_SKETCH_NAME = "sketch_" + sketch
EIO_HTML_MACRO_SKETCH_DATE = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
EIO_HTML_MACRO_SKETCH_VIMEO_URL = "https://player.vimeo.com/146741790"
EIO_HTML_MACRO_SKETCH_SOURCE_TEXT = "github.com/emergent-io/eio_qte/releases/tag/v0.0.3"
EIO_HTML_MACRO_SKETCH_SOURCE_URL = "https://github.com/emergent-io/eio_qte/releases/tag/v0.0.3"
EIO_HTML_MACRO_SKETCH_DESCRIPTION = "Pond-hopped pebbles make / ripples return to their source / again and again."

indexTemplateFilePath = "/Users/connerlacy/Documents/emergent.io/website/templates/sketches/index_template.html"
indexFilePath = os.path.join(rootDir, "index.html")

templateFile = open(indexTemplateFilePath, 'r')
indexFile = open(indexFilePath, 'w')

for line in templateFile:
	if "EIO_HTML_MACRO_SKETCH_THUMB_SECTION" in line:
		for thumb in range(0, i): #File count from above
			line = '		<div class="col-xs-4"> <a href="./images/emergentio_' + EIO_HTML_MACRO_SKETCH_NAME + '_image_' + str(thumb).zfill(3) + '.png"> <img class="sketch-thumb" src="thumbs/emergentio_' + EIO_HTML_MACRO_SKETCH_NAME + '_thumb_' + str(thumb).zfill(3) + '.png"> </a> </div>\n'
			indexFile.write(line)
	else:
		line = line.replace("EIO_HTML_MACRO_SKETCH_NAME", EIO_HTML_MACRO_SKETCH_NAME)
		line = line.replace("EIO_HTML_MACRO_SKETCH_DATE", EIO_HTML_MACRO_SKETCH_DATE)
		line = line.replace("EIO_HTML_MACRO_SKETCH_VIMEO_URL", EIO_HTML_MACRO_SKETCH_VIMEO_URL)
		line = line.replace("EIO_HTML_MACRO_SKETCH_SOURCE_TEXT", EIO_HTML_MACRO_SKETCH_SOURCE_TEXT)
		line = line.replace("EIO_HTML_MACRO_SKETCH_SOURCE_URL", EIO_HTML_MACRO_SKETCH_SOURCE_URL)
		line = line.replace("EIO_HTML_MACRO_SKETCH_DESCRIPTION", EIO_HTML_MACRO_SKETCH_DESCRIPTION)
		indexFile.write(line)
		
	print(line)
templateFile.close()
indexFile.close()

# Make a bunch of screen caps of sketch
# Move the keepers into the img folder inside of sketch folder
# Run above script to copy files into 'thumbs' directory