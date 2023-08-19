/* See LICENSE file for copyright and license details. */

/* appearance */
static const int overviewgappo      = 30;        /* on overview,gap in win and border */
static const int overviewgappi      = 20;        /* on overview,gap in win and win */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Liberation Sans:style:Regular:size=11" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "\\", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.7;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout overviewlayout = { "田",  overview };

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "品",      htile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[]=",      vtile },
//	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG,cmd1) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG, .v = cmd1} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier             key                  function        argument */          
	{ MODKEY,               XK_u,                scratchpad_hide, {0} },   /*  hide and unhide  */
	{ MODKEY,               XK_o,                scratchpad_show, {0} },   
//	{ MODKEY,               XK_equal,            scratchpad_remove,{0} },
	{ MODKEY,               XK_n,                newempty,       {0} },
    { MODKEY|ShiftMask,     XK_q,                spawn, SHCMD("kill -9 $(xprop | grep _NET_WM_PID | awk '{print $3}')") }, /* kill -9 selected window */
	{ MODKEY,               XK_l,                shiftview,      {.i = +1 } },
	{ MODKEY,               XK_j,                shiftview,      {.i = -1 } },
	{ MODKEY,               XK_Right,            shiftview,      {.i = +1 } },
	{ MODKEY,               XK_Left,             shiftview,      {.i = -1 } },
	{ ShiftMask,            XK_End,              shiftview,      {.i = -1 } },
	{ MODKEY,               XK_p,                spawn,      SHCMD("bemenu-run -ibnl10 --fn 'CodeNewRoman Nerd Font Mono Italic 15' -p'run' -M13 -W0.3") },
	{ MODKEY, 		        XK_semicolon,        spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,     XK_Return,           spawn,          {.v = termcmd } },                      
	{ MODKEY,               XK_b,                togglebar,      {0} },
	{ MODKEY,               XK_Down,             focusstackvis,  {.i = +1 } },
	{ MODKEY,               XK_Up,               focusstackvis,  {.i = -1 } },
	{ MODKEY,               XK_k,                focusstackvis,  {.i = +1 } },
	{ MODKEY,               XK_i,                focusstackvis,  {.i = -1 } },
	{ MODKEY|Mod1Mask,      XK_k,                focusstackhid,  {.i = +1 } },
	{ MODKEY|Mod1Mask,      XK_i,                focusstackhid,  {.i = -1 } },
	{ MODKEY,               XK_e,                incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_i,                setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,     XK_k,                setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_Return,           zoom,           {0} },
	{ MODKEY,               XK_space,            zoom,           {0} },
	{ MODKEY,               XK_Tab,              view,           {0} },
	{ MODKEY,               XK_c,                killclient,     {0} },
	{ MODKEY,               XK_slash,            killclient,     {0} },
	{ MODKEY,               XK_t,                setlayout,      {.v = &layouts[0]} },  /*  cycle in htile and vtile layout */
	{ MODKEY,               XK_f,                setlayout,      {.v = &layouts[1]} },  /* cycle in monocle and previous layout */
	{ MODKEY,               XK_m,                togglefullscr,  {0} },
	{ MODKEY|ShiftMask,     XK_space,            togglefloating, {0} },
	{ MODKEY,               XK_0,                view,           {.ui = ~0 } },
	{ MODKEY,               XK_a,                toggleoverview, {0} },      /* toggle overview layout or go to tag which own focus window */
	{ MODKEY|ShiftMask,     XK_0,                tag,            {.ui = ~0 } },
	{ MODKEY,               XK_comma,            focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,           focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,            tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,           tagmon,         {.i = +1 } },
	{ MODKEY,               XK_s,                show,           {0} },
	{ MODKEY|ShiftMask,     XK_h,                showall,        {0} },
	{ MODKEY,               XK_h,                hide,           {0} },
    { 0,         XF86XK_AudioLowerVolume,    spawn, SHCMD("~/.dwm/voldn.sh") },            /* volume up                 */
    { 0,         XF86XK_AudioRaiseVolume,    spawn, SHCMD("~/.dwm/volup.sh") },            /* volume down               */
    { 0,         XF86XK_MonBrightnessDown,   spawn, SHCMD("~/.dwm/bridn.sh") },            /* brightness down           */
    { 0,         XF86XK_MonBrightnessUp,     spawn, SHCMD("~/.dwm/briup.sh") },            /* brightness up             */
	TAGKEYS(                XK_1,                                0,0)
	TAGKEYS(                XK_2,                                1,0)
	TAGKEYS(                XK_3,                                2,0)
	TAGKEYS(                XK_4,                                3,0)
	TAGKEYS(                XK_5,                                4,0)
	TAGKEYS(                XK_6,                                5,0)
	TAGKEYS(                XK_7,                                6,"st ranger /seven")
	TAGKEYS(                XK_8,                                7,"st ranger /eight")
	TAGKEYS(                XK_9,                                8,0)
	TAGKEYS(                XK_backslash,                        9,0)
	TAGKEYS(                XK_z,                                10,"st mpv --shuffle /seven/music/aac/")
	{ MODKEY|ShiftMask,     XK_F12,              quit,           {0} },                                
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

