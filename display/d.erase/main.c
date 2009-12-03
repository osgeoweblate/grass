/*
 ****************************************************************************
 *
 * MODULE:       d.erase
 * AUTHOR(S):    James Westervelt - USA CERL
 * PURPOSE:      Erase the current display frame with user defined color.
 * COPYRIGHT:    (C) 2000 by the GRASS Development Team
 *
 *               This program is free software under the GNU General Public
 *               License (>=v2). Read the file COPYING that comes with GRASS
 *               for details.
 *
 *****************************************************************************/

#include <stdlib.h>
#include <grass/gis.h>
#include <grass/display.h>
#include <grass/glocale.h>

int main(int argc, char *argv[])
{
    struct Option *color;
    struct Flag *eraseframe;
    struct GModule *module;

    G_gisinit(argv[0]);

    module = G_define_module();
    G_add_keyword(_("display"));
    module->description =
	_("Erase the contents of the active display frame with user defined color");

    color = G_define_option();
    color->key = "color";
    color->type = TYPE_STRING;
    color->required = NO;
    color->answer = DEFAULT_BG_COLOR;
    color->description =
	_("Color to erase with, either a standard GRASS color or R:G:B triplet (separated by colons)");
    color->gisprompt = "old_color,color,color";

    eraseframe = G_define_flag();
    eraseframe->key = 'f';
    eraseframe->description = _("Remove all frames and erase the screen");

    if (G_parser(argc, argv))
	exit(1);

    if (D_open_driver() != 0)
	G_fatal_error(_("No graphics device selected"));

    D_setup_unity(0);

    D_erase(color->answer);

    if (eraseframe->answer)
	D__erase();

    D_close_driver();

    exit(0);
}
