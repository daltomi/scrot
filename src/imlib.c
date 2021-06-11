/* imlib.c

Copyright 1999-2000 Tom Gilbert
Copyright 2020      daltomi <daltomi@disroot.org>
Copyright 2020      ideal <idealities@gmail.com>
Copyright 2020      Sean Brennan <zettix1@gmail.com>
Copyright 2020      spycapitan <spycapitan@protonmail.com>
Copyright 2021      Christopher Nelson <christopher.nelson@languidnights.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies of the Software and its documentation and acknowledgment shall be
given in the documentation and software packages that this Software was
used.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "scrot.h"
#include "options.h"

Display *disp = NULL;
Visual *vis = NULL;
Screen *scr = NULL;
Colormap cm;
int depth;
Window root = 0;


void
init_x_and_imlib(char *dispstr, int screen_num)
{
   disp = XOpenDisplay(dispstr);
   if (!disp) {
      fprintf(stderr, "Can't open X display. It *is* running, yeah? [");
      fprintf(stderr, "%s", dispstr ? dispstr :
              (getenv("DISPLAY") ? getenv("DISPLAY") : "NULL"));
      fprintf(stderr, "]\n");
      exit(EXIT_FAILURE);
   }

   if (screen_num)
      scr = ScreenOfDisplay(disp, screen_num);
   else
      scr = ScreenOfDisplay(disp, DefaultScreen(disp));

   vis = DefaultVisual(disp, XScreenNumberOfScreen(scr));
   depth = DefaultDepth(disp, XScreenNumberOfScreen(scr));
   cm = DefaultColormap(disp, XScreenNumberOfScreen(scr));
   root = RootWindow(disp, XScreenNumberOfScreen(scr));

   imlib_context_set_drawable(root);
   imlib_context_set_display(disp);
   imlib_context_set_visual(vis);
   imlib_context_set_colormap(cm);
   imlib_context_set_color_modifier(NULL);
   imlib_context_set_operation(IMLIB_OP_COPY);
}
