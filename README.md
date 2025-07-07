# List-Table-Files ~ts 
A CLI tool that displays directory contents of the current working directory into a neat little table. I honestly felt like Tony Stark building the mini arc reactor in the cave in Iron Man 1 while programming this project. Making my own tools, albeit for simple tasks, got me feeling like that one gif of Tony Stark hammering on the anvil.

![iron-man-iron-hammer](res/iron-man-iron-man-hammer.gif)

## Features
- Table displays the Filename, Filesize, Type (File or Directory), and the Date last Modified (Month/Day/Year Time).
- The table's "FileName" columns' length is dynamic with the length of the longest filename in the directory.
- FileSize column displays file size in Bytes (B), Kilobytes (KB)Megabytes (MB), and Gigabytes (GB).
- Uses unicode escape codes to draw the table.

## Demo

![tablefiles_demo](res/tablefiles_demo.png)

## Usage
```
$ tablefiles.exe
```

## Build from Source
```
$ make
```
