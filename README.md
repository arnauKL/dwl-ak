# dwl - personal fork

> From the main README:

dwl is a compact, hackable compositor for [Wayland] based on [wlroots]. It is
intended to fill the same space in the Wayland world that dwm does in X11,
primarily in terms of functionality, and secondarily in terms of
philosophy. Like dwm, dwl is:

- Easy to understand, hack on, and extend with patches
- One C source file (or a very small number) configurable via `config.h`
- Tied to as few external dependencies as possible

## Patches

- [`dwl-bar`](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/bar): uses `slstatus` to output info into dwl, which now has a bar.
- `wallust` integration: added a way to re-compile dwl using wallust to generate a theme (`dwl-colors.h`) (homemade).
- mouse warping: simmilar to hyprland. When changing focus with Alt+J / Alt+K, have the mouse warp to the center of the new client (homemade).
