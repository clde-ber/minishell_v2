/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:59:48 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/03 14:31:28 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_free_2_strings_a_return(char *str_first, char *str_secd)
{
	ft_free_2_strings(str_first, str_secd);
	return (ft_strdup(""));
}
