# mmenu - minimal menu

Small ncurses menu for c programs and shell scripts, similar to suckless' dmenu. 

## For shell scripts
It reads the contents of /tmp/mmenu and changes them to the chosen option. It takes the second argument as the prompt, and if the third one is set to "t" or "true", it will write the index of the line instead of the line itself.
An example might look like: 
```bash
ls -1 > /tmp/mmenu && mmenu "select file: " && </tmp/mmenu xargs less -R 
```

## For C programs
The main (mmenu) function takes 3 inputs, the options, (similar to argv), the length of the options (similar to argc),
and the prompt to be asked (a string). The return value is the index of the element chosen, or -1 in the case of none.
The -lncurses flag is required at compilation. An example may look like:

```c
#include "mmenu.h"

int main() {
	char* options[5] = {"Zero", "One", "Two", "Three", "Four"};
	int chosen = mmenu(options, 5, "Please choose an option: ");
	if(chosen == -1) exit(1);
	printf("You chose: %s", options[chosen]);
}
```
