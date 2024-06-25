/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassa <cassassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:42:10 by cassassa          #+#    #+#             */
/*   Updated: 2024/05/27 14:42:10 by cassassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*str;

	str = pointer;
	while (count--)
	{
		*str = (unsigned char) value;
		str++;
	}
	return (pointer);
}

// #include <stdio.h>
// #include "libft.h"
// #include <string.h>

// int main() {

//     int array [] = { 54, 85, 20, 63, 21 };
//     size_t size = sizeof( int ) * 5;
//     int length;

//     /* Display the initial values */
//     for( length=0; length<5; length++) {
//         printf( "%d ", array[ length ] );
//     }
//     printf( "\n" );

//     /* Reset the memory bloc */
//     ft_memset( array, 'q', size );

//     /* Display the new values */
//     for( length=0; length<5; length++) {
//         printf( "%d ", array[ length ] );
//     }
//     printf( "\n" );

//     return 0;
// }