https://viewsourcecode.org/snaptoken/kilo/index.html

{
    tcsetattr(nt fd, int action, const struct termios *settings)
    
use to set terminal attribute/configratuiton or setting 

tell the terminal: use these rules now.”

Input:

fd → which terminal (again STDIN_FILENO)-> keybord input.

action → when to apply the new rules:

TCSANOW → immediately

TCSADRAIN → after all output has been written

TCSAFLUSH → after flushing input buffer (common for raw mode)

settings → the struct containing the new rules you want.}





{
    tcgetattr

“Get terminal attributes.”

Function:

int tcgetattr(int fd, struct termios *settings);


Meaning: “Ask the terminal: what are your current rules?”

Input:

fd → the file descriptor (usually STDIN_FILENO = 0 for keyboard input).

settings → a pointer to a struct termios where the terminal will copy its current configuration.

Output:

On success, settings now contains all the current terminal rules (echo, canonical mode, signal handling, etc.).

Return value: 0 if success, -1 if error.
}

****
tcgetattr → like reading the current configuration of your keyboard/terminal.

tcsetattr → like writing a new configuration.

struct termios → the “settings file” that holds all the switches/properties such as 

flags like ECHO, ICANON, etc. → the individual switches you can flip on/off
****


<hr>
Turning on raw mode with tcsetattr is just the first step. It gives you direct access to every keypress, so your program behaves like a text editor instead of waiting for the terminal to process things for you.

Once you can read keystrokes immediately, you can define your own rules for:

typing characters,

moving the cursor with arrows,

saving to a file,

copying/cutting/pasting, etc.




<hr> ***perror()***

Most C library functions that fail will set the global errno{such as 1 for sucess , 0 for error, 1 for operation not permited etc } 


variable to indicate what the error was. perror() looks at the global errno variable and prints a descriptive error message for it. It also prints the string given to it before it prints the error message, which is meant to provide context about what part of your code caused the error.



Ctr key setup 

since CTRL key ranges from 1-26 for all 26 letter 
using bit wise manupluatio / hexadecimal they convert numer like 67 87 etc into range of 1-26 to use with CTRl 

'C' (67) → 67 & 0x1f → 3 → Ctrl-C

'Q' (81) → 81 & 0x1f → 17 → Ctrl-Q