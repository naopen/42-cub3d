/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:31:33 by dhosokaw          #+#    #+#             */
/*   Updated: 2025/02/09 18:38:53 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>

void	ft_pf_putchar(char c);
void	ft_pf_putstr(char *str);
char	*ft_pf_strdup(const char *s1);
size_t	ft_pf_strlen(const char *s);
char	*ft_pf_itoa(int n);

int		ft_c_output(va_list *args);
int		ft_s_output(va_list *args);
int		ft_p_output(va_list *args);
int		ft_d_output(va_list *args);
int		ft_i_output(va_list *args);
int		ft_u_output(va_list *args);
int		ft_x_output(va_list *args);
int		ft_xx_output(va_list *args);
int		ft_percent_output(void);

int		ft_printf(const char *format, ...);

#endif
