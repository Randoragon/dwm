/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappi     = 10;       /* inner gap between windows */
static const unsigned int gappo     = 10;       /* outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar */
static const int startontag         = 1;        /* 0 means no tag active on start */
static const char *fonts[]          = { "monospace:size=10" };
static int lrpad                    = 2;        /* pixel sum of left and right padding for bar text. ~0 for auto */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*                   fg         bg         border    */
    [SchemeNorm]     = { "#000000", "#000000", col_gray2  }, // Only border is important
    [SchemeSel]      = { "#000000", "#000000", col_cyan   }, // Only border is important
    [SchemeStatus]   = { col_gray3, col_gray1, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { col_gray3, col_gray1, "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeTagsUrg]  = { col_gray1, col_gray3, "#000000"  }, // Tagbar left urgent {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { col_gray3, col_gray1, "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
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

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spranger",    spcmd2},
    {"keepassxc",   spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance       title           tags mask  isfloating  isterminal  noswallow  monitor  float x,y,w,h,border  */
    { "Gimp",    NULL,          NULL,           0,         1,          0,           0,        -1       -1,-1,-1,-1,-1        },
    { "Firefox", NULL,          NULL,           1 << 8,    0,          0,          -1,        -1       -1,-1,-1,-1,-1        },
    { "st",      NULL,          NULL,           0,         0,          1,          -1,        -1       -1,-1,-1,-1,-1        },
    { NULL,      NULL,          "Event Tester", 0,         1,          0,           1,        -1       -1,-1,-1,-1,-1        }, /* xev */
    { NULL,      "spterm",      NULL,           SPTAG(0),  1,          0,           1,        -1       -1,-1,-1,-1,-1        },
    { NULL,      "spfm",        NULL,           SPTAG(1),  1,          0,           1,        -1       -1,-1,-1,-1,-1        },
    { NULL,      "keepassxc",   NULL,           SPTAG(2),  0,          0,           1,        -1       -1,-1,-1,-1,-1        },
};

/* layout(s) */
static const float mfact     = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;     /* number of clients in master area */
static const int resizehints = 1;     /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 0; /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

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
    { "[\\]",      dwindle },
    { "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { KeyPress,   MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { KeyPress,   MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { KeyPress,   MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { KeyPress,   MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static Key keys[] = {
   /* type          modifier                      key        function        argument */
    { KeyPress,     MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { KeyPress,     MODKEY,                       XK_b,      togglebar,      {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_j,      rotatestack,    {.i = +1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_k,      rotatestack,    {.i = -1 } },
    { KeyPress,     MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { KeyPress,     MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { KeyPress,     MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { KeyPress,     MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
    { KeyPress,     MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
    { KeyPress,     MODKEY,                       XK_Return, zoom,           {0} },
    { KeyPress,     MODKEY,                       XK_Tab,    view,           {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { KeyPress,     MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { KeyPress,     MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { KeyPress,     MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { KeyPress,     MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
    { KeyPress,     MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
    { KeyPress,     MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
    { KeyPress,     MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
    { KeyPress,     MODKEY,                       XK_y,      setlayout,      {.v = &layouts[8]} },
    { KeyPress,     MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[7]} },
    { KeyPress,     MODKEY,                       XK_space,  setlayout,      {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
    { KeyPress,     MODKEY|Mod1Mask,              XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
    { KeyPress,     MODKEY|Mod1Mask,              XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
    { KeyPress,     MODKEY|Mod1Mask,              XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
    { KeyPress,     MODKEY|Mod1Mask,              XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_Down,   moveplace,      {.ui = WIN_S  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_Up,     moveplace,      {.ui = WIN_N  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_Right,  moveplace,      {.ui = WIN_E  }},
    { KeyPress,     MODKEY|Mod1Mask|ShiftMask,    XK_Left,   moveplace,      {.ui = WIN_W  }},
    { KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
    { KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
    { KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
    { KeyPress,     MODKEY|Mod1Mask|ControlMask,  XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
    { KeyPress,     MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { KeyPress,     MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { KeyPress,     MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                                      XK_1,                      0)
    TAGKEYS(                                      XK_2,                      1)
    TAGKEYS(                                      XK_3,                      2)
    TAGKEYS(                                      XK_4,                      3)
    TAGKEYS(                                      XK_5,                      4)
    TAGKEYS(                                      XK_6,                      5)
    TAGKEYS(                                      XK_7,                      6)
    TAGKEYS(                                      XK_8,                      7)
    TAGKEYS(                                      XK_9,                      8)
    { KeyPress,     MODKEY,                       XK_h,      viewtoleft,     {0} },
    { KeyPress,     MODKEY,                       XK_l,      viewtoright,    {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_h,      tagtoleft,      {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_l,      tagtoright,     {0} },
    { KeyPress,     MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { KeyPress,     MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
    { KeyPress,     MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
    { KeyPress,     MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
    { KeyPress,     MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
    { KeyPress,     MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
    { KeyPress,     MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
    { KeyPress,     MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
    { KeyPress,     MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
    { KeyPress,     MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
    { KeyPress,     MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
    { KeyPress,     MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
    { KeyPress,     MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
    { KeyPress,     MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
    { KeyPress,     MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
    { KeyPress,     MODKEY,                       XK_y,      togglescratch,  {.ui = 0 } },
    { KeyPress,     MODKEY,                       XK_u,      togglescratch,  {.ui = 1 } },
    { KeyPress,     MODKEY,                       XK_x,      togglescratch,  {.ui = 2 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
    /* signum       function        argument  */
    { 1,            setlayout,      {.v = 0} },
};
