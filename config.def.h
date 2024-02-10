/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu Sans:size=10" };
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#BBBBBB", "#222222", "#444444" },
	[SchemeSel]  = { "#EEEEEE", "#643500", "#FF2200" },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "--class", "sp_term,Alacritty", "-T", "scratchpad", NULL };
const char *spcmd2[] = {"alacritty", "--class", "sp_music,Alacritty", "-T", "sp_music", "-e", "ncmpcpp", NULL };
const char *spcmd3[] = {"alacritty", "--class", "sp_news,Alacritty", "-T", "sp_news", "-e", "newsraft", NULL };
const char *spcmd4[] = {"alacritty", "--class", "sp_calc,Alacritty", "-T", "sp_calc", "-e", "qalc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"scratchpad",   spcmd1},
	{"sp_music",     spcmd2},
	{"sp_news",      spcmd3},
	{"sp_calc",      spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "w", "e", "d" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title              tags mask   isfloating   monitor */
	{ "floatme",      NULL,       NULL,              0,          1,           -1 },
	{ "firefox",      NULL,       NULL,              1 << 9,     0,           -1 },
	{ "Chromium",     NULL,       NULL,              1 << 9,     0,           -1 },
	{ "thunderbird",  NULL,       NULL,              1 << 10,    0,           -1 },
	{ "discord",      NULL,       NULL,              1 << 11,    0,           -1 },
	{ NULL,           "sp_term",  NULL,              SPTAG(0),   1,           -1 },
	{ NULL,           "sp_music", NULL,              SPTAG(1),   1,           -1 },
	{ NULL,           "sp_news",  NULL,              SPTAG(2),   1,           -1 },
	{ NULL,           "sp_calc",  NULL,              SPTAG(3),   1,           -1 },

	{ "firefox",      "Places",   NULL,              0,          1,           -1 },
	{ "discord",      "discord",  "Discord Updater", 0,          1,           -1 },
	{ NULL,           NULL,       "Event Tester",    0,          1,           -1 }, /* xev */
	{ NULL,           NULL,       "surf-dl",         0,          1,           -1 },
	{ "Gimp",         "gimp",     "GIMP Startup",    0,          1,           -1 },
	{ "steam",        NULL,       "Special Offers",  0,          1,           -1 },
	{ "Hydrogen",     NULL,       "Mixer",           0,          1,           -1 },
	{ "zoom",         "zoom",     "Polls",           0,          1,           -1 },
	{ "Sxiv",         NULL,       NULL,              0,          1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* commands */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *quitmenucmd[]  = { "quitmenu", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = quitmenucmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_i,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_s,      zoom,           {0} },
	{ MODKEY|ControlMask,           XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_0,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_space,  togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_m,      togglescratch,  {.ui = 1 } },
	{ MODKEY,                       XK_n,      togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_slash,  togglescratch,  {.ui = 3 } },
	{ MODKEY|ShiftMask,             XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ControlMask,           XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ControlMask,           XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ControlMask,           XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      movethrow,      {.ui = DIR_N }},
	{ MODKEY|ControlMask|ShiftMask, XK_j,      movethrow,      {.ui = DIR_S }},
	{ MODKEY|ControlMask|ShiftMask, XK_h,      movethrow,      {.ui = DIR_W }},
	{ MODKEY|ControlMask|ShiftMask, XK_l,      movethrow,      {.ui = DIR_E }},
	{ MODKEY|ControlMask|ShiftMask, XK_n,      movethrow,      {.ui = DIR_C }},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_w,                      9)
	TAGKEYS(                        XK_e,                      10)
	TAGKEYS(                        XK_d,                      11)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
};
