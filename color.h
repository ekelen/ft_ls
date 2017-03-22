#ifndef FT_COLOR_H
# define FT_COLOR_H

# define FG_BLK		"\x1b[30m"
# define FG_RED		"\x1b[31m"
# define FG_GRN		"\x1b[32m"
# define FG_YEL		"\x1b[33m"
# define FG_BLU		"\x1b[34m"
# define FG_PNK		"\x1b[35m"
# define FG_CYN		"\x1b[36m"
# define FG_RESET	"\x1b[0m"

# define BG_BLK		"\x1b[40m"
# define BG_RED		"\x1b[41m"
# define BG_GRN		"\x1b[42m"
# define BG_YEL		"\x1b[43m"
# define BG_BLU		"\x1b[44m"
# define BG_PNK		"\x1b[45m"
# define BG_CYN		"\x1b[46m"
# define BG_RESET	"\x1b[49m"

# define FBG_RESET	"\x1b[49m\x1b[20m"

typedef struct			s_color
{
	char	fg[7];
	char	bg[7];
}						t_color;

#endif


// The color designators are as follows:

//                            a     black
//                            b     red
//                            c     green
//                            d     brown
//                            e     blue
//                            f     magenta
//                            g     cyan
//                            h     light grey
//                            A     bold black, usually shows up as dark grey
//                            B     bold red
//                            C     bold green
//                            D     bold brown, usually shows up as yellow
//                            E     bold blue
//                            F     bold magenta
//                            G     bold cyan
//                            H     bold light grey; looks like bright white
//                            x     default foreground or background

//                      Note that the above are standard ANSI colors.  The actual display may differ depending on the color capabilities of the terminal
//                      in use.

//                      The order of the attributes are as follows:

//                            1.   directory
//                            2.   symbolic link
//                            3.   socket
//                            4.   pipe
//                            5.   executable
//                            6.   block special
//                            7.   character special
//                            8.   executable with setuid bit set
//                            9.   executable with setgid bit set
//                            10.  directory writable to others, with sticky bit
//                            11.  directory writable to others, without sticky bit

//                      The default is "exfxcxdxbxegedabagacad", i.e. blue foreground and default background for regular directories, black foreground
//                      and red background for setuid executables, etc.