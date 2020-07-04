/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const unsigned int gappi     = 20;       /* inner gap between windows */
static const unsigned int gappo     = 30;       /* outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;       /* 0 means that dwm will calculate bar */
static const int startontag         = 1 << 3;   /* 0 means no tag active on start */
static const char *fonts[]          = {
    "font awesome 5 free solid:fontformat=truetype:size=10:antialias=true;3",
    "font awesome 5 brands regular:fontformat=truetype:size=10:antialias=true;3",
    "dejavu sans:size=9:antialias=true",
};
static int lrpad                    = 6;       /* pixel sum of left and right padding for bar text. ~0 for auto */
static const char col_gray1[]       = "#050505";
static const char col_gray2[]       = "#222222";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#dfdfdf";
static const char col_yellow1[]     = "#ffb52a";
static const char col_yellow2[]     = "#ffd05a";
static const char col_red[]         = "#bd2c40";
static const unsigned int baralpha = 200;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*                   fg            bg            border     */
	[SchemeNorm]     = { "#000000",    "#000000",    col_gray2   }, // Only border is important
	[SchemeSel]      = { "#000000",    col_yellow1,  col_yellow1 }, // Only border is important, but bg holds color for tag underline rectangle
	[SchemeStatus]   = { col_gray3,    col_gray1,    "#000000"   }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4,    col_gray2,    "#000000"   }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { col_gray4,    col_gray1,    "#000000"   }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeTagsUrg]  = { col_gray4,    col_red,      "#000000"   }, // Tagbar left urgent {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_yellow2,  col_gray1,    "#000000"   }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { col_yellow2,  col_gray1,    "#000000"   }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
	/*                   fg      bg        border     */
	[SchemeNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]   = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsUrg]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoNorm] = { OPAQUE, baralpha, borderalpha },
};

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-g", "155x50", "-n", "s_term", NULL };
const char *spcmd2[] = {"st", "-g", "155x50", "-n", "s_music", "-e", "ncmpcpp", NULL };
const char *spcmd3[] = {"st", "-g", "155x50", "-n", "s_news", "-e", "dualboat", NULL };
static Sp scratchpads[] = {
	/* name           cmd  */
	{"s_term",        spcmd1},
	{"s_music",       spcmd2},
	{"s_news",        spcmd3},
};

/* signals */
static Signal signals[] = {
	/* signum               function        argument*/
	{ 15,                   quit,           {0} },
	{ 10,                   updatestatus,   {0} },
};

