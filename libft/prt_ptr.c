/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:17 by cassassa          #+#    #+#             */
/*   Updated: 2024/03/22 15:28:17 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rev_print(char *hexa)
{
	int	len;
	int	rtrn;

	len = ft_strlen(hexa) - 1;
	rtrn = 0;
	while (len >= 0)
		rtrn += write(STDOUT_FILENO, &hexa[len--], 1);
	return (--rtrn);
}

static int	hexa_convptr(unsigned long addr)
{
	int		i;
	int		temp;
	char	hexa[42];

	i = 0;
	while (addr != 0)
	{
		temp = addr % 16;
		if (temp < 10)
			hexa[i++] = temp + 48;
		else
			hexa[i++] = temp + 87;
		addr = addr / 16;
	}
	hexa[i] = '\0';
	return (rev_print(hexa) + 1);
}

int	prt_ptr(void *ptr_addr)
{
	if (ptr_addr == 0)
		return (write(STDOUT_FILENO, "(nil)", 5));
	write(STDOUT_FILENO, "0x", 2);
	return (hexa_convptr((unsigned long int)ptr_addr) + 2);
}
