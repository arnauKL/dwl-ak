/* Taken from https://github.com/djpohly/dwl/issues/466 */

// clang-format off
#include <X11/XF86keysym.h> // So I can have media keys working
#include "/home/ak/.cache/wal/colors-dwl.h" // pywal integration

#define COLOR(hex) {                    \
    ((hex >> 24) & 0xFF) / 255.0f,      \
    ((hex >> 16) & 0xFF) / 255.0f,      \
    ((hex >> 8) & 0xFF) / 255.0f,       \
    (hex & 0xFF) / 255.0f               \
}

/* appearance */
static const int sloppyfocus                = 1; /* focus follows mouse */
static const int bypass_surface_visibility  = 0; /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartborders               = 1;
static const unsigned int borderpx          = 1; /* border pixel of windows */

static const int smartgaps      = 0; /* 1 means no outer gap when there is only one window */
static int gaps                 = 0; /* 1 means gaps between windows are added */
static const unsigned int gappx = 24; /* gap pixel between windows */


static int enableautoswallow    = 1; /* enables autoswallowing newly spawned clients */
static float swallowborder      = 1.0f; /* add this multiplied by borderpx to border when a client is swallowed */


static const int showbar    = 0; /* 0 means no bar */
static const int topbar     = 0;  /* 0 means bottom bar */
static const char *fonts[]  = { "CaskaydiaCove NF:size=9:style=Bold" };

static uint32_t colors[][3] = {
    /* [...] = {fg, bg, border} */
    [SchemeNorm] = { COLOR3, BG, COLOR8 },
    [SchemeSel] = { BG, COLOR2, COLOR2 },
    [SchemeUrg] = { 0, 0, 0x770000ff },
};

static const float rootcolor[] = COLOR (BG);
//static const float rootcolor[] = COLOR (0x9a5400ff); // Brown-ish
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[] = { 0.0f, 0.5f, 0.0f, 1.0f }; /* You can also use glsl colors */


/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = { "1", "2", "3", "4", "5" };

/* logging */
static int log_level = WLR_ERROR;

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave
 * at least one example) */

static const Rule rules[] = {
    /* app_id               title       tags mask   isfloating  isterm  noswallow   monitor */
    /* examples: */
    { "foot",               NULL,       0,          0,          1,      1,          -1 },
    {NULL,     "Spotify Premium",  1 << 3,          0,          0,      1,          -1 },
    //{ "blueman-manager",    NULL,       0,          1,          0,      1,          -1 },
    // { "Gimp_EXAMPLE", NULL, 0, 1, 0, 0,
    //   -1 }, /* Start on currently visible tags floating, not tiled */
    // { "firefox_EXAMPLE", NULL, 1 << 8, 0, 0, 0,
    //   -1 }, /* Start on ONLY tag "9" */
};

/* layout(s) */
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[M]", monocle },
    { "[]=", tile },
    { "><>", NULL }, /* no layout function means floating behavior */
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland
 * clients https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
 */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't
 * be used */
static const MonitorRule monrules[] = {
    /* name       mfact  nmaster scale layout       rotate/reflect x    y */
    /* example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,
    -1,  -1 },
    */
    /* defaults */
    { NULL, 0.5f, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    /* can specify fields: rules, model, layout, variant, options */
    /* example:
    .options = "ctrl:nocaps",
    */
    .options = "caps:ctrl_modifier",
    .layout = "es",
};

/* numlock and capslock (from patch) */
static const int numlock    = 1;
static const int capslock   = 0;

/* unclutter patch */
static const int cursor_timeout = 5; // seconds?

static const int repeat_rate    = 40;
static const int repeat_delay   = 400;
/* Trackpad */
static const int tap_to_click   = 1;
static const int tap_and_drag   = 1;
static const int drag_lock      = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method
    = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method
    = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile
    = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map
    = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_ALT

#define TAGKEYS(KEY, SKEY, TAG)                                               \
    { MODKEY, KEY, view, { .ui = 1 << TAG } },                                \
        { MODKEY | WLR_MODIFIER_CTRL, KEY, toggleview, { .ui = 1 << TAG } },  \
        { MODKEY | WLR_MODIFIER_SHIFT, SKEY, tag, { .ui = 1 << TAG } },       \
    {                                                                         \
        MODKEY | WLR_MODIFIER_CTRL | WLR_MODIFIER_SHIFT, SKEY, toggletag,     \
        {                                                                     \
            .ui = 1 << TAG                                                    \
        }                                                                     \
    }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                            \
    {                                                                         \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                  \
    }

/* commands */
static const char *termcmd[] = { "foot", NULL };
static const char *menucmd[]
    = { "wmenu-run", "-b", "-i",         "-f", "CaskaydiaCove NF bold 9", "-N",
        WMENU_BG,    "-S", WMENU_COLOR3, "-s", WMENU_BG,           NULL };
static const char *screenshotcmd[] = { "grimshot", "savecopy", "area", NULL };
static const char *bluemancmd[] = { "blueman-manager", NULL };
static const char *filemanagercmd[] = { "nemo", NULL };
static const char *browsercmd[] = { "luakit", NULL };
static const char *tor_browsercmd[] = { "torbrowser-launcher", NULL };
static const char *toggle_bgcmd[]
    = { "/home/ak/scripts/toggle-swaybg.sh", NULL };
static const char *random_dark_bgcmd[]
    = { "/home/ak/scripts/random-wal.sh", "dark", NULL };
static const char *random_light_bgcmd[]
    = { "/home/ak/scripts/random-wal.sh", "light", NULL };
static const char *bat_notcmd[] = { "/home/ak/scripts/bat-notify.sh", NULL };

static const Key keys[] = {
    /* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
    /* modifier(s)                              key             function    argument */
    {MODKEY,                                    XKB_KEY_p,      spawn,      {.v = menucmd}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_Return, spawn,      {.v = termcmd}},
    {MODKEY,                                    XKB_KEY_e,      spawn,      {.v = filemanagercmd}},
    {MODKEY,                                    XKB_KEY_w,      spawn,      {.v = browsercmd}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_W,      spawn,      {.v = tor_browsercmd}},
    {WLR_MODIFIER_LOGO | WLR_MODIFIER_SHIFT,    XKB_KEY_S,      spawn,      {.v = screenshotcmd}},
    {WLR_MODIFIER_LOGO,                         XKB_KEY_b,      spawn,      {.v = bluemancmd}},
    {WLR_MODIFIER_LOGO,                         XKB_KEY_1,      spawn,      {.v = toggle_bgcmd}},
    {WLR_MODIFIER_LOGO,                         XKB_KEY_2,      spawn,      {.v = random_dark_bgcmd}},
    {WLR_MODIFIER_LOGO,                         XKB_KEY_3,      spawn,      {.v = random_light_bgcmd}},
    {WLR_MODIFIER_LOGO,                         XKB_KEY_0,      spawn,      {.v = bat_notcmd}},
    {MODKEY,                                    XKB_KEY_b,      togglebar,  {0}},   // Toggle bar visibility
    {MODKEY,                                    XKB_KEY_j,      focusstack, {.i = +1}}, // Change focus up
    {MODKEY,                                    XKB_KEY_k,      focusstack, {.i = -1}}, // Change focus down
    {MODKEY,                                    XKB_KEY_i,      incnmaster, {.i = +1}}, // Add master to layout
    {MODKEY,                                    XKB_KEY_d,      incnmaster, {.i = -1}}, // Remove master from layout
    {MODKEY,                                    XKB_KEY_h,      setmfact,   {.f = -0.05f}}, // Resize
    {MODKEY,                                    XKB_KEY_l,      setmfact,   {.f = +0.05f}}, // Resize
    {MODKEY,                                    XKB_KEY_ntilde, setmfact,   {.f = 1.5f}}, // Resize
    
    {MODKEY,                                    XKB_KEY_Return, zoom,       {0}},   // Move selected client to master position
    {MODKEY,                                    XKB_KEY_Tab,    view,       {0}},   // View 0th tag
    {MODKEY,                                    XKB_KEY_q,      killclient, {0}},   // Kill client
    // Layouts
    {MODKEY,                                    XKB_KEY_m,      setlayout,  {.v = &layouts[0]}},    // [0] is monocle
    {MODKEY,                                    XKB_KEY_t,      setlayout,  {.v = &layouts[1]}},    // [1] is tile
    {MODKEY,                                    XKB_KEY_n,      setlayout,  {.v = &layouts[2]}},    // [2] is null
    {MODKEY,                                    XKB_KEY_space,  setlayout,  {0}},   // No layout: floating
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_space,  togglefloating, {0}},   // No layout for current window
    {MODKEY,                                    XKB_KEY_f,      togglefullscreen,   {0}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_F,      togglefakefullscreen, {0}},
    // Swallow patch
    {MODKEY,                                    XKB_KEY_a,      toggleswallow,  {0}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_A,      toggleautoswallow,  {0}},
    {MODKEY,                                    XKB_KEY_0,      view,       {.ui = ~0}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_equal,  tag,        {.ui = ~0}},
    {MODKEY,                                    XKB_KEY_comma,  focusmon,   {.i = WLR_DIRECTION_LEFT}},
    {MODKEY,                                    XKB_KEY_period, focusmon,   {.i = WLR_DIRECTION_RIGHT}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_less,   tagmon,     {.i = WLR_DIRECTION_LEFT}},
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_greater,tagmon,     {.i = WLR_DIRECTION_RIGHT}},
    // Moveresize kb patch
    { MODKEY|WLR_MODIFIER_CTRL,                 XKB_KEY_j,      moveresizekb,   {.v = (int []){ 0, 40, 0, 0 }}},
    { MODKEY|WLR_MODIFIER_CTRL,                 XKB_KEY_k,      moveresizekb,   {.v = (int []){ 0, -40, 0, 0 }}},
    { MODKEY|WLR_MODIFIER_CTRL,                 XKB_KEY_l,      moveresizekb,   {.v = (int []){ 40, 0, 0, 0 }}},
    { MODKEY|WLR_MODIFIER_CTRL,                 XKB_KEY_h,      moveresizekb,   {.v = (int []){ -40, 0, 0, 0 }}},

    { MODKEY|WLR_MODIFIER_SHIFT,                XKB_KEY_J,      moveresizekb,   {.v = (int []){ 0, 0, 0, 40 }}},
    { MODKEY|WLR_MODIFIER_SHIFT,                XKB_KEY_K,      moveresizekb,   {.v = (int []){ 0, 0, 0, -40 }}},
    { MODKEY|WLR_MODIFIER_SHIFT,                XKB_KEY_L,      moveresizekb,   {.v = (int []){ 0, 0, 40, 0 }}},
    { MODKEY|WLR_MODIFIER_SHIFT,                XKB_KEY_H,      moveresizekb,   {.v = (int []){ 0, 0, -40, 0 }}},

    // Gaps
	{ MODKEY,                    XKB_KEY_g,          togglegaps,     {0} },
    //
    //
    // Workspaces, configured for spanish keyboard keys
    TAGKEYS(XKB_KEY_1, XKB_KEY_exclam, 0),
    TAGKEYS(XKB_KEY_2, XKB_KEY_quotedbl, 1),
    TAGKEYS(XKB_KEY_3, XKB_KEY_periodcentered, 2),
    TAGKEYS(XKB_KEY_4, XKB_KEY_dollar, 3),
    TAGKEYS(XKB_KEY_5, XKB_KEY_percent, 4),
    TAGKEYS(XKB_KEY_6, XKB_KEY_ampersand, 5),
    TAGKEYS(XKB_KEY_7, XKB_KEY_slash, 6),
    TAGKEYS(XKB_KEY_8, XKB_KEY_parenleft, 7),
    TAGKEYS(XKB_KEY_9, XKB_KEY_parenright, 8),
    {MODKEY | WLR_MODIFIER_SHIFT,               XKB_KEY_Q,      quit,   {0}},

    /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
    {WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT,      XKB_KEY_Terminate_Server,       quit,   {0}},
