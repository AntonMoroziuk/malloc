/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:33:19 by amoroziu          #+#    #+#             */
/*   Updated: 2020/01/05 17:33:36 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "malloc.h"

void	*split_block(t_block_header *block, size_t size);
void	*new_block(t_block_header *block, size_t size, void *max_addr);
int		malloc_init(void);
int		is_big(void *ptr);

#endif
