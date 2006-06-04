namespace eval tile::theme::tileqt {
  variable PreviewInterp {}

  proc updateLayouts {} {
    ## Variable "theme" should be defined by the C part of the extension.
    variable theme
    if {![info exists theme]} {return}
    style theme use tileqt
    # puts "Current Qt Theme: [currentThemeName] ($theme)"
    switch -glob -- [string tolower $theme] {
      b3 -
      default -
      plastik -
      metal4kde -
      polyester -
      liquid -
      platinum -
      highcolor -
      highcontrast -
      light -
      light, -
      {light, 2nd revision} -
      {light, 3rd revision} -
      phase -
      baghira -
      help 
      {
        # 3 Arrows...
        style layout Horizontal.TScrollbar {
          Scrollbar.background
          Horizontal.Scrollbar.trough -children {
              Horizontal.Scrollbar.leftarrow -side left
              Horizontal.Scrollbar.rightarrow -side right
              Horizontal.Scrollbar.leftarrow -side right
              Horizontal.Scrollbar.thumb -side left -expand true -sticky we
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Scrollbar.background
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.uparrow -side top
              Vertical.Scrollbar.downarrow -side bottom
              Vertical.Scrollbar.uparrow -side bottom
              Vertical.Scrollbar.thumb -side top -expand true -sticky ns
          }
        };# style layout Vertical.TScrollbar
      }
      keramik -
      thinkeramik {
        # 3 Arrows...
        style layout Horizontal.TScrollbar {
          Scrollbar.background
          Horizontal.Scrollbar.trough -children {
              Horizontal.Scrollbar.leftarrow -side left
              Horizontal.Scrollbar.rightarrow -side right -children {
                Horizontal.Scrollbar.subleftarrow -side left
                Horizontal.Scrollbar.subrightarrow -side right
              }
              Horizontal.Scrollbar.thumb -side left -expand true -sticky we
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Scrollbar.background
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.uparrow -side top
              Vertical.Scrollbar.downarrow -side bottom -children {
                Vertical.Scrollbar.subuparrow -side top
                Vertical.Scrollbar.subdownarrow -side bottom
              }
              Vertical.Scrollbar.thumb -side top -expand true -sticky ns
          }
        };# style layout Vertical.TScrollbar
      }
      system -
      systemalt
      {
        ## 2 arrows at ONE edge of the scrollbar
        style layout Horizontal.TScrollbar {
          Horizontal.Scrollbar.trough -children {
              Horizontal.Scrollbar.rightarrow -side right
              Horizontal.Scrollbar.leftarrow -side right
              Horizontal.Scrollbar.thumb -side left -expand true -sticky we
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.downarrow -side bottom
              Vertical.Scrollbar.uparrow -side bottom
              Vertical.Scrollbar.thumb -side top -expand true -sticky ns
          }
        };# style layout Vertical.TScrollbar
      }
      bluecurve -
      cde -
      compact -
      windows -
      motif -
      motifplus -
      riscos -
      sgi -
      acqua -
      marble -
      dotnet -
      default {
        ## Default layout: 2 arrows at the two edges of the scrollbar
        style layout Horizontal.TScrollbar {
          Horizontal.Scrollbar.trough -children {
              Horizontal.Scrollbar.leftarrow -side left
              Horizontal.Scrollbar.rightarrow -side right
              Horizontal.Scrollbar.thumb -side left -expand true -sticky we
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.uparrow -side top
              Vertical.Scrollbar.downarrow -side bottom
              Vertical.Scrollbar.thumb -side top -expand true -sticky ns
          }
        };# style layout Vertical.TScrollbar
      }
    }
  }; # updateLayouts

  proc updateStyles {} {
    style theme settings tileqt {
      style default "." \
         -background [currentThemeColour -active -background] \
         -foreground [currentThemeColour -active -foreground] \
         -selectforeground [currentThemeColour -highlightedText] \
         -selectbackground [currentThemeColour -highlight] \
         ;
      style map "." -foreground [list \
         active          [currentThemeColour -active   -foreground] \
         disabled        [currentThemeColour -disabled -foreground] \
         focus           [currentThemeColour -active   -foreground] \
         pressed         [currentThemeColour -active   -foreground] \
         selected        [currentThemeColour -active   -foreground] \
      ] -background [list \
         active          [currentThemeColour -active   -background] \
         disabled        [currentThemeColour -disabled -background] \
         pressed         [currentThemeColour -active   -background] \
         pressed         [currentThemeColour -active   -background] \
         selected        [currentThemeColour -active   -background] \
      ] -selectforeground [list \
         active          [currentThemeColour -active   -highlightedText] \
         disabled        [currentThemeColour -disabled -highlightedText] \
         focus           [currentThemeColour -active   -highlightedText] \
         pressed         [currentThemeColour -active   -highlightedText] \
         selected        [currentThemeColour -active   -highlightedText] \
      ] -selectbackground [list \
         active          [currentThemeColour -active   -highlight] \
         disabled        [currentThemeColour -disabled -highlight] \
         focus           [currentThemeColour -active   -highlight] \
         pressed         [currentThemeColour -active   -highlight] \
         selected        [currentThemeColour -active   -highlight] \
      ]

      style map TButton -foreground [list \
         active          [currentThemeColour -active   -buttonText] \
         disabled        [currentThemeColour -disabled -buttonText] \
         focus           [currentThemeColour -active   -buttonText] \
         pressed         [currentThemeColour -active   -buttonText] \
         selected        [currentThemeColour -active   -buttonText] \
      ] -background [list \
         active          [currentThemeColour -active   -button] \
         disabled        [currentThemeColour -disabled -button] \
         focus           [currentThemeColour -active   -button] \
         pressed         [currentThemeColour -active   -button] \
         selected        [currentThemeColour -active   -button] \
      ]
      style default TButton      -width -11 -padding {4 4 4 4}

      style map TCheckbutton -foreground [list \
         active          [currentThemeColour -active   -buttonText] \
         disabled        [currentThemeColour -disabled -buttonText] \
         focus           [currentThemeColour -active   -buttonText] \
         pressed         [currentThemeColour -active   -buttonText] \
         selected        [currentThemeColour -active   -buttonText] \
      ] -background [list \
         active          [currentThemeColour -active   -button] \
         disabled        [currentThemeColour -disabled -button] \
         focus           [currentThemeColour -active   -button] \
         pressed         [currentThemeColour -active   -button] \
         selected        [currentThemeColour -active   -button] \
      ]
      style default TCheckbutton -padding {0 1 0 1}
      
      style map TCombobox -foreground [list \
         active          [currentThemeColour -active   -buttonText] \
         disabled        [currentThemeColour -disabled -buttonText] \
         focus           [currentThemeColour -active   -buttonText] \
         pressed         [currentThemeColour -active   -buttonText] \
         selected        [currentThemeColour -active   -buttonText] \
      ] -background [list \
         active          [currentThemeColour -active   -button] \
         disabled        [currentThemeColour -disabled -button] \
         focus           [currentThemeColour -active   -button] \
         pressed         [currentThemeColour -active   -button] \
         selected        [currentThemeColour -active   -button] \
      ]
      style default TCombobox    ;#-padding {3 2 3 2}
      
      style map TEntry -foreground [list \
         active          [currentThemeColour -active   -text] \
         disabled        [currentThemeColour -disabled -text] \
         focus           [currentThemeColour -active   -text] \
         pressed         [currentThemeColour -active   -text] \
         selected        [currentThemeColour -active   -text] \
      ] -background [list \
         active          [currentThemeColour -active   -base] \
         disabled        [currentThemeColour -disabled -base] \
         focus           [currentThemeColour -active   -base] \
         pressed         [currentThemeColour -active   -base] \
         selected        [currentThemeColour -active   -base] \
      ] -selectforeground [list \
         active          [currentThemeColour -active   -highlightedText] \
         disabled        [currentThemeColour -disabled -highlightedText] \
         focus           [currentThemeColour -active   -highlightedText] \
         pressed         [currentThemeColour -active   -highlightedText] \
         selected        [currentThemeColour -active   -highlightedText] \
      ] -selectbackground [list \
         active          [currentThemeColour -active   -highlight] \
         disabled        [currentThemeColour -disabled -highlight] \
         focus           [currentThemeColour -active   -highlight] \
         pressed         [currentThemeColour -active   -highlight] \
         selected        [currentThemeColour -active   -highlight] \
      ]
      style default TEntry       -padding {3 2 3 2}
      
      style default TLabelframe  -background [currentThemeColour -background] \
                                 -padding 0
      
      style map TMenubutton -foreground [list \
         active          [currentThemeColour -active   -buttonText] \
         disabled        [currentThemeColour -disabled -buttonText] \
         focus           [currentThemeColour -active   -buttonText] \
         pressed         [currentThemeColour -active   -buttonText] \
         selected        [currentThemeColour -active   -buttonText] \
      ] -background [list \
         active          [currentThemeColour -active   -button] \
         disabled        [currentThemeColour -disabled -button] \
         focus           [currentThemeColour -active   -button] \
         pressed         [currentThemeColour -active   -button] \
         selected        [currentThemeColour -active   -button] \
      ] -selectforeground [list \
         active          [currentThemeColour -active   -highlightedText] \
         disabled        [currentThemeColour -disabled -highlightedText] \
         focus           [currentThemeColour -active   -highlightedText] \
         pressed         [currentThemeColour -active   -highlightedText] \
         selected        [currentThemeColour -active   -highlightedText] \
      ] -selectbackground [list \
         active          [currentThemeColour -active   -highlight] \
         disabled        [currentThemeColour -disabled -highlight] \
         focus           [currentThemeColour -active   -highlight] \
         pressed         [currentThemeColour -active   -highlight] \
         selected        [currentThemeColour -active   -highlight] \
      ]
      style default TMenubutton  -width -11 -padding {3 2 3 2}
      #style default TNotebook    -expandtab {2 2 2 2}
      #style default TNotebook    -expandtab {1 0 1 0}

      style map TRadiobutton -foreground [list \
         active          [currentThemeColour -active   -buttonText] \
         disabled        [currentThemeColour -disabled -buttonText] \
         focus           [currentThemeColour -active   -buttonText] \
         pressed         [currentThemeColour -active   -buttonText] \
         selected        [currentThemeColour -active   -buttonText] \
      ] -background [list \
         active          [currentThemeColour -active   -button] \
         disabled        [currentThemeColour -disabled -button] \
         focus           [currentThemeColour -active   -button] \
         pressed         [currentThemeColour -active   -button] \
         selected        [currentThemeColour -active   -button] \
      ]
      style default TRadiobutton -padding {0 1 0 1}

      style map Toolbutton -foreground [list \
         active          [currentThemeColour -active   -buttonText] \
         disabled        [currentThemeColour -disabled -buttonText] \
         focus           [currentThemeColour -active   -buttonText] \
         pressed         [currentThemeColour -active   -buttonText] \
         selected        [currentThemeColour -active   -buttonText] \
      ] -background [list \
         active          [currentThemeColour -active   -button] \
         disabled        [currentThemeColour -disabled -button] \
         focus           [currentThemeColour -active   -button] \
         pressed         [currentThemeColour -active   -button] \
         selected        [currentThemeColour -active   -button] \
      ]
      style default Toolbutton   ;#-padding {4 4}
    };# style theme settings tileqt
  };# updateStyles

  proc kdeLocate_kdeglobals {} {
    set KDE_dirs {}
    # As a first step, examine the KDE env variables...
    global env
    foreach {var cmd} {KDEHOME {kde-config --localprefix} 
                 KDEDIRS {}
                 KDEDIR  {kde-config --prefix}} {
      if {[info exists env($var)]} {
        set paths [set env($var)]
        if {[string length $paths]} {
          foreach path [split $paths :] {lappend KDE_dirs $path}
        }
      }
      if {[string length $cmd]} {
        lappend KDE_dirs [eval exec $cmd]
      }
    }
    # Now, examine all the paths found to locate the kdeglobals file.
    set PATHS {}
    foreach path $KDE_dirs {
      if {[file exists $path/share/config/kdeglobals]} {
        lappend PATHS $path/share/config/kdeglobals
      }
    }
    return $PATHS
  };# kdeLocate_kdeglobals

  ## updateColourPalette:
  #  This procedure will be called from tileqt core each time a message is
  #  received from KDE to change the palette used.
  proc updateColourPalette {} {
    #  puts >>updateColourPalette
    foreach filename [kdeLocate_kdeglobals] {
      if {[file exists $filename]} {
        set file [open $filename]
        while {[gets $file line] != -1} {
          set line [string trim $line]
          switch -glob $line {
            contrast=*         {
              if {![info exists options(-contrast)]} {
                set options(-contrast) [string range $line 9 end]
              }
            }
            background=*       {
              if {![info exists options(-background)]} {
                set options(-background) [kdeGetColourHex $line]
              }
            }
            foreground=*       {
              if {![info exists options(-foreground)]} {
                set options(-foreground) [kdeGetColourHex $line]
              }
            }
            buttonBackground=* {
              if {![info exists options(-buttonBackground)]} {
                set options(-buttonBackground) [kdeGetColourHex $line]
              }
            }
            buttonForeground=* {
              if {![info exists options(-buttonForeground)]} {
                set options(-buttonForeground) [kdeGetColourHex $line]
              }
            }
            selectBackground=* {
              if {![info exists options(-selectBackground)]} {
                set options(-selectBackground) [kdeGetColourHex $line]
              }
            }
            selectForeground=* {
              if {![info exists options(-selectForeground)]} {
                set options(-selectForeground) [kdeGetColourHex $line]
              }
            }
            windowBackground=* {
              if {![info exists options(-windowBackground)]} {
                set options(-windowBackground) [kdeGetColourHex $line]
              }
            }
            windowForeground=* {
              if {![info exists options(-windowForeground)]} {
                set options(-windowForeground) [kdeGetColourHex $line]
              }
            }
            linkColor=*        {
              if {![info exists options(-linkColor)]} {
                set options(-linkColor) [kdeGetColourHex $line]
              }
            }
            visitedLinkColor=* {
              if {![info exists options(-visitedLinkColor)]} {
                set options(-visitedLinkColor) [kdeGetColourHex $line]
              }
            }
          }
        }
        close $file
      }
    }
    if {[info exists options]} {
      eval setPalette [array get options]
    }
  };# updateColourPalette

  ## kdeStyleChangeNotification:
  #  This procedure will be called from tileqt core each time a message is
  #  received from KDE to change the style used.
  proc kdeStyleChangeNotification {} {
    #  puts >>kdeStyleChangeNotification
    ## This method will be called each time a ClientMessage is received from
    ## KDE KIPC...
    ## Our Job is:
    ##  a) To get the current style from KDE, and
    ##  b) Apply it.
    foreach filename [kdeLocate_kdeglobals] {
      if {[file exists $filename]} {
        set file [open $filename]
        while {[gets $file line] != -1} {
          set line [string trim $line]
          if {[string match widgetStyle*=* $line]} {
            # We have found the style!
            set index [string first = $line]; incr index
            set style [string range $line $index end]
            if {[string length $style]} {
              close $file
              applyStyle $style
              return
            }
          }
        }
        close $file
      }
    }
  };# kdeStyleChangeNotification

  ## applyStyle:
  #  This procedure can be used to apply any available Qt/KDE style.
  #  Ths "style" parameter must be a string from the style names returned by
  #  tile::theme::tileqt::availableStyles.
  proc applyStyle {style} {
    updateColourPalette
    setStyle $style
    updateStyles
    updateLayouts
    event generate {} <<ThemeChanged>>
  };# applyStyle

  ## kdePaletteChangeNotification:
  #  This procedure will be called from tileqt core each time a message is
  #  received from KDE to change the palette used.
  proc kdePaletteChangeNotification {} {
    #  puts >>kdePaletteChangeNotification
    kdeStyleChangeNotification
  };# kdePaletteChangeNotification

  proc kdeGetColourHex {line} {
    set index [string first = $line]; incr index
    set value [string range $line $index end]
    foreach {r g b} [split $value ,] {break}
    return [format #%02X%02X%02X $r $g $b]
  };# kdeGetColourHex

  ## createThemeConfigurationPanel:
  #  This method will create a configuration panel for the tileqt theme in the
  #  provided frame widget.
  proc createThemeConfigurationPanel {dlgFrame} {
    ## The first element in our panel, is a combobox, with all the available
    ## Qt/KDE styles.
    ttk::labelframe $dlgFrame.style_selection -text "Qt/KDE Style:"
      ttk::combobox $dlgFrame.style_selection.style -state readonly
      $dlgFrame.style_selection.style set [currentThemeName]
      bind $dlgFrame.style_selection.style <<ThemeChanged>> \
        {%W set [tile::theme::tileqt::currentThemeName]}
      bind $dlgFrame.style_selection.style <Enter> \
        {%W configure -values [tile::theme::tileqt::availableStyles]}
      ttk::button $dlgFrame.style_selection.apply -text Apply -command \
       "tile::theme::tileqt::applyStyle \[$dlgFrame.style_selection.style get\]"
      grid $dlgFrame.style_selection.style $dlgFrame.style_selection.apply \
        -padx 2 -sticky snew
      grid columnconfigure $dlgFrame.style_selection 0 -weight 1
    pack $dlgFrame.style_selection -fill x -expand 0 -padx 2 -pady 2
    ## The second element of our panel, is a preview area. Since tile does not
    ## allow us to use a different theme for some widgets, we start a new wish
    ## session through a pipe, and we embed its window in our dialog. Then, we
    ## instrument this second wish through the pipe...
    ttk::labelframe $dlgFrame.preview -text "Preview:"
      variable PreviewInterp
      if {[string length $PreviewInterp]} {
        frame $dlgFrame.preview.container
          pack [label $dlgFrame.preview.container.lbl \
                 -text {Preview Unavailable!}] -fill both -expand 1
      } else {
        frame $dlgFrame.preview.container -container 1 -height 250 -width 400
        ## Create a slave interpreter, and load tileQt. Widgets in this interp
        ## may be of a different widget style!
        set PreviewInterp [interp create]
        interp eval $PreviewInterp {package require Tk}
        interp eval $PreviewInterp "
          wm withdraw .
          set auto_path \{$::auto_path\}
          package require tile
          package require tile::theme::tileqt
          tile::theme::tileqt::applyStyle \{[currentThemeName]\}
          toplevel .widgets -height 250 -width 400 \
                            -use [winfo id $dlgFrame.preview.container]
          tile::theme::tileqt::selectStyleDlg_previewWidgets .widgets
        "
        bind $dlgFrame.preview.container <Destroy> \
          "tile::theme::tileqt::destroyThemeConfigurationPanel"
        bind $dlgFrame.style_selection.style <<ComboboxSelected>> \
          {tile::theme::tileqt::updateThemeConfigurationPanel [%W get]}
      }
      pack $dlgFrame.preview.container -padx 0 -pady 0 -fill both -expand 1
    pack $dlgFrame.preview -fill both -expand 1 -padx 2 -pady 2
  };# createThemeConfigurationPanel

  proc destroyThemeConfigurationPanel {} {
    variable PreviewInterp
    interp delete $PreviewInterp
    set PreviewInterp {}
  };# destroyThemeConfigurationPanel

  proc updateThemeConfigurationPanel {style} {
    variable PreviewInterp
    interp eval $PreviewInterp "tile::theme::tileqt::applyStyle \{$style\}"
  };# updateThemeConfigurationPanel

  proc selectStyleDlg_previewWidgets {{win {}}} {
    ## Create a notebook widget...
    ttk::notebook $win.nb -padding 6
    set tab1 [ttk::frame $win.nb.tab1]
    $win.nb add $tab1 -text "Tab 1" -underline 0 -sticky news
    set tab2 [ttk::frame $win.nb.tab2]
    $win.nb add $tab2 -text "Tab 2" -underline 0 -sticky news
    set tab3 [ttk::frame $win.nb.tab3]
    $win.nb add $tab3 -text "Tab 3" -underline 0 -sticky news
    set tab4 [ttk::frame $win.nb.tab4]
    $win.nb add $tab4 -text "Tab 4" -underline 0 -sticky news
    ## Fill only tab1...
    #####################
    ## Add a set of radiobuttons to the left...
    ttk::labelframe $tab1.buttons -text "Buttons:"
      ttk::radiobutton $tab1.buttons.b1 -text "Selection 1" -variable \
         tile::theme::tileqt::temp(selectionVariable) -value 1
      ttk::radiobutton $tab1.buttons.b2 -text "Selection 2" -variable \
         tile::theme::tileqt::temp(selectionVariable) -value 2
      ttk::radiobutton $tab1.buttons.b3 -text "Selection 3" -variable \
         tile::theme::tileqt::temp(selectionVariable) -value 3
      ttk::checkbutton $tab1.buttons.b4 -text "Check Button"
      grid $tab1.buttons.b1 -sticky snew
      grid $tab1.buttons.b2 -sticky snew
      grid $tab1.buttons.b3 -sticky snew
      grid $tab1.buttons.b4 -sticky snew
    ## Add a set of other widgets (like progress, combo, scale, etc).
    ttk::frame $tab1.widgets
      ttk::progressbar $tab1.widgets.progress -orient horizontal -maximum 100 \
        -variable tile::theme::tileqt::temp(progress)
      grid $tab1.widgets.progress -sticky snew -padx 1 -pady 1
      ttk::scale $tab1.widgets.scale -orient horizontal -from 0 -to 100 \
        -variable tile::theme::tileqt::temp(progress)
      set tile::theme::tileqt::temp(progress) 70
      grid $tab1.widgets.scale -sticky snew -padx 1 -pady 1
      ttk::entry $tab1.widgets.entry -textvariable \
        tile::theme::tileqt::temp(entry)
      set tile::theme::tileqt::temp(entry) {Entry Widget}
      grid $tab1.widgets.entry -sticky snew -padx 1 -pady 1
      ttk::button $tab1.widgets.button -text Button
      grid $tab1.widgets.button -sticky snew -padx 1 -pady 1
      ttk::combobox $tab1.widgets.combo -values {{Selection 1} {Selection 2}}
      $tab1.widgets.combo set {Selection 1}
      grid $tab1.widgets.combo -sticky snew -padx 1 -pady 1
    grid $tab1.buttons $tab1.widgets -padx 2 -pady 2 -sticky snew
    ttk::scrollbar $tab1.hsb -orient horizontal
    grid $tab1.hsb -columnspan 2 -padx 2 -pady 2 -sticky snew
    ttk::scrollbar $tab1.vsb -orient vertical
    grid $tab1.vsb -row 0 -column 3 -padx 2 -pady 2 -sticky snew
    grid columnconfigure $tab1 1 -weight 1
    pack $win.nb -fill both -expand 1
  };# selectStyleDlg_previewWidgets

  proc availableStyles {} {
    return [lsort -dictionary [availableStyles_AsReturned]]
  };# availableStyles
  
  ## Update layouts on load...
  updateLayouts
  updateStyles

  ## Test the theme configuration panel...
  if {0 && ![info exists ::testConfigurationPanel]} {
    toplevel .themeConfPanel
    wm withdraw .themeConfPanel
    wm title .themeConfPanel "TileQt Configuration Panel..."
    frame .themeConfPanel.page
    createThemeConfigurationPanel .themeConfPanel.page
    update
    pack .themeConfPanel.page -fill both -expand 1
    wm deiconify .themeConfPanel
  }
}
