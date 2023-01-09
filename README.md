# 21sh
Almost like a real shell. Tested on macos.

Supports pipes "|".\
Supports the 4 following redirections “<”, “>”, “<<” and “>>”.\
Supports file descriptor aggregation ">&", "<&", "2>& /dev/null"\
Supports closing of fd "<&-", ">&-", "2>&-"\
Supports semicolon to seperate list of commands ";"\
Supports line editing, moving with OPTION+left/right, go beginning of line with HOME, go end of line with END.\
Supports OPTION + UP/DOWN for moving up or down a row.\
The ctrl+D et ctrl+C keys combination features for line edition and process execution.\
Supports quotes(') and double quotes(")\
Supports history with up and down keys.\
Supports CTRL + U, for copying. CTRL + W, for cutting. CTRL + Y, for pasting.

## INSTALLATION
clone git\
make\
./21\
HAVE FUN.
