/*  output.h - Common routines for raster/vector */
/*
    libzint - the open source barcode library
    Copyright (C) 2020-2023 Robin Stuart <rstuart114@gmail.com>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the project nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
 */
/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h> /* For FILE */

/* Check colour options are good (`symbol->fgcolour`, `symbol->bgcolour`) */
INTERNAL int out_check_colour_options(struct zint_symbol *symbol);

/* Return RGB(A) from (well-formed) colour string. Returns 0 if RGB or converted CMYK, 1 if RGBA */
INTERNAL int out_colour_get_rgb(const char *colour, unsigned char *red, unsigned char *green, unsigned char *blue,
                unsigned char *alpha);
/* Return CMYK from (well-formed) colour string. Returns 0 if CMYK, 1 if converted RBG, 2 if converted RGBA */
INTERNAL int out_colour_get_cmyk(const char *colour, int *cyan, int *magenta, int *yellow, int *black,
                unsigned char *rgb_alpha);

/* Set left (x), top (y), right and bottom offsets for whitespace */
INTERNAL void out_set_whitespace_offsets(const struct zint_symbol *symbol, const int hide_text,
                float *xoffset, float *yoffset, float *roffset, float *boffset, const float scaler,
                int *xoffset_si, int *yoffset_si, int *roffset_si, int *boffset_si);

/* Set composite offset and main width excluding addon (for start of addon calc) and addon text, returning
   UPC/EAN type */
INTERNAL int out_process_upcean(const struct zint_symbol *symbol, int *p_main_width, int *p_comp_xoffset,
                unsigned char addon[6], int *p_addon_gap);

/* Calculate large bar height i.e. linear bars with zero row height that respond to the symbol height.
   If scaler `si` non-zero (raster), then large_bar_height if non-zero or else row heights will be rounded
   to nearest pixel and symbol height adjusted */
INTERNAL float out_large_bar_height(struct zint_symbol *symbol, const int si, int *row_heights_si,
                int *symbol_height_si);

/* Split UPC/EAN add-on text into various constituents */
INTERNAL void out_upcean_split_text(const int upceanflag, const unsigned char text[], unsigned char textparts[4][7]);

/* Create output file, creating sub-directories if necessary. Returns `fopen()` FILE pointer */
INTERNAL FILE *out_fopen(const char filename[256], const char *mode);

#ifdef _WIN32
/* Do `fopen()` on Windows, assuming `filename` is UTF-8 encoded. Props Marcel, ticket #288 */
INTERNAL FILE *out_win_fopen(const char *filename, const char *mode);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* vim: set ts=4 sw=4 et : */
#endif /* Z_OUTPUT_H */
