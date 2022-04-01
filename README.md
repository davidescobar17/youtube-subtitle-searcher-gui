# Youtube Subtitle Searcher GUI

YouTube Subtitle Searcher GUI is GUI version of previous project [Youtube Subtitle Searcher](https://github.com/davidescobar17/youtube-subtitle-searcher). This is an application to search subtitles from YouTube videos for a specified term and generate link to the times in which the term appears in the video. Subtitle files are required to be in VTT format with the title:

    <video name>-<youtube video id>

Subtitles with this format can be downloaded using [youtube-dl](https://github.com/ytdl-org/youtube-dl). This application can execute the required command to download the subtitles. This command is: 

    youtube-dl --skip-download --write-sub --write-auto-sub --sub-format vtt --output %(title)s-%(id)s.%(ext)s <link to video>

## How to Use

  1. Download the zip in the release and extract.
  2. Download [youtube-dl](https://github.com/ytdl-org/youtube-dl) and place it in the directory with youtube-subtitle-searcher.exe.
  3. Run youtube-subtitle-searcher.exe.

## Getting Started

This shows how to get a local copy of the project running for development.

### Built With

  - [QT Creator](https://www.qt.io/download)

### Prerequisites

- [youtube-dl](https://github.com/ytdl-org/youtube-dl)

### Installing

Download [youtube-dl](https://github.com/ytdl-org/youtube-dl) and place it in the directory with youtube-subtitle-searcher.exe.