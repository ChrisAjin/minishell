/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbennou <inbennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:16:04 by inbennou          #+#    #+#             */
/*   Updated: 2024/05/26 16:26:47 by inbennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitest.h"

// prends la struct en param pour tout free
// exit prends 1 arg = exit_code
void	exit_shell(int write_ex)
{
	if (write_ex)
		if (write(1, "exit\n", 5) < 0)
			perror("write error");
	// tout free
	// rl_clear_history
	exit(1); // exit avec le bon exit_code
}
