/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjilee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:11:26 by eunjilee          #+#    #+#             */
/*   Updated: 2022/12/19 18:11:27 by eunjilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

void	tmp_err1(t_list **tmp_list, int *err)
{
	tmp_clear(tmp_list);
	*err = SYS;
}

void	tmp_err2(char *tmp_file, t_list **tmp_list, int *err)
{
	free(tmp_file);
	tmp_clear(tmp_list);
	*err = SYS;
}
