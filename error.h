#ifndef ERROR_H
# define ERROR_H

# define ERR_FILE "ls: %s: No such file or directory "
# define VALID_OPT "[-atRrl]"

void	error(char *s);
void	usage_err(char c);

# endif