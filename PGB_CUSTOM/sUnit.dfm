object ServerForm: TServerForm
  Left = 0
  Top = 0
  Caption = #49444#51221' '#44288#47532
  ClientHeight = 429
  ClientWidth = 651
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 651
    Height = 429
    ActivePage = tabBase
    Align = alClient
    TabOrder = 0
    object tabBase: TTabSheet
      Caption = 'DEBUG'
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 339
        Height = 401
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Label2: TLabel
          Left = 16
          Top = 6
          Width = 80
          Height = 13
          Caption = #49444#51221#54028#51068' Sheets'
        end
        object Label3: TLabel
          Left = 16
          Top = 245
          Width = 37
          Height = 13
          Caption = #47532#53556#44050':'
        end
        object Button7: TButton
          Left = 188
          Top = 16
          Width = 145
          Height = 25
          Caption = 'udp pagging'
          TabOrder = 0
          OnClick = Button7Click
        end
        object ListBox1: TListBox
          Left = 16
          Top = 25
          Width = 145
          Height = 185
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = []
          ItemHeight = 19
          ParentFont = False
          PopupMenu = PopupMenu2
          TabOrder = 1
          OnContextPopup = ListBox1ContextPopup
        end
        object Button1: TButton
          Left = 188
          Top = 47
          Width = 75
          Height = 25
          Caption = 'Reload'
          TabOrder = 2
        end
        object Edit1: TEdit
          Left = 16
          Top = 264
          Width = 121
          Height = 21
          TabOrder = 3
          Text = 'Edit1'
        end
      end
      object Panel2: TPanel
        Left = 339
        Top = 0
        Width = 304
        Height = 401
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 1
        object Memo1: TMemo
          Left = 6
          Top = 3
          Width = 290
          Height = 350
          Lines.Strings = (
            'Memo1')
          ScrollBars = ssVertical
          TabOrder = 0
        end
        object btnCleanLog: TButton
          Left = 211
          Top = 359
          Width = 85
          Height = 25
          Caption = 'clean log'
          TabOrder = 1
          OnClick = btnCleanLogClick
        end
      end
    end
    object tabConfig2: TTabSheet
      Caption = 'EXCEL'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox3: TGroupBox
        Left = 3
        Top = 0
        Width = 637
        Height = 284
        Caption = 'GroupBox3'
        TabOrder = 0
        object AdvStringGrid4: TAdvStringGrid
          Left = 11
          Top = 16
          Width = 494
          Height = 177
          Cursor = crDefault
          DrawingStyle = gdsClassic
          ScrollBars = ssBoth
          TabOrder = 0
          HoverRowCells = [hcNormal, hcSelected]
          ActiveCellFont.Charset = DEFAULT_CHARSET
          ActiveCellFont.Color = clWindowText
          ActiveCellFont.Height = -11
          ActiveCellFont.Name = 'Tahoma'
          ActiveCellFont.Style = [fsBold]
          ControlLook.FixedGradientHoverFrom = clGray
          ControlLook.FixedGradientHoverTo = clWhite
          ControlLook.FixedGradientDownFrom = clGray
          ControlLook.FixedGradientDownTo = clSilver
          ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
          ControlLook.DropDownHeader.Font.Color = clWindowText
          ControlLook.DropDownHeader.Font.Height = -11
          ControlLook.DropDownHeader.Font.Name = 'Tahoma'
          ControlLook.DropDownHeader.Font.Style = []
          ControlLook.DropDownHeader.Visible = True
          ControlLook.DropDownHeader.Buttons = <>
          ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
          ControlLook.DropDownFooter.Font.Color = clWindowText
          ControlLook.DropDownFooter.Font.Height = -11
          ControlLook.DropDownFooter.Font.Name = 'Tahoma'
          ControlLook.DropDownFooter.Font.Style = []
          ControlLook.DropDownFooter.Visible = True
          ControlLook.DropDownFooter.Buttons = <>
          Filter = <>
          FilterDropDown.Font.Charset = DEFAULT_CHARSET
          FilterDropDown.Font.Color = clWindowText
          FilterDropDown.Font.Height = -11
          FilterDropDown.Font.Name = 'Tahoma'
          FilterDropDown.Font.Style = []
          FilterDropDown.TextChecked = 'Checked'
          FilterDropDown.TextUnChecked = 'Unchecked'
          FilterDropDownClear = '(All)'
          FilterEdit.TypeNames.Strings = (
            'Starts with'
            'Ends with'
            'Contains'
            'Not contains'
            'Equal'
            'Not equal'
            'Larger than'
            'Smaller than'
            'Clear')
          FixedRowHeight = 22
          FixedFont.Charset = DEFAULT_CHARSET
          FixedFont.Color = clWindowText
          FixedFont.Height = -11
          FixedFont.Name = 'Tahoma'
          FixedFont.Style = [fsBold]
          FloatFormat = '%.2f'
          HoverButtons.Buttons = <>
          HoverButtons.Position = hbLeftFromColumnLeft
          HTMLSettings.ImageFolder = 'images'
          HTMLSettings.ImageBaseName = 'img'
          PrintSettings.DateFormat = 'dd/mm/yyyy'
          PrintSettings.Font.Charset = DEFAULT_CHARSET
          PrintSettings.Font.Color = clWindowText
          PrintSettings.Font.Height = -11
          PrintSettings.Font.Name = 'Tahoma'
          PrintSettings.Font.Style = []
          PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
          PrintSettings.FixedFont.Color = clWindowText
          PrintSettings.FixedFont.Height = -11
          PrintSettings.FixedFont.Name = 'Tahoma'
          PrintSettings.FixedFont.Style = []
          PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
          PrintSettings.HeaderFont.Color = clWindowText
          PrintSettings.HeaderFont.Height = -11
          PrintSettings.HeaderFont.Name = 'Tahoma'
          PrintSettings.HeaderFont.Style = []
          PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
          PrintSettings.FooterFont.Color = clWindowText
          PrintSettings.FooterFont.Height = -11
          PrintSettings.FooterFont.Name = 'Tahoma'
          PrintSettings.FooterFont.Style = []
          PrintSettings.PageNumSep = '/'
          SearchFooter.FindNextCaption = 'Find &next'
          SearchFooter.FindPrevCaption = 'Find &previous'
          SearchFooter.Font.Charset = DEFAULT_CHARSET
          SearchFooter.Font.Color = clWindowText
          SearchFooter.Font.Height = -11
          SearchFooter.Font.Name = 'Tahoma'
          SearchFooter.Font.Style = []
          SearchFooter.HighLightCaption = 'Highlight'
          SearchFooter.HintClose = 'Close'
          SearchFooter.HintFindNext = 'Find next occurrence'
          SearchFooter.HintFindPrev = 'Find previous occurrence'
          SearchFooter.HintHighlight = 'Highlight occurrences'
          SearchFooter.MatchCaseCaption = 'Match case'
          ShowDesignHelper = False
          SortSettings.DefaultFormat = ssAutomatic
          Version = '8.1.0.0'
          ColWidths = (
            64
            64
            64
            64
            64)
          RowHeights = (
            22
            22
            22
            22
            22
            22
            22
            22
            22
            22)
        end
        object Button2: TButton
          Left = 536
          Top = 24
          Width = 75
          Height = 25
          Caption = 'reload'
          Enabled = False
          TabOrder = 1
        end
        object Button6: TButton
          Left = 536
          Top = 55
          Width = 75
          Height = 25
          Caption = 'test_config'
          TabOrder = 2
          OnClick = Button6Click
        end
      end
    end
    object tabFile: TTabSheet
      Caption = #54028#51068#44221#47196
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label1: TLabel
        Left = 80
        Top = 307
        Width = 31
        Height = 13
        Caption = 'Label1'
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 643
        Height = 193
        Align = alTop
        BevelOuter = bvNone
        Color = clWindow
        Ctl3D = True
        ParentBackground = False
        ParentCtl3D = False
        TabOrder = 0
        object Splitter2: TSplitter
          Left = 0
          Top = 27
          Height = 166
          ExplicitLeft = 137
          ExplicitTop = 54
          ExplicitHeight = 139
        end
        object Panel4: TPanel
          Left = 0
          Top = 0
          Width = 643
          Height = 27
          Align = alTop
          BevelOuter = bvNone
          Color = clWindow
          ParentBackground = False
          TabOrder = 0
          Visible = False
          object Button3: TButton
            AlignWithMargins = True
            Left = 3
            Top = 3
            Width = 75
            Height = 21
            Align = alLeft
            Caption = 'Button1'
            TabOrder = 0
          end
          object Button4: TButton
            AlignWithMargins = True
            Left = 84
            Top = 3
            Width = 75
            Height = 21
            Align = alLeft
            Caption = 'Button2'
            TabOrder = 1
          end
          object Button5: TButton
            AlignWithMargins = True
            Left = 165
            Top = 3
            Width = 75
            Height = 21
            Align = alLeft
            Caption = 'Button3'
            TabOrder = 2
          end
        end
        object PanelRight: TPanel
          Left = 3
          Top = 27
          Width = 640
          Height = 166
          Align = alClient
          BevelOuter = bvNone
          Color = clWindow
          ParentBackground = False
          TabOrder = 1
          object ValueList: TValueListEditor
            AlignWithMargins = True
            Left = 3
            Top = 3
            Width = 634
            Height = 160
            Align = alClient
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goAlwaysShowEditor, goThumbTracking]
            PopupMenu = PopupMenu1
            TabOrder = 0
            OnDblClick = ValueListDblClick
            ColWidths = (
              72
              556)
            RowHeights = (
              18
              18)
          end
        end
      end
      object Panel7: TPanel
        Left = 0
        Top = 193
        Width = 643
        Height = 208
        Align = alClient
        BevelOuter = bvNone
        Color = clWindow
        ParentBackground = False
        TabOrder = 1
        object Memo2: TMemo
          AlignWithMargins = True
          Left = 3
          Top = 26
          Width = 637
          Height = 179
          Align = alClient
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 0
        end
        object ProgressBar1: TProgressBar
          AlignWithMargins = True
          Left = 3
          Top = 3
          Width = 637
          Height = 17
          Align = alTop
          TabOrder = 1
        end
      end
    end
  end
  object IdUDPServer1: TIdUDPServer
    BufferSize = 102400
    Bindings = <>
    DefaultPort = 0
    OnUDPRead = IdUDPServer1UDPRead
    Left = 168
    Top = 216
  end
  object OpenDialog1: TOpenDialog
    Left = 200
    Top = 144
  end
  object PopupMenu1: TPopupMenu
    AutoHotkeys = maManual
    AutoLineReduction = maManual
    Left = 272
    Top = 144
    object N3: TMenuItem
      Caption = #44221#47196' '#50676#44592
      OnClick = N3Click
    end
    object N1: TMenuItem
      Caption = #52628#44032
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #49325#51228
      OnClick = N2Click
    end
  end
  object IdFTP1: TIdFTP
    IPVersion = Id_IPv4
    ConnectTimeout = 0
    NATKeepAlive.UseKeepAlive = False
    NATKeepAlive.IdleTimeMS = 0
    NATKeepAlive.IntervalMS = 0
    ProxySettings.ProxyType = fpcmNone
    ProxySettings.Port = 0
    Left = 287
    Top = 243
  end
  object PopupMenu2: TPopupMenu
    Left = 68
    Top = 152
    object pM1: TMenuItem
      Caption = 'json '#49373#49457
      OnClick = pM1Click
    end
  end
end
