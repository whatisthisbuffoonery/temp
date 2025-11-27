#include "header_mand.h"

static char *grab(t_queue *q, va_list va)
{
    char    cmp;

    if (q->type == str)
        return (q->str);
    else if (q->type == op)
    {
        cmp = q->str[0];
        if (cmp == 'c')
            return (char_op(va_arg(va, char)));
        else if (cmp == 's' || cmp == 'p')
            return (ptr_op(va_arg(va, char *), cmp));
        else if (cmp == 'd' || cmp == 'i')
            return (int_op(va_arg(va, int)));
        else if (cmp == 'u' || cmp == 'x' || cmp == 'X')
            return (uint_op(va_arg(va, unsigned int), cmp));
        write(1, &cmp, 1);
        write(1, "  <--  who put this here\n", 25);
    }
    else
        write(1, "nil type in queue???\n", 22);
    return (NULL);
}

static char *print_strjoin(char *dst, char *src, t_queue *f)
{
    char    *ret;
    int    i;
    int    k;

    if (!dst || !src)
        return (NULL);
    ret = malloc((ft_strlen(dst) + ft_strlen(src) + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    i = -1;
    k = -1;
    while (dst[++i])
        ret[i] = dst[i];
    while (src[++k])
        ret[i + k] = src[k];
    ret[i + k] = '\0';
    free(dst);
    if (f->type == op)
        free(src);
    return (ret);
}

static void    *tantrum_boogaloo(char *ret, char *new, char *tmp, t_queue *f)
{
    if (ret)
        free(ret);
    if (new && f->type == op)
        free(new);
    if (tmp)
        free(tmp);
    return (NULL);
}

char    *process(t_queue *q, va_list va)
{
    t_queue *f;
    char    *ret;
    char    *tmp;
    char    *new;

    f = q->next;
    ret = grab(q, va);
    if (!ret)
        return (tantrum_boogaloo(0, ret, 0, q));
    while (f)
    {
        new = grab(f, va);
        tmp = print_strjoin(ret, new, f);
        if (!tmp || !new)
            return (tantrum_boogaloo(ret, new, tmp, f));
        f = f->next;
        ret = tmp;
    }
    return (ret);
}