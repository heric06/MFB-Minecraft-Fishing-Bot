# MFB-Minecraft-Fishing-Bot

Info
----
This program is an automated command-line tool for afk-fishing in Minecraft, working on Unix based operating systems.

You will need:
--------------
  xdotool
  afk-fishing setup [see: <https://www.youtube.com/watch?v=TJ6CCFoGbig>]

How to
------
Debian based:

  `sudo apt-get install xdotool`

MacOSX:

  install brew [see: <https://brew.sh/>]
  
  `brew install xdotool` 

Usage:
------
mfb [OPTIONS] [TIME]

Options:

 -s <time>      --sec  <time>   Adds time seconds
  
 -m <time>      --min  <time>   Adds time minutes
  
 -h <time>      --hour <time>   Adds time hours
  
 -i             --nolim         No limit fishing
 
 -v             --version       Displays version
 
