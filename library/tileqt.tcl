namespace eval tile::theme::tileqt {
  variable PreviewPipe {}

  proc updateLayouts {} {
    ## Variable "theme" should be defined by the C part of the extension.
    variable theme
    if {![info exists theme]} {return}
    style theme use tileqt
    # puts "Current Qt Theme: [currentThemeName]"
    switch -exact -- $theme {
      b3 -
      default -
      keramik -
      plastik -
      platinum -
      thinkeramik -
      highcolor -
      light -
      light, -
      help 
      {
        # 3 Arrows...
        style layout Horizontal.TScrollbar {
          Horizontal.Scrollbar.trough -children {
              Horizontal.Scrollbar.leftarrow -side left
              Horizontal.Scrollbar.rightarrow -side right
              Horizontal.Scrollbar.leftarrow -side right
              Horizontal.Scrollbar.thumb
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.uparrow -side top
              Vertical.Scrollbar.downarrow -side bottom
              Vertical.Scrollbar.uparrow -side bottom
              Vertical.Scrollbar.thumb
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
              Horizontal.Scrollbar.thumb
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.downarrow -side bottom
              Vertical.Scrollbar.uparrow -side bottom
              Vertical.Scrollbar.thumb
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
              Horizontal.Scrollbar.thumb
          }
        };# style layout Horizontal.TScrollbar
        style layout Vertical.TScrollbar {
          Vertical.Scrollbar.trough -children {
              Vertical.Scrollbar.uparrow -side top
              Vertical.Scrollbar.downarrow -side bottom
              Vertical.Scrollbar.thumb
          }
        };# style layout Vertical.TScrollbar
      }
    }
  }; # updateLayouts

  proc updateStyles {} {
    style theme settings tileqt {
      style default "." \
         -background [currentThemeColour -background] \
         -foreground [currentThemeColour -foreground] \
	 -selectforeground [currentThemeColour -selectforeground] \
	 -selectbackground [currentThemeColour -selectbackground] \
         ;
      style default TButton      -padding {4 4} -width -11
      style default TCheckbutton -padding 0
      style default TCombobox    -padding {3 2 3 2}
      style default TEntry       -padding {2 2 2 4}
      style default TLabelframe  -background [currentThemeColour -background] \
                                 -padding 0
      style default TMenubutton  -padding {4 4} -width -11
      #style default TNotebook    -expandtab {2 2 2 2}
      style default TNotebook    -expandtab {1 0 1 0}
      style default TRadiobutton -padding 0
      style default Toolbutton   -padding {4 4}
    };# style theme settings tileqt
  };# updateStyles

  ## kdeStyleChangeNotification:
  #  This procedure will be called from tileqt core each time a message is
  #  received from KDE to change the style used.
  proc kdeStyleChangeNotification {} {
    ## This method will be called each time a ClientMessage is received from
    ## KDE KIPC...
    updateStyles
  };# kdeStyleChangeNotification

  ## applyStyle:
  #  This procedure can be used to apply any available Qt/KDE style.
  #  Ths "style" parameter must be a string from the style names returned by
  #  tile::theme::tileqt::availableStyles.
  proc applyStyle {style} {
    setStyle $style
    updateStyles
  };# applyStyle

  ## createThemeConfigurationPanel:
  #  This method will create a configuration panel for the tileqt theme in the
  #  provided frame widget.
  proc createThemeConfigurationPanel {dlgFrame} {
    ## The first element in our panel, is a combobox, with all the available
    ## Qt/KDE styles.
    ttk::labelframe $dlgFrame.style_selection -text "Qt/KDE Style:"
      ttk::combobox $dlgFrame.style_selection.style -state readonly
      $dlgFrame.style_selection.style set [currentThemeName]
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
      variable PreviewPipe
      if {[string length $PreviewPipe]} {
        frame $dlgFrame.preview.container -text {Preview Unavailable!}
      } else {
        frame $dlgFrame.preview.container -container 1 -height 250 -width 400
        ## Open a pipe to a second wish process...
        if {[catch {
          set PreviewPipe [open "|[info nameofexecutable] \
                                -use [winfo id $dlgFrame.preview.container]" w]
          puts $PreviewPipe "set ::testConfigurationPanel 0"
          puts $PreviewPipe "set auto_path \{$::auto_path\}"
          puts $PreviewPipe "package require Tk; package require tile;\
                             package require tile::theme::tileqt"
          puts $PreviewPipe ". configure -height 250 -width 400"
          puts $PreviewPipe "tile::theme::tileqt::applyStyle \{[currentThemeName]\}"
          puts $PreviewPipe "tile::theme::tileqt::selectStyleDlg_previewWidgets"
          flush $PreviewPipe
          } error]} {
          catch {close $PreviewPipe}
          set PreviewPipe {}
        } else {
          bind $dlgFrame.preview.container <Destroy> \
            {puts $tile::theme::tileqt::PreviewPipe exit;
             puts {Closing pipe...};
             catch {close $tile::theme::tileqt::PreviewPipe}}
          bind $dlgFrame.style_selection.style <<ComboboxSelected>> \
            {puts $tile::theme::tileqt::PreviewPipe "tile::theme::tileqt::applyStyle \{[%W get]\}"; flush $tile::theme::tileqt::PreviewPipe}
        }
      }
      pack $dlgFrame.preview.container -padx 0 -pady 0 -fill both -expand 1
    pack $dlgFrame.preview -fill both -expand 1 -padx 2 -pady 2
  };# selectStyleDlg

  proc selectStyleDlg_previewWidgets {{win {}}} {
    ## Create a notebook widget...
    ttk::notebook $win.nb -padding 6
    set tab1 [ttk::frame $win.nb.tab1]
    $win.nb add $tab1 -text "Tab 1" -underline 0 -sticky news
    set tab2 [ttk::frame $win.nb.tab2]
    $win.nb add $tab2 -text "Tab 2" -underline 0 -sticky news
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
    grid columnconfigure $tab1 1 -weight 1
    pack $win.nb -fill both -expand 1
  };# selectStyleDlg_previewWidgets
  
  ## Update layouts on load...
  updateLayouts
  updateStyles

  ## Test the theme configuration panel...
  if {![info exists ::testConfigurationPanel]} {
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
