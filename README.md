# mmenu - minimal menu

Small ncurses menu for c programs, similar to suckless' dmenu. The main (mmenu) function takes 3 inputs, the options, (similar to
argv), the length of the options (similar to argc), and the prompt to be asked (a string). The return value is the index of
the element chosen, or -1 in the case of none. The -lncurses flag is required at compilation.
