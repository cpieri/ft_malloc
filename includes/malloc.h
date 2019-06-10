/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:28:16 by cpieri            #+#    #+#             */
/*   Updated: 2019/06/10 11:31:07 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

void	free(void *ptr);
void	show_alloc_mem(void);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif
