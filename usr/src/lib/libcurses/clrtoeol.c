/*
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "@(#)clrtoeol.c	5.6 (Berkeley) %G%";
#endif	/* not lint */

#include <curses.h>

/*
 * wclrtoeol --
 *	Clear up to the end of line.
 */
int
wclrtoeol(win)
	register WINDOW *win;
{
	register int minx, x, y;
	register char *end, *maxx, *sp;

	y = win->cury;
	x = win->curx;
	end = &win->lines[y]->line[win->maxx];
	minx = -1;
	maxx = &win->lines[y]->line[x];
	for (sp = maxx; sp < end; sp++)
		if (*sp != ' ') {
			maxx = sp;
			if (minx == -1)
				minx = sp - win->lines[y]->line;
			*sp = ' ';
		}
#ifdef DEBUG
	__TRACE("CLRTOEOL: minx = %d, maxx = %d, firstch = %d, lastch = %d\n",
	    minx, maxx - win->lines[y]->line, win->lines[y]->firstch, 
	    win->lines[y]->lastch);
#endif
	/* Update firstch and lastch for the line. */
	return (touchline(win, y, win->curx, win->maxx - 1));
}
