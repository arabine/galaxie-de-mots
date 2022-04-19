#/bin/bash

#	    MDPI (Baseline)	HDPI	XHDPI	XXHDPI	XXXHDPI
# Scale	1 x	1.5 x	2 x	3 x	4 x
# DPI	   ~ 160 dpi	~ 240 dpi	~ 320 dpi	~ 480 dpi	~ 640 dpi
# App Launcher Icons	48 px	72 px	96 px	144 px	192 px

mkdir -p mipmap-mdpi
mkdir -p mipmap-hdpi
mkdir -p mipmap-xhdpi
mkdir -p mipmap-xxhdpi
mkdir -p mipmap-xxxhdpi

inkscape --export-type=png --export-width=48 --export-height=48 -o mipmap-mdpi/ic_launcher.png logo.svg
inkscape --export-type=png --export-width=72 --export-height=72 -o mipmap-hdpi/ic_launcher.png logo.svg
inkscape --export-type=png --export-width=96 --export-height=96 -o mipmap-xhdpi/ic_launcher.png logo.svg
inkscape --export-type=png --export-width=144 --export-height=144 -o mipmap-xxhdpi/ic_launcher.png logo.svg
inkscape --export-type=png --export-width=192 --export-height=192 -o mipmap-xxxhdpi/ic_launcher.png logo.svg
