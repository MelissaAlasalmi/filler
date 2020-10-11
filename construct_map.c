#include "filler.h"

int ft_abs(int n)
{
    if (n < 0)
		n = n * -1;
    return (n);
}

int fill_heatmap(t_filler *data, int row, int column)
{
    int y;
    int x;
    int distance;
    int min;

    y = 0;
    min = 0;
    while (y < data->map_y)
    {   
        x = 0;
        while (x < data->map_x)
        {
            if (data->heatmap[y][x] == -2)
            {
                distance = ft_abs(x - column);
                distance += ft_abs(y - row);
                if (distance < min || min == 0)
                    min = distance;
            }
            x++;
        }
        y++;
    }
    return(min);
}

void construct_heatmap(t_filler *data)
{
    int y;
    int x;

    y = 0;
    while (y < data->map_y)
    {    
        x = 0;
        while (x < data->map_x)
        {
            if (data->heatmap[y][x] == 0)
                data->heatmap[y][x] = fill_heatmap(data, y, x);
            x++;
        }
        y++;
    }
    ft_putstr_fd("here", 2);
}

int construct_map(t_filler *data)
{
    int y;
    int x;

    y = 0;
    if (!(data->heatmap = (int**)malloc(sizeof(int*) * data->map_y)))
		return (1);
    while (y < data->map_y)
    {
        if(!(data->heatmap[y] = (int*)malloc(sizeof(int) * data->map_x)))
            return(1);
        y++;
    }
    y = 0;
    while (y < data->map_y)
    {
        x = 0;
        while (x < data->map_x)
        {
            if (data->map[y][x] == '.')
                data->heatmap[y][x] = 0;
            if (data->map[y][x] == 'o' || data->map[y][x] == 'O')
            {
                if(data->playernum == 1)
                    data->heatmap[y][x] = -1;
                else
                    data->heatmap[y][x] = -2;
            }
            if (data->map[y][x] == 'x' || data->map[y][x] == 'X')
            {
                if(data->playernum == 2)
                    data->heatmap[y][x] = -1;
                else
                    data->heatmap[y][x] = -2;
            }
            x++;
        }
        y++;
    }
    construct_heatmap(data);
    testheatmap(data);
    return (0);
}