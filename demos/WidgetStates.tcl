###############################################################################
## WidgetStates.tcl:
## This demo shows information about the Qt/KDE style currently in use.
##
###############################################################################
package require tile
ttk::setTheme tileqt
foreach {arg val} $argv {
  switch -glob -- $arg {
    -st* {ttk::theme::tileqt::applyStyle $val}
  }
}

set exit_image_data {
R0lGODlhEAAQAOepAI0LC5ANDZMODpsTE58WFqIYGKUbG6gdHbAcHKwgIK0i
IrQfH64iIrEjI7MlJboiIrYnJ7coKLgpKb8mJroqKr0qKsQqKsktLcguLrk2
NsovL780NM0wMMQ2NtEzM9IzM8g5Oa5FRdU1Nc84ONY2NtM4ONo5OdU+PsNG
Rt07O948PN8+PuI/P9VFRdtDQ9xDQ+FBQeBDQ+BEROZCQulEROpERMRVVdVO
TsdWVuZJSe1GRulISOpISOlKSu5ISOtKSuxLS+1LS8ZcXMdcXPBLS9RYWOdQ
UOVTU8dgYPZNTddbW8phYflPT/pQUM5kZPxRUc1mZtFnZ79yctVpaexgYORk
ZNlsbM5xccV1ddlubtZwcNxubutoaOhqas91dct3d+Bubt5wcN9yculvb+Zy
ctp4eOV2dtl+ftuDg+GDg9eOjs+Tk+mJidmUlNGdneOcnNqhocmqqtikpO6e
nt+lpcyxsd6srOWrq9iysuGwsNuzs92zs+yurvOrq9m3t9i4uPSsrO6vr9y4
uPCwsOG3t+S3t+C7u9+9vee7u+i7u+jAwN3Hx97Hx9/IyOLOzurNzezOzu/P
z+bU1PDQ0PLQ0OvU1OPY2OnW1uXZ2e/a2u/b2+3c3O3d3fHq6vPr6/j09Pr1
9fv19fn29vv29vn39/v39/v5+fz5+f7+/v//////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////////////////////yH+FUNyZWF0ZWQgd2l0aCBUaGUgR0lNUAAh+QQB
CgD/ACwAAAAAEAAQAAAI/gD/KaBAsKBBggoElhiCpOESJ1GmWNkSBgwPBRKE
0Nmo6JKnTpIM8Qk0iIyECDbUtKmUipQlTKRSOXozZ0wECBm8PEJVR8qZNGgO
oVrEhgsEBwiupIoDJcsdOWLMIEq1hoqDBgvsfApRREkpUTiqdBn150cDBg8y
MaowosUpUyiOGJm0KQaDBBM0NcLggcTbDjNoUOL0IsEBC3k+bSBh4i0IGkBC
4SFywMAFLancmFCRyM8JHYBSYWFioACHD4VQwZExA0aQPqgE5WhSgMAHEi4I
pQIFKVKoVIJuNHlCYICIzSzK7OHESc+XHsOfDAigIQWLGTV0+NiRhEn0FQH+
CwEQQL68efIA/gUEADs=}

set help_image_data {
R0lGODlhEAAQAMZxABpk+htl/CJo+CJr/yVt/yZt/yht+ypw/ytw/S5z/zF1
/zJ2/zV4/jZ4/zt8/zx8/z58+j1+/0B//0GA/0iA8EuC80iD/kmE/EqF/U6F
9U6H/E+I/lSK91OL/laM+1aM/FmM9FSN/1WO/1aO/lqQ/lyQ+l2Q+l+Q9lqR
/1uR/VuR/1yR/l2S/16T/16U/l+U/WCU/2OW/mma/G2c/Gyd/22d/26e/3Cf
/3eg9Hmj+X6n+Xyo/4as94es+Iet+oSu/4eu/Yiw/4yy/5S3/pq5+Zq8/6C/
/qbD/6nF/arF/arG/qzH/7DK/7bN/LfN+rXO/7vQ+b/Q9LzS/r7S+8XU8sLW
/sfX+MjY+sra+c/e/NDf/tTg+Nji+Nfj/dbk/trk+Nzk9tnl/dzm+N3m993n
+97p/97q/+Lr/uLs/+vv+Orx/+3y++7y/PD1//j6//z9//3+////////////
/////////////////////////////////////////////////yH+FUNyZWF0
ZWQgd2l0aCBUaGUgR0lNUAAh+QQBCgB/ACwAAAAAEAAQAAAHuYB/goOEhYYP
EyUmDwuGgg4dSGdfXGRQHgeFDjJaWGJxcWxbXjgFhBtSU2txamhvcVlVGoMP
QExOcW1MTFZxZUo6A4ISQ0VGZk9FRGBxSSMhCYIYP9TUPGNxYSkhIQ2CFjTh
NDVUcV0vIukMghEtLi0sKmluMSj2KAiCCisw/TBNS/zBIBFg0AUbCGdEuXID
oQ0IhA6c2LEjB5w4QSiCAFCIAAcfQo4sEdIjA0dHBip88EBBgKOXhgIBADs=
====}

image create photo exit_image -data $exit_image_data
image create photo help_image -data $help_image_data

set win {}
set row 0; set column 0
set widgets {button checkbutton radiobutton entry menubutton combobox rcombobox
             scrollbar scale progressbar notebook panedwindow labelframe}
set states {active disabled focus pressed selected readonly background
             alternate}
foreach widget $widgets {
  foreach state $states {
    switch $widget {
      labelframe {
        set w [ttk::$widget $win.${widget}_$state -class Toolbar]
        ttk::menubutton $w.mb -text Toolbar -width 8
        pack $w.mb -fill both
      }
      rcombobox {
        set w [ttk::combobox $win.${widget}_$state -state readonly]
      }
      default {
        set w [ttk::$widget $win.${widget}_$state]
      }
    }
    catch { $w configure -from 0 -to 100 }
    catch { $w configure -value 35 }
    catch { $w configure -text $state }
    catch { $w configure -image help_image -compound left }
    catch { $w configure -orient horizontal }
    catch { $w configure -exportselection 0}
    catch { $w delete 0 end }
    catch { $w insert end "$state" }
    catch { $w selection range 0 5 }
    if {$widget == "notebook"} {
      set pw [ttk::panedwindow $w.client -orient horizontal]
      $w add $pw -text "Demo 1"
      $pw state $state
      ttk::label $pw.l -text "Notebook Page"
      pack $pw.l -fill both
      if {$state != "pressed"} {
        set pw [ttk::panedwindow $w.client2 -orient horizontal]
        $w add $pw -text "Demo 2"
      }
    } else {
      $w state $state
    }
    switch -glob $widget {
      *combobox - menubutton - entry {
        $w configure -width 8
      }
    }
    grid $w -row $row -column $column -sticky snw -padx 1 -pady 1
    incr column
    #if {$column > 4} {incr row; set column 0}
  }
  incr row
  set column 0
}
ttk::labelframe $win.themes -text Themes:
  set col -1; set row 0
  foreach style [lsort [ttk::theme::tileqt::availableStyles]] {
    if {$col > 6} {incr row; set col -1}
    grid [ttk::button $win.themes.[string tolower $style] -text $style \
          -command "ttk::theme::tileqt::applyStyle \{$style\}"] \
      -column [incr col] -row $row -sticky snew -padx 1 -pady 1
  }
  ttk::button $win.themes.exit -text Exit -image exit_image \
    -compound left -command exit
  grid $win.themes.exit -columnspan 8 -padx 5 -pady 10
grid $win.themes -columnspan [llength $states] -padx 2 -pady 2
grab set $win.themes
