/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"
#define TERMCLASS "alacritty"

/* appearance */
static const unsigned int borderpx = 1; // border pixel of windows
static const unsigned int snap = 32;    // snap pixel
static unsigned int gappih = 3;         // horiz inner gap
static unsigned int gappiv = 3;         // vert inner gap
static unsigned int gappoh = 5;         // horiz outer gap
static unsigned int gappov = 5;         // vert outer gap
static int smartgaps = 0;               // 1 - no outer gap when only one window
static const int showbar = 1;           // 0 means no bar
static const int topbar = 1;            // 0 means bottom bar
static const char *fonts[] = {"Noto Sans Mono:size=9"};
static const char dmenufont[] = "Noto Sans Mono:size=9";
static const char col_gray1[] = "#1e2127";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#030303";
static const char col_cyan[] = "#7ec0ee";
static const char *colors[][3] = {
    /* fg   bg  border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
// static const char *tags[] = {"", "", "", "", "", "", "", "", ""};
static const char *tags[] = {"", "", "", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 6, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;     /* number of clients in master area */
static const int resizehints = 1; // 1 - respect size hints in tiled resizals

// #include "vanitygaps.c"

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile},   /* first entry is default */
    {"TTT", bstack}, /* Master on top, slaves on bottom */
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},

    {"[@]", spiral},   /* Fibonacci spiral */
    {"[\\]", dwindle}, /* Decreasing in size right and leftward */

    {"[D]", deck},    /* Master on left, slaves in monocle-like mode on right */
    {"[M]", monocle}, /* All windows on top of eachother */

    {"|M|", centeredmaster},         /* Master in middle, slaves on sides */
    {">M>", centeredfloatingmaster}, /* Same but master floats */

    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

// #include "vanitygaps.c"

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ALTMOD, KEY, toggleview, {.ui = 1 << TAG}},                    \
      {ControlMask | ALTMOD, KEY, tag, {.ui = 1 << TAG}},                      \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }
#define ESHCMD(cmd) SHCMD("exec " cmd)

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *firefox[] = {"firefox", NULL};
static const char *filecmd[] = {"thunar", NULL};
static const char *ahkcmd[] = {"autokey-gtk", NULL};
static const char *kpcmd[] = {"keepassxc", NULL};
static const char *lxcmd[] = {"lxappearance", NULL};

#include "shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_w, spawn, {.v = firefox}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_e, spawn, {.v = filecmd}},
    {MODKEY | ShiftMask, XK_x, spawn, {.v = lxcmd}},
    {MODKEY | ShiftMask, XK_a, spawn, {.v = ahkcmd}},
    {MODKEY | ShiftMask, XK_k, spawn, {.v = kpcmd}},
    {ALTMOD, XK_Return, zoom, {0}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_n, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY | ControlMask, XK_h, incnmaster, {.i = +1}},
    {MODKEY | ControlMask, XK_v, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY, XK_x, killclient, {0}},
    {MODKEY | ShiftMask, XK_q, quit, {0}},
    // {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},

    // Gaps
    {MODKEY | ControlMask, XK_a, togglegaps, {1}},
    {MODKEY | ShiftMask, XK_equal, defaultgaps, {0}},
    {MODKEY, XK_equal, incrgaps, {.i = +1}},
    {MODKEY | ControlMask, XK_d, incrgaps, {.i = -1}},

    // Layouts
    {MODKEY, XK_e, setlayout, {.v = &layouts[0]}},             /* tile */
    {MODKEY | ShiftMask, XK_e, setlayout, {.v = &layouts[1]}}, /* bstack */
    {MODKEY, XK_y, setlayout, {.v = &layouts[2]}},             /* spiral */
    {MODKEY | ShiftMask, XK_y, setlayout, {.v = &layouts[3]}}, /* dwindle */
    {MODKEY, XK_n, setlayout, {.v = &layouts[4]}},             /* deck */
    {MODKEY | ShiftMask, XK_n, setlayout, {.v = &layouts[5]}}, /* monocle */
    {MODKEY, XK_i, setlayout, {.v = &layouts[6]}}, /* centeredmaster */
    {MODKEY | ShiftMask,
     XK_i,
     setlayout,
     {.v = &layouts[7]}}, // centeredfloatingmaster
    {MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[8]}}, // floating
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY | ShiftMask, XK_h, cyclelayout, {.i = -1}},
    {MODKEY | ShiftMask, XK_l, cyclelayout, {.i = +1}},

    // shiftview
    {ALTMOD | ControlMask, XK_l, shiftview, {.i = 1}},
    {ALTMOD | ControlMask, XK_h, shiftview, {.i = -1}},
    {ALTMOD | ControlMask, XK_k, shiftview, {.i = 1}},
    {ALTMOD | ControlMask, XK_n, shiftview, {.i = -1}},
    {ALTMOD | ControlMask, XK_Delete, spawn, SHCMD("sysact")},

    {MODKEY | ControlMask, XK_m, spawn,
     SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
    // {MODKEY, XK_minus, spawn,SHCMD("pamixer --allow-boost -d 5; kill -44
    // $(pidof dwmblocks)")}, {MODKEY | ShiftMask, XK_minus,
    // spawn,SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)")},
    // {MODKEY, XK_equal, spawn,SHCMD("pamixer --allow-boost -i 5; kill -44
    // $(pidof dwmblocks)")}, {MODKEY | ShiftMask, XK_Left, spawn,SHCMD("pamixer
    // --allow-boost -i 15; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioMute, spawn,
     SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_Sleep, spawn, ESHCMD("lock-sleep")},
    {0, XF86XK_PowerOff, spawn, SHCMD("sysact")},
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set 250+")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 250-")},
    {0, XF86XK_TouchpadOff, spawn, SHCMD("synclient TouchpadOff=1")},
    {0, XF86XK_TouchpadOn, spawn, SHCMD("synclient TouchpadOff=0")},
    TAGKEYS(XK_o, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_i, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
/* click   event mask      button  function argument */
#ifndef __OpenBSD__
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigdwmblocks, {.i = 1}},
    {ClkStatusText, 0, Button2, sigdwmblocks, {.i = 2}},
    {ClkStatusText, 0, Button3, sigdwmblocks, {.i = 3}},
    {ClkStatusText, 0, Button4, sigdwmblocks, {.i = 4}},
    {ClkStatusText, 0, Button5, sigdwmblocks, {.i = 5}},
    {ClkStatusText, ShiftMask, Button1, sigdwmblocks, {.i = 6}},
#endif
    {ClkStatusText, ShiftMask, Button3, spawn,
     SHCMD(TERMINAL " -e nvim ~/suckless/dwmblocks/config.h")},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, defaultgaps, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, incrgaps, {.i = +1}},
    {ClkClientWin, MODKEY, Button5, incrgaps, {.i = -1}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkTagBar, 0, Button4, shiftview, {.i = -1}},
    {ClkTagBar, 0, Button5, shiftview, {.i = 1}},
    {ClkRootWin, 0, Button2, togglebar, {0}},
};
