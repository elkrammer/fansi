# fANSI

fANSI allows you to display legacy / retro ANSI art in your terminal.

![screenshot](https://user-images.githubusercontent.com/64374/124131577-f274a600-da4d-11eb-9f68-d8ca0f2d7154.png)j

## Features

* Display legacy ANSI (.ANS) art images in your terminal
* Read SAUCE information
* Screen Saver mode to display all files in a directory
* Print [Code Page 437](https://en.wikipedia.org/wiki/Code_page_437) table as UTF-8 characters

## Requirements

* Linux
* UTF-8 capable terminal with 256 color support
* Terminal font that provides glyphs for the CP437 characters (e.g., Hack, Consolas, Iosevka, etc)

## Building

```
$ git clone git@github.com:elkrammer/fansi.git
$ cd fansi
$ make
```

## Usage

```
./fansi [options] filename

Options:
    --speed value         Set rendering speed. Default speed is 110 - increase it to slow down the output
-s  --ssaver dirname      Screen Saver mode
    --sauce filename      Print SAUCE metadata for file
    --cp437               Print Code Page 437 as UTF-8 characters
-h  --help                Print help text and exit
```

You may use the `--cp437` option to check if your terminal font supports all CP437 glyphs.

## TODO / Ideas

* add support for .BIN files
* add support for Xbin (.XB) files
* rewrite using ncurses
