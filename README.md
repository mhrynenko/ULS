<h1 align='center'> ULS </h1>

### Description
The ls command lists files and directories within the file system, and shows detailed information about them. This program works as a system utility ls. During developmnet was implemented:
- the usage: usage: uls [-l] [file ...]
- basic functionality of this command - list of directory contents without flags
- processing of file operands for files and directories
- the -l flag, which is one of the most useful flags
- the view of extended file attributes and access control lists (ACL)
- error handling, as in the original ls . Output uls as the program name instead of
ls where necessary
- the multicolumn output format when the option -l isn't specified
- some extra flags:
  - -a (-A) - display all files including the hidden files
  - -C - output in multiple columns sorted by columns
  - -x - output in multiple columns sorted by rows
  - -F - puts a / (slash) after each file name if the file is a directory, an * (asterisk) if the file can be executed, an = (equal sign) if the file is a socket, a | (pipe) sign if the file is a FIFO, and an @ for a symbolic link. 
  - -f - lists the name in each slot for each directory specified in the Directory parameter. This flag turns off the -l, -t, -s, and -r flags, and turns on the -a flag. The order of the listing is the order in which entries appear in the directory.
  - -G - colorful output
  - -i - display numbers of file descriptors in the first column
  - -l - displays the mode, number of links, owner, group, size (in bytes), and time of last modification for each file
  - -m - uses stream output format (a comma-separated series)
  - -o - displays the same information as the -l flag, except the -o flag suppresses display of the group and symbolic link information
  - -s - gives size in kilobytes for each entry
  - -p - puts a slash after each file name if that file is a directory
  - -1 - forces output into one-entry-per-line format
  - -r - reverses the order of the sort, giving reverse alphabetic or the oldest first, as appropriate
  - -t - sorts by time of last modification (latest first) instead of by name    
   

#### Some examples of working    
![ULS](https://user-images.githubusercontent.com/108219165/177314915-a62f2e53-fabe-4f16-b184-bf34c4b9eab2.png)


### How to start
*This program was developed on the MacOS, so it works correctly there.*   

In folder with cloned project use `make` to compile project. Start program with `./uls [-aACfFGilmosp1rtx] [file ...]`.

To delete the program - `make uninstall`   
To delete all 'obj' files - `make clean`   
To reinstall the program - `make reinstall`

