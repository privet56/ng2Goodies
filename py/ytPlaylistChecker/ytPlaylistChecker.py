#!/usr/bin/env python3

import urllib.request
import urllib.error
import re
import sys
import time
import os
import argparse
import time
import json
from collections import OrderedDict

# from pytube import YouTube # pip install pytube + set PATH to pytube.exe

def exitWithError(msg):
    print(msg)
    system.exit(1)

def getFC(fn):
    with open(fn) as f:
        return f.read()

def isValidVid(vid): # title: "[Private video]" & "[Deleted video]" have no uploader, data incomplete!
    return False if vid["uploader"] is None else True

def existsIn(vid, playlist):
    for idx, vidOfPlaylist in enumerate(playlist):
        if vid["id"] == vidOfPlaylist["id"] and isValidVid(vidOfPlaylist):
            return True
    return False

def getNotExistingEntries(playlist, oldPlaylist):
    notExistingEntries = []
    for idx, vid in enumerate(oldPlaylist):
        if not existsIn(vid, playlist):
            notExistingEntries.append(vid)
    return notExistingEntries

def getVidUrl(url):
    if url.startswith('http'):
        return url
    return "https://www.youtube.com/watch?v=" + url

def get(value, defaultValue):
    return value if value else defaultValue

def getVid(id, playlist):
    for idx, vid in enumerate(playlist):
        if vid['id'] == id:
            return vid

    exitWithError("vnf '" + id + "'")

def generateHtml(playlistFC, oldPlaylistFC, playlistName):
    html = "<html><head></head><body><table style='width:100%;'>\n"
    
    playlist = json.loads(playlistFC)["entries"]
    oldPlaylist = []
    invalidVids = 0
    if (oldPlaylistFC != ""):
        oldPlaylist = json.loads(oldPlaylistFC)["entries"]
        notExistingEntries = getNotExistingEntries(playlist, oldPlaylist)
        for idx, vid in enumerate(notExistingEntries):
            if isValidVid(vid):
                invalidVids = invalidVids + 1
                oldVid = getVid(vid['id'], oldPlaylist)
                print("deleted(" + str(invalidVids) + "): " + getVidUrl(oldVid["url"]) + " = "+ get(oldVid["title"], '-') + " (author: " + get(oldVid["uploader"], '-') + ")")
                html += ("<tr>\n"
                            "<td title=deleted>X</td>\n"
                            "<td><img loading=lazy src=http://img.youtube.com/vi/" + oldVid["id"] + "/1.jpg></td>\n"
                            "<td><a href=" + getVidUrl(oldVid["url"]) + ">" + get(oldVid["title"],'-') + "</a></td>\n"
                            "<td>(DELETED): " + get(oldVid["uploader"],'-') + "</td>\n"
                        "</tr>\n")

    validVids = 0
    for idx, vid in enumerate(playlist):

        if isValidVid(vid):

            validVids = validVids + 1

            html += ("<tr>\n"
                        "<td>" + str(validVids) + "</td>\n"
                        "<td><img loading=lazy src=http://img.youtube.com/vi/" + vid["id"] + "/1.jpg></td>\n"
                        "<td><a href=" + getVidUrl(vid["url"]) + ">" + vid["title"] + "</a></td>\n"
                        "<td>" + vid["uploader"] + "</td>\n"
                    "</tr>\n")

    html += (   "</table>"
                "<link rel=stylesheet href=css.css>"
                "<script src=https://code.jquery.com/jquery-3.3.1.slim.min.js></script>"
                "<script src=https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js></script>"
                "<script src=https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js></script>"
                "<script src=js.js></script>"
                "</body></html>")

    with open(playlistName + '.playlist.html', 'w', encoding="utf-8") as f:
        f.write(html)

    return len(playlist) if len(playlist) > len(oldPlaylist) else len(oldPlaylist)

def downloadPlaylistAndGetFC(playlist):
    fn = time.strftime(playlist + ".playlist-%Y.%m.%d.json")
    if os.path.isfile(fn):
        return getFC(fn), False
    # args: see https://github.com/ytdl-org/youtube-dl
    # exe actually is yt-dlp.exe
    e = os.system('youtube-dl.exe --ignore-errors --dump-single-json --list-thumbnails --get-thumbnail --flat-playlist https://www.youtube.com/playlist?list=' + playlist + ' > ' + fn)
    if os.path.isfile(fn):
        fc = getFC(fn)
        fc = fc[fc.find('{'):] # yt-dlp.exe writes some info (ID Width Height URL) before the actual JSON -> remove everything before {
        with open(fn, 'w', encoding="utf-8") as f: # write fixed fc back to fn
            f.write(fc)
        return fc, True
    else:
        exitWithError("fnf '" + fn + "' ... " + e)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--playlist' , type=str, default='',  help='playlist', required=True)

    playlist = parser.parse_args().playlist
    playlistFC, newlyDownloaded = downloadPlaylistAndGetFC(playlist)
    latestPlaylist = playlist + '.playlist-latest.json' # older playlist to compare with current and find missing entries
    latestPlaylistFC = "" if not os.path.isfile(latestPlaylist) else getFC(latestPlaylist)

    elementsCount = generateHtml(playlistFC, latestPlaylistFC, playlist)

    if newlyDownloaded:
        playlistFCFormatted = json.dumps(json.loads(playlistFC), indent=2, sort_keys=True) # nice formatted + sorted -> diff can easily find changes!
        with open(latestPlaylist, 'w', encoding="utf-8") as f:
            f.write(playlistFCFormatted)

    print("Finished checking " + str(elementsCount) + " elements.")
