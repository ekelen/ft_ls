/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 20:41:23 by ekelen            #+#    #+#             */
/*   Updated: 2017/04/10 20:41:25 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_FILE "ls: %s: No such file or directory "
# define VALID_OPT "[-atRrl]"

void	error(char *s);
void	usage_err(char c);

#endif
