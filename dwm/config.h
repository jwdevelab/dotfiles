/*
     ____                              _     _       ____  ___
    / __ \__  ______  ____ _____ ___  (_)___| |     / /  |/  /
   / / / / / / / __ \/ __ `/ __ `__ \/ / ___/ | /| / / /|_/ / 
  / /_/ / /_/ / / / / /_/ / / / / / / / /__ | |/ |/ / /  / /  
 /_____/\__, /_/ /_/\__,_/_/ /_/ /_/_/\___/ |__/|__/_/  /_/   
       /____/                                                 
*/
static const unsigned int borderpx  = 2;        /* border pixel of windows */ 
static const unsigned int snap      = 32;       /* snap pixel */ 
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=9" };
static const char dmenufont[]       = "monospace:size=9";
static const char col_gray1[]       = "#24221f";
static const char col_gray2[]       = "#4f4b41";
static const char col_gray3[]       = "#757575";
static const char col_gray4[]       = "#ebdbb2";
static const char col_gray5[]       = "#91856e";
static const char col_cyan[]        = "#252221";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_cyan, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray5  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm1", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spterm2", "-g", "120x34", NULL };
const char *spcmd3[] = {"st", "-n", "spspt", "-g", "144x41", "-e", "spt", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm1",  spcmd1},
	{"spterm2",    spcmd2},
	{"spspt",  spcmd3},
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Nemo",                  NULL,       NULL,       0,            1,           -1 },
	{ "Nitrogen",              NULL,       NULL,       0,            1,           -1 },
	{ "Lxappearance",          NULL,       NULL,       0,            1,           -1 },
	{ "Onboard",               NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",               NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,		  "spterm1",  	NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spterm2",   		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "spspt",  	NULL,		SPTAG(2),		1,			 -1 },
};


/* layout(s) */
static const float mfact     = 0.495; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "horizgrid.c"
#include "tatami.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "|",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|+|",      tatami },
	{ "###",      horizgrid },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray5, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *mutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *brdown[] = { "brightnessctl", "set", "20-", NULL }; 
static const char *brup[] = { "brightnessctl", "set", "20+", NULL }; 
static const char *scshot[]  = { "flameshot", "gui", NULL };
static const char *runrofi[]  = { "rofi", "-show", "run", NULL };
static const char *menurofi[]  = { "rofi", "-show", "drun", NULL };
static const char *bluerofi[]  = { "rofi-bluetooth", NULL };
static const char *wifirofi[]  = { "rofi-network", NULL };
static const char *calcrofi[]  = { "rofi", "-show", "calc", NULL };
static const char *filerofi[]  = { "rofi", "-modi", "filebrowser", "-show", "filebrowser", NULL };
static const char *lock[]  = { "slock", NULL };
static const char *powerrofi[]  = { "powerrofi.sh", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *keyvir[]  = { "onboard", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *nemo[]  = { "nemo", NULL };
static const char *killici[]  = { "xkill", NULL };
static const char *kcolor[]  = { "kcolorchooser", NULL };
static const char *setr[] = { "setxkbmap", "tr", NULL }; 
static const char *sets[] = { "setxkbmap", "us", NULL }; 

#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = nemo } },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          {.v = keyvir } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = setr } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = sets } },
	{ 0,                            XK_Print,  spawn,          {.v = scshot } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = firefox } },
	{ MODKEY,                       XK_x,      spawn,          {.v = kcolor } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = runrofi } },
	{ MODKEY,                       XK_d,      spawn,          {.v = menurofi } },
	{ MODKEY,                       XK_b,      spawn,          {.v = bluerofi } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = wifirofi } },
	{ MODKEY,                       XK_v,      spawn,          {.v = calcrofi } },
	{ MODKEY,                       XK_a,      spawn,          {.v = filerofi } },
	{ MODKEY,                       XK_c,      spawn,          {.v = lock } },
	{ MODKEY|ShiftMask,             XK_Print,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_w,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      togglebar,      {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_y,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_y,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.04} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.04} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_space,  spawn,          {.v = termcmd } },
//	{ MODKEY,                     XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_e,      view,           {0} },
	{ MODKEY,                       XK_i,      view,           {0} },
	{ MODKEY|ControlMask,           XK_q,      spawn,          {.v = killici } },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_Return, setlayout,      {0} },
	{ MODKEY|ControlMask,           XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ControlMask,           XK_y,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ControlMask,           XK_u,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_Return, togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_m,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ 0, XF86XK_AudioMute, spawn, {.v = mutecmd } },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = brup } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = brdown } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = powerrofi } },
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
	{ MODKEY,                 			XK_F1, 	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            	      		XK_F2,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            		      	XK_F3,	   togglescratch,  {.ui = 2 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
