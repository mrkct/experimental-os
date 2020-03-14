#ifndef UTIL_H
#define UTIL_H

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MOVE_PTR(p, t, x) p = (t *) (((char *) p) + x);

#endif