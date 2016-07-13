#!/usr/bin/python

from converter import Converter
c = Converter()

info = c.probe('data/output.mov')

conv = c.convert('data/output.mov', 'data/output.mp4', {
    'format': 'mkv',
    'audio': {
        'codec': 'mp3',
        'samplerate': 11025,
        'channels': 2
    },
    'video': {
        'codec': 'h264',
        'width': 1280,
        'height': 640,
        'fps': 15
    }})

for timecode in conv:
    print "Converting (%f) ...\r" % timecode