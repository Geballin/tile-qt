namespace eval tileqt {

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


  proc currentThemeName {} {
    variable theme
    if {![info exists theme]} {return {}}
    return $theme
  };# currentThemeName

  ## Update layouts...
  updateLayouts
}