/* tagging */
static const char *tags[] = { "", "", "", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance       title           tags mask  isfloating  canfocus  isterminal  noswallow  monitor  float x,y,w,h,border        */
	{ "Gimp",        NULL,          NULL,           0,         1,          1,        0,           0,        -1,        -1, -1, -1, -1, -1        },
	{ "St",          NULL,          NULL,           0,         0,          1,        1,          -1,        -1,        -1, -1, -1, -1, -1        },
	{ NULL,          NULL,          "Event Tester", 0,         1,          1,        0,           1,        -1,        -1, -1, -1, -1, -1        }, /* xev */
	{ NULL,		     "s_term",		NULL,		    SPTAG(0),  1,		   1,        1,           1,        -1,        -1, -1, -1, -1, -1        },
	{ NULL,		     "s_music",		NULL,		    SPTAG(1),  1,		   1,        1,           1,        -1,        -1, -1, -1, -1, -1        },
	{ NULL,		     "s_news",		NULL,		    SPTAG(2),  1,		   1,        1,           1,        -1,        -1, -1, -1, -1, -1        },
    { "floatme",     NULL,          NULL,           0,         1,          1,        0,           0,        -1,        -1, -1, -1, -1, -1        },
	{ "firefox",     NULL,          NULL,           1 << 0,    0,          1,        0,           0,        -1,        -1, -1, -1, -1, -1        },
	{ "Thunderbird", NULL,          NULL,           1 << 1,    0,          1,        0,           0,        -1,        -1, -1, -1, -1, -1        },
	{ "discord",     NULL,          NULL,           1 << 2,    0,          1,        0,           0,        -1,        -1, -1, -1, -1, -1        },
	{ "GLava",       NULL,          NULL,           0,         1,          0,        0,           1,        -1,         0,  0, -1, -1,  0        },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *quitcmd[] = { "quitmenu", NULL };

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
	{ KeyPress,     MODKEY|ShiftMask,             XK_i,             setlayout,      {.v = &layouts[1]} },
	{ KeyPress,     MODKEY,                       XK_i,             setlayout,      {.v = &layouts[2]} },
	{ KeyPress,     MODKEY,                       XK_u,             setlayout,      {.v = &layouts[5]} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_u,             setlayout,      {.v = &layouts[6]} },
    { KeyPress,     MODKEY,                       XK_y,             setlayout,      {.v = &layouts[8]} },
    { KeyPress,     MODKEY|ShiftMask,             XK_y,             setlayout,      {.v = &layouts[9]} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_space,         togglefloating, {0} },
    { KeyPress,     MODKEY,                       XK_f,             togglefullscr,  {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_s,             togglesticky,   {0} },
	{ KeyPress,     MODKEY|Mod1Mask,              XK_j,             moveresize,     {.v = "0x 25y 0w 0h" } },
	{ KeyPress,     MODKEY|Mod1Mask,              XK_k,             moveresize,     {.v = "0x -25y 0w 0h" } },
	{ KeyPress,     MODKEY|Mod1Mask,              XK_l,             moveresize,     {.v = "25x 0y 0w 0h" } },
	{ KeyPress,     MODKEY|Mod1Mask,              XK_h,             moveresize,     {.v = "-25x 0y 0w 0h" } },
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_j,             moveplace,      {.ui = WIN_S  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_k,             moveplace,      {.ui = WIN_N  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_l,             moveplace,      {.ui = WIN_E  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_h,             moveplace,      {.ui = WIN_W  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_m,             moveplace,      {.ui = WIN_C  }},
	{ KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_j,             moveresize,     {.v = "0x 0y 0w 25h" } },
	{ KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_k,             moveresize,     {.v = "0x 0y 0w -25h" } },
	{ KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_l,             moveresize,     {.v = "0x 0y 25w 0h" } },
	{ KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_h,             moveresize,     {.v = "0x 0y -25w 0h" } },
	{ KeyPress,     MODKEY,                       XK_0,             view,           {.ui = ~0 } },
	{ KeyPress,     MODKEY,                       XK_comma,         focusmon,       {.i = -1 } },
	{ KeyPress,     MODKEY,                       XK_period,        focusmon,       {.i = +1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_comma,         tagmon,         {.i = -1 } },
	{ KeyPress,     MODKEY|ShiftMask,             XK_period,        tagmon,         {.i = +1 } },
	TAGKEYS(                                      XK_w,                             0)
	TAGKEYS(                                      XK_e,                             1)
	TAGKEYS(                                      XK_d,                             2)
	TAGKEYS(                                      XK_1,                             3)
	TAGKEYS(                                      XK_2,                             4)
	TAGKEYS(                                      XK_3,                             5)
	TAGKEYS(                                      XK_4,                             6)
	TAGKEYS(                                      XK_5,                             7)
	TAGKEYS(                                      XK_6,                             8)
	TAGKEYS(                                      XK_7,                             9)
	TAGKEYS(                                      XK_8,                            10)
	TAGKEYS(                                      XK_9,                            11)
    { KeyPress,     MODKEY,                       XK_h,             viewtoleft,     {0} },
    { KeyPress,     MODKEY,                       XK_l,             viewtoright,    {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_h,             tagtoleft,      {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_l,             tagtoright,     {0} },
	{ KeyPress,     MODKEY,                       XK_q,             killclient,     {0} },
	{ KeyPress,     MODKEY|ShiftMask,             XK_q,             spawn,          {.v = quitcmd} },
    { KeyPress,     MODKEY,                       XK_bracketright,  incrgaps,       {.i = +4 } },
    { KeyPress,     MODKEY,                       XK_bracketleft,   incrgaps,       {.i = -4 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_bracketright,  incrogaps,      {.i = +4 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_bracketleft,   incrogaps,      {.i = -4 } },
    { KeyPress,     MODKEY|ControlMask,           XK_bracketright,  incrigaps,      {.i = +4 } },
    { KeyPress,     MODKEY|ControlMask,           XK_bracketleft,   incrigaps,      {.i = -4 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_0,             togglegaps,     {0} },
    { KeyPress,     MODKEY|ControlMask,           XK_0,             defaultgaps,    {0} },
	{ KeyPress,     MODKEY,            			  XK_p,  	 togglescratch,  {.ui = 0 } },
	{ KeyPress,     MODKEY,            			  XK_m,	     togglescratch,  {.ui = 1 } },
	{ KeyPress,     MODKEY,            			  XK_n,	     togglescratch,  {.ui = 2 } },
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
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
};

