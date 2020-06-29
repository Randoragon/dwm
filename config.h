/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int startontag         = 1;        /* 0 means no tag active on start */
static const char *fonts[]          = { "dejavu sans:size=10:antialias=true" };
static const char dmenufont[]       = "dejavu sans:size=10:antialias=true";
static const char col_gray1[]       = "#050505";
static const char col_gray2[]       = "#222222";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#dfdfdf";
static const char col_active1[]      = "#ffb52a";
static const char col_active2[]      = "#ff274d";
static const char *colors[][4]      = {
	/*               fg         bg           border        float */
	[SchemeNorm] = { col_gray3, col_gray1,   col_gray2,   col_gray2},
	[SchemeSel]  = { col_gray4, col_active1, col_active1, col_active2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,          -1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "grid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress,   MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_active2, "-sf", col_gray4, NULL };

#include "movestack.c"
static Key keys[] = {
   /* type          modifier                      key               function        argument */
	{ KeyPress,     MODKEY,                       XK_o,             spawn,          {.v = dmenucmd } },
	{ KeyPress,     MODKEY,                       XK_b,             togglebar,      {0} },
	{ KeyPress,     MODKEY,                       XK_j,             focusstack,     {.i = +1 } },
	{ KeyPress,     MODKEY,                       XK_k,             focusstack,     {.i = -1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_j,             movestack,      {.i = +1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_k,             movestack,      {.i = -1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_j,             rotatestack,    {.i = +1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_k,             rotatestack,    {.i = -1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_equal,         incnmaster,     {.i = +1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_minus,         incnmaster,     {.i = -1 } },
	{ KeyPress,     MODKEY|ControlMask,           XK_h,             setmfact,       {.f = -0.05} },
	{ KeyPress,     MODKEY|ControlMask,           XK_l,             setmfact,       {.f = +0.05} },
	{ KeyPress,     MODKEY,                       XK_s,             zoom,           {0} },
	{ KeyPress,     MODKEY,                       XK_Tab,           view,           {0} },
	{ KeyPress,     MODKEY,                       XK_t,             setlayout,      {.v = &layouts[0]} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_t,             setlayout,      {.v = &layouts[3]} },
	{ KeyPress,     MODKEY,                       XK_f,             setlayout,      {.v = &layouts[1]} },
	{ KeyPress,     MODKEY,                       XK_m,             setlayout,      {.v = &layouts[2]} },
	{ KeyPress,     MODKEY,                       XK_u,             setlayout,      {.v = &layouts[5]} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_u,             setlayout,      {.v = &layouts[6]} },
    { KeyPress,     MODKEY,                       XK_y,             setlayout,      {.v = &layouts[8]} },
    { KeyPress,     MODKEY|ShiftMask,             XK_y,             setlayout,      {.v = &layouts[9]} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_space,         togglefloating, {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_f,             togglefullscr,  {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_s,             togglesticky,   {0} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_j,             moveresize,     {.v = "0x 25y 0w 0h" } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_k,             moveresize,     {.v = "0x -25y 0w 0h" } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_l,             moveresize,     {.v = "25x 0y 0w 0h" } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_h,             moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ KeyPress,     MODKEY|ControlMask,           XK_j,             moveresize,     {.v = "0x 0y 0w 25h" } },
	{ KeyPress,     MODKEY|ControlMask,           XK_k,             moveresize,     {.v = "0x 0y 0w -25h" } },
	{ KeyPress,     MODKEY|ControlMask,           XK_l,             moveresize,     {.v = "0x 0y 25w 0h" } },
	{ KeyPress,     MODKEY|ControlMask,           XK_h,             moveresize,     {.v = "0x 0y -25w 0h" } },
	{ KeyPress,     MODKEY,                       XK_0,             view,           {.ui = ~0 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_0,             tag,            {.ui = ~0 } },
	{ KeyPress,     MODKEY,                       XK_comma,         focusmon,       {.i = -1 } },
	{ KeyPress,     MODKEY,                       XK_period,        focusmon,       {.i = +1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_comma,         tagmon,         {.i = -1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_period,        tagmon,         {.i = +1 } },
	TAGKEYS(                                      XK_1,                             0)
	TAGKEYS(                                      XK_2,                             1)
	TAGKEYS(                                      XK_3,                             2)
	TAGKEYS(                                      XK_4,                             3)
	TAGKEYS(                                      XK_5,                             4)
	TAGKEYS(                                      XK_6,                             5)
	TAGKEYS(                                      XK_7,                             6)
	TAGKEYS(                                      XK_8,                             7)
	TAGKEYS(                                      XK_9,                             8)
    { KeyPress,     MODKEY,                       XK_h,             viewtoleft,     {0} },
    { KeyPress,     MODKEY,                       XK_l,             viewtoright,    {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_h,             tagtoleft,      {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_l,             tagtoright,     {0} },
	{ KeyPress,     MODKEY,                       XK_q,             killclient,     {0} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_q,             quit,           {0} },
    { KeyPress,     MODKEY,                       XK_bracketright,  incrgaps,       {.i = +4 } },
    { KeyPress,     MODKEY,                       XK_bracketleft,   incrgaps,       {.i = -4 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_bracketright,  incrogaps,      {.i = +4 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_bracketleft,   incrogaps,      {.i = -4 } },
    { KeyPress,     MODKEY|ControlMask,           XK_bracketright,  incrigaps,      {.i = +4 } },
    { KeyPress,     MODKEY|ControlMask,           XK_bracketleft,   incrigaps,      {.i = -4 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_0,             togglegaps,     {0} },
    { KeyPress,     MODKEY|ControlMask,           XK_0,             defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

