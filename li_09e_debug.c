/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_09e_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:33:07 by jdouniol          #+#    #+#             */
/*   Updated: 2019/02/18 05:33:09 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_room_flow(t_all elem, int nb)
{
	int			i;

	i = 0;
	while (i++ < nb)
		elem.room = elem.room->next;
	ft_printf("%-9s|", elem.room->name_room);
}

void	print_all_name_flow(t_all elem)
{
	int			i;

	i = 0;
	ft_printf("%-10s", "");
	while (elem.room)
	{
		ft_printf("%-10s", elem.room->name_room);
		elem.room = elem.room->next;
	}
	ft_putchar('\n');
	ft_printf("%-10s", "");
	while (++i < elem.number_rooms)
		ft_printf("___________");
	ft_putchar('\n');
}

void	ft_print_matrice_flow(int **matrice, t_all *elem)
{
	int i;
	int j;

	i = 0;
	print_all_name_flow(*elem);
	while (i < elem->number_rooms)
	{
		j = 0;
		print_room_flow(*elem, i);
		while (j < elem->number_rooms)
		{
			ft_printf("%-10d", matrice[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}

void	print_room(t_all elem, int nb)
{
	int			i;

	i = 0;
	while (i++ < nb)
		elem.room = elem.room->next;
	ft_printf("%-9s|", elem.room->name_room);
}

void	print_all_name(t_all elem)
{
	int			i;

	i = 0;
	ft_printf("%-10s", "");
	while (elem.room)
	{
		ft_printf("%-10s", elem.room->name_room);
		elem.room = elem.room->next;
	}
	ft_putchar('\n');
	ft_printf("%-10s", "");
	while (++i < elem.number_rooms)
		ft_printf("___________");
	ft_putchar('\n');
}

void	ft_print_matrice(t_room ***matrice, t_all *elem)
{
	int i;
	int j;

	i = 0;
	print_all_name(*elem);
	while (i < elem->number_rooms)
	{
		j = 0;
		print_room(*elem, i);
		while (j < elem->number_rooms)
		{
			if (matrice[i][j])
				ft_printf("%-10s", matrice[i][j]->name_room);
			else
				ft_printf("%-10s", "~");
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}

void	ft_print_matrice_weight(t_room ***matrice, t_all *elem)
{
	int i;
	int j;

	i = 0;
	print_all_name(*elem);
	while (i < elem->number_rooms)
	{
		j = 0;
		print_room(*elem, i);
		while (j < elem->number_rooms)
		{
			if (matrice[i][j])
				ft_printf("%-10d", 1); // j ai mis 1 ici plutot que matrice[i][j]->weight qui n exsiste plus
			else
				ft_printf("%-10s", "~");
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n\n");
}

void	print_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s\n", path->room->name_room);
		path = path->next;
	}
	ft_printf("_______________________________\n");
}

void	print_tab_path(t_tab_path *tab)
{
	while (tab)
	{
		ft_printf("======SIZE = %d =======\n", path_size(tab->path));
		ft_printf("======NB_ANT = %d =======\n\n", tab->nb_ant);
		print_path(tab->path);
		tab = tab->next;
	}
}

/*if (ac == 2 && ft_read_2(&elem, av[1]) == FAIL)
{
	ft_free_all(&elem);
	ft_printf("Error\n");
	return (EXIT_FAILURE);
}*/

int		ft_read_2(t_all *elem, char *file)
{
	int		i;
	char	*line;
	int 	fd;

	ft_init_elem(elem);
	i = GNL_LINE_READ;
	line = NULL;
	fd = open(file, 'r');
	while (i == GNL_LINE_READ)
	{
		line = NULL;
		if ((i = get_next_line(fd, &line)) == GNL_ERROR)
			return (FAIL);
		if (i == GNL_END)
		{
			free(line);
			break ;
		}
		if (ft_get_instructions(elem, line) == ERROR)
		{
			free(line);
			return (ERROR);//( Si carte reseolvable ? ERROR : FAIL); //cas ou la carte esr resolvable malgre une ligne d'erreur
		}
		ft_save_map(elem, line);
		free(line);
	}
	return (SUCCESS);//(Si carte resolvable) ? SUCCESS : FAIL); //  if path found retourne success sinon fail
}