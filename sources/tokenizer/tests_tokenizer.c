/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:54:31 by jakken            #+#    #+#             */
/*   Updated: 2022/11/30 20:26:33 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int count_delimits(char *str, char **delimits);

void test_count_delimits(void)
{
	char	**delimits;
	char	*input;

	delimits = ft_memalloc(sizeof(*delimits) * 11);
	delimits[0] = " ";
	input = "n";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "nice dog";
	if (count_delimits(input, delimits) != 1)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "a b";
	if (count_delimits(input, delimits) != 1)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "nice dog and cat";
	if (count_delimits(input, delimits) != 3)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "n d a c";
	if (count_delimits(input, delimits) != 3)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);

	delimits[0] = ">";
	input = "n";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = ">";
	if (count_delimits(input, delimits) != 1)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "hello > pallo";
	if (count_delimits(input, delimits) != 1)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "hello < pallo";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);

	delimits[0] = ">&";
	input = ">&";
	if (count_delimits(input, delimits) != 1)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = ">&>&";
	if (count_delimits(input, delimits) != 2)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = ">";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "&>";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = ">";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "&";
	if (count_delimits(input, delimits) != 0)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "hello>&pallo";
	if (count_delimits(input, delimits) != 1)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "hello>&pallo>&";
	if (count_delimits(input, delimits) != 2)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "o>&o>&";
	if (count_delimits(input, delimits) != 2)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);
	input = "helloo&o>&pallo>&";
	if (count_delimits(input, delimits) != 2)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);

	delimits[1] = ">";
	input = "helloo&o>&pallo>&";
	if (count_delimits(input, delimits) != 2)
		ft_printf("ERROR: %s\n", input);
	else
		ft_printf("%s: OK\n", input);

}

int main(void)
{
	test_count_delimits();
	return (0);
}