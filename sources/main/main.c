/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/18 17:37:05 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void uninit_keyboard(t_term *t)
{
	ft_memdel((void **)&t->nl_addr);
}

int	main(void)
{
	t_term	t;
	
	ft_keyboard(&t);
	ft_printf(t.inp);
	uninit_keyboard(&t);
	// input array here
	// initialise keyboard
	// get the input and perhaps copy it to a new string?
	// lexer
	// parser
	// tree generation?

}
