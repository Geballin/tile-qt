###############################################################################
## StyleIntrospection.tcl:
## This demo shows information about the Qt/KDE style currently in use.
##
###############################################################################
package require tile
ttk::setTheme tileqt

set win {}
label $win.lbl_option   -text Option:
label $win.lbl_active   -text -active
label $win.lbl_disabled -text -disabled
label $win.lbl_inactive -text -inactive
label $win.lbl_explain  -text Explanation:
grid $win.lbl_option $win.lbl_active $win.lbl_disabled $win.lbl_inactive \
     $win.lbl_explain -sticky snew -padx 2 -pady 2
foreach {option explanation} {
                background      {Returns the background color.}
                foreground      {Returns the foreground color.}
                button          {Returns the button color.}
                light           {Returns the light color.}
                dark            {Returns the dark color.}
                mid             {Returns the mid color.}
                text            {Returns the text foreground color. }
                base            {Returns the base color.}
                midlight        {Returns the midlight color.}
                brightText      {Returns the bright text foreground color.}
                buttonText      {Returns the button text foreground color.}
                shadow          {Returns the shadow color.}
                highlight       {Returns the highlight color.}
                highlightedText {Returns the highlighted text color.}
                link            {Returns the unvisited link text color.}
                linkVisited     {Returns the visited link text color.}} {
  label $win.$option -text "-$option:" -anchor w
  
  set active_colour [ttk::theme::tileqt::currentThemeColour -$option]
  label $win.${option}_active_colour -background $active_colour \
    -relief raised -borderwidth 1
  label $win.${option}_active_colour_value -text $active_colour

  set disabled_colour [ttk::theme::tileqt::currentThemeColour \
                             -disabled -$option]
  label $win.${option}_disabled_colour -background $disabled_colour \
    -relief raised -borderwidth 1
  label $win.${option}_disabled_colour_value -text $disabled_colour

  set inactive_colour [ttk::theme::tileqt::currentThemeColour \
                             -inactive -$option]
  label $win.${option}_inactive_colour -background $inactive_colour \
    -relief raised -borderwidth 1
  label $win.${option}_inactive_colour_value -text $inactive_colour
  
  label $win.${option}_explain -text $explanation -anchor w
  grid $win.$option $win.${option}_active_colour \
       $win.${option}_disabled_colour $win.${option}_inactive_colour \
       $win.${option}_explain -sticky snew -padx 2 -pady 2
  grid x $win.${option}_active_colour_value \
       $win.${option}_disabled_colour_value \
       $win.${option}_inactive_colour_value -sticky snew -padx 2 -pady 2
}
