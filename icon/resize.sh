#!/bin/bash -x

svgname="$1"
[[ -z "$2" ]] && section="apps" || section="$2"
[[ -z "$3" ]] && maxres="128" || maxres="$3"

pngname="`basename ${svgname} .svg`.png"

for resol in 16 22 32 48 64 128
do
       if [[ "$resol" -le "$maxres" ]]
       then
               icondir="debian/usr/share/icons/hicolor/${resol}x${resol}/${section}"
               mkdir -p "$icondir"
               rsvg-convert -h "$resol" -w "$resol"  "${svgname}" -o "${icondir}/${pngname}"
       fi
done
icondir="debian/usr/share/icons/hicolor/scalable/${section}"
mkdir -p "$icondir"
gzip -9 "${svgname}" -c > "${icondir}/${svgname}z"
