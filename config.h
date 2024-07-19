/* See LICENSE file for copyright and license details. */

// Constants
#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 1;       /* snap pixel */
static unsigned int gappih          = 7;       /* horiz inner gap */
static unsigned int gappiv          = 7;       /* vert inner gap */
static unsigned int gappoh          = 9;       /* horiz outer gap */
static unsigned int gappov          = 9;       /* vert outer gap */
static int smartgaps                = 0;       /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag  = True;
static const char *fonts[]    = {
    "Cascadia Mono:size=9",
    "Noto Color Emoji:pixelsize=11:antialias=true:autohint=true",
    "JoyPixels:pixelsize=9:antialias=true:autohint=true"
};
static const char dmenufont[] = "Operator Mono Lig Book:size=9";

#include "/home/razak/.cache/wal/colors-wal-dwm.h"

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "82x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "Cascadia Mono:size=14", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[]   = {TERMINAL, "-n", "obsidian-open", "-g", "84x38", "-e", "obsidian-open", NULL };
static Sp scratchpads[] = {
  /* name          cmd  */
  {"spterm",      spcmd1},
  {"spcalc",      spcmd2},
  {"spnotes",     spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1 // nrowgrid: force two clients to always split vertically
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol   arrange function */
    {"[]=",     tile},                   /* first entry is default */
    {"TTT",     bstack},                 /* Master on top, slaves on bottom */
    {"===",     bstackhoriz},
    {"HHH",     grid},                   /* Master on top, slaves on bottom */
    {"###",     nrowgrid},
    {"[@]",     spiral},                 /* Fibonacci spiral */
    {"[\\]",    dwindle},                /* Decreasing in size right and leftward */
    {"[D]",     deck},                   /* Master on left, slaves in monocle-like mode on right */
    {"[M]",     monocle},                /* All windows on top of eachother */
    {"|M|",     centeredmaster},         /* Master in middle, slaves on sides */
    {">M>",     centeredfloatingmaster}, /* Same as above but master floats */
    {"><>",     NULL},                   /* no layout function means floating behavior */
    {NULL,      NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define CMOD MODKEY | ControlMask
#define SMOD MODKEY | ShiftMask
#define AMOD MODKEY | ALTMOD

#define TAGKEYS(KEY,TAG)                                                        \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { ControlMask|ALTMOD,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { ALTMOD,                       KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ALTMOD,                KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define ESHCMD(cmd) SHCMD("exec " cmd)

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[]  = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]   = { "kitty", NULL };
static const char *browsers[]  = { "choose_browser", NULL };
static const char *filecmd[]   = { "thunar", NULL };
static const char *dmenucmd[]  = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *mailcmd[]   = { "thunderbird", NULL };
static const char *emojimenu[] = { "dmenuemoji", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_w,      spawn,          ESHCMD("fuj -profiles")},
    { MODKEY,                       XK_o,      spawn,          {.v = browsers} },
    { CMOD,                         XK_e,      spawn,          {.v = mailcmd} },
    { MODKEY,                       XK_e,      spawn,          {.v = filecmd} },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd} },
    { AMOD,                         XK_e,      spawn,          {.v = emojimenu} },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    // Power Menu TODO: figure out why renew is not working
    { CMOD,                         XK_l,                      spawn,    ESHCMD("sysact") },
    // Shiftview
    { MODKEY,                       XK_n,      shiftview,      {.i = 1} },
    { MODKEY,                       XK_p,      shiftview,      {.i = -1} },
    // Vanitygaps
    { CMOD,                         XK_t,     togglegaps,     {1} },
    { CMOD,                         XK_d,     defaultgaps,    {0} },
    { CMOD,                         XK_j,     incrgaps,       {.i = +1} },
    { CMOD,                         XK_k,     incrgaps,       {.i = -1} },
    // Actualfullscreen
    { MODKEY,                       XK_f,     togglefullscr,  {0} },
    // Cyclelayout
    { SMOD,                         XK_h,     cyclelayout,    {.i = -1} },
    { SMOD,                         XK_l,     cyclelayout,    {.i = +1} },
    // Move stack
    { MODKEY|ShiftMask,             XK_n,    movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,    movestack,      {.i = -1 } },
    // Scrapads
    { MODKEY,                       XK_apostrophe,  togglescratch,  {.ui = 0 } },
    { MODKEY,                       XK_m,           togglescratch,  {.ui = 1 } },
    { MODKEY,                       XK_semicolon,   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