/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
 * do not remove them.
 */

#define CHVT(n)                                                                                                        \
    {                                                                                                                  \
        WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT,   XKB_KEY_XF86Switch_VT_##n,      chvt,   { .ui = (n) }                           \
    }
    CHVT(1),
    CHVT(2),
    CHVT(3),
    CHVT(4),
    CHVT(5),
    CHVT(6),
    CHVT(7),
    CHVT(8),
    CHVT(9),
    CHVT(10),
    CHVT(11),
    CHVT(12),
    /* Media keys */
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = (const char *[]){ "/home/ak/scripts/change-vol.sh", "up", NULL}}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = (const char *[]){ "/home/ak/scripts/change-vol.sh", "down", NULL}}},
    {0, XF86XK_AudioMute, spawn, {.v = (const char *[]){ "/home/ak/scripts/change-vol.sh", "mute", NULL}}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = (const char *[]){ "/home/ak/scripts/change-brightness.sh", "up", NULL}}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = (const char *[]){ "/home/ak/scripts/change-brightness.sh", "down", NULL}}},
};

static const Button buttons[] = {
    {ClkLtSymbol,                               0,      BTN_LEFT,   setlayout,  {.v = &layouts[0]}},
    {ClkLtSymbol,                               0,      BTN_RIGHT,  setlayout,  {.v = &layouts[2]}},
    {ClkTitle,                                  0,      BTN_MIDDLE, zoom,       {0}},
    {ClkStatus,                                 0,      BTN_MIDDLE, spawn,      {.v = termcmd}},
    {ClkClient,                                 MODKEY, BTN_LEFT,   moveresize, {.ui = CurMove}},
    {ClkClient,                                 MODKEY, BTN_MIDDLE, togglefloating, {0}},
    {ClkClient,                                 MODKEY, BTN_RIGHT,  moveresize, {.ui = CurResize}},
    {ClkTagBar,                                 0,      BTN_LEFT,   view,       {0}},
    {ClkTagBar,                                 0,      BTN_RIGHT,  toggleview, {0}},
    {ClkTagBar,                                 MODKEY, BTN_LEFT,   tag,        {0}},
    {ClkTagBar,                                 MODKEY, BTN_RIGHT,  toggletag,  {0}},
};
