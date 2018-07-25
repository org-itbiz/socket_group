object mForm: TmForm
  Left = 0
  Top = 0
  Caption = 'mForm'
  ClientHeight = 591
  ClientWidth = 765
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 765
    Height = 544
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitLeft = 64
    ExplicitTop = 16
    ExplicitWidth = 185
    ExplicitHeight = 41
    object WebBrowser1: TWebBrowser
      Left = 0
      Top = 0
      Width = 765
      Height = 550
      Align = alClient
      TabOrder = 0
      ControlData = {
        4C000000114F0000D83800000000000000000000000000000000000000000000
        000000004C000000000000000000000001000000E0D057007335CF11AE690800
        2B2E126208000000000000004C0000000114020000000000C000000000000046
        8000000000000000000000000000000000000000000000000000000000000000
        00000000000000000100000000000000000000000000000000000000}
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 544
    Width = 765
    Height = 47
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 40
      Height = 13
      Caption = #47532#53556' '#44050':'
    end
    object edtReturnV: TEdit
      Left = 62
      Top = 12
      Width = 121
      Height = 21
      TabOrder = 0
      Text = #47532#53556#44050
    end
    object btnHWForm: TButton
      Left = 680
      Top = 12
      Width = 75
      Height = 25
      Caption = 'hw socket'
      TabOrder = 1
      OnClick = btnHWFormClick
    end
  end
  object IdUDPServer1: TIdUDPServer
    Bindings = <>
    DefaultPort = 0
    OnUDPRead = IdUDPServer1UDPRead
    Left = 288
    Top = 144
  end
  object sgcWSServer1: TsgcWebSocketServer
    Port = 30001
    OnConnect = sgcWSServer1Connect
    OnMessage = sgcWSServer1Message
    OnDisconnect = sgcWSServer1Disconnect
    OnError = sgcWSServer1Error
    OnException = sgcWSServer1Exception
    LoadBalancer.AutoRegisterBindings = False
    LoadBalancer.AutoRestart = 0
    LoadBalancer.Enabled = False
    LoadBalancer.Port = 0
    Authentication.Enabled = False
    Authentication.AllowNonAuth = False
    Authentication.URL.Enabled = True
    Authentication.Session.Enabled = True
    Authentication.Basic.Enabled = False
    Bindings = <>
    HeartBeat.Enabled = False
    HeartBeat.Interval = 300
    HeartBeat.Timeout = 0
    MaxConnections = 0
    SSLOptions.Port = 0
    ThreadPool = False
    ThreadPoolOptions.MaxThreads = 0
    ThreadPoolOptions.PoolSize = 32
    Extensions.DeflateFrame.Enabled = False
    Extensions.DeflateFrame.WindowBits = 15
    Extensions.PerMessage_Deflate.Enabled = False
    Extensions.PerMessage_Deflate.ClientMaxWindowBits = 15
    Extensions.PerMessage_Deflate.ClientNoContextTakeOver = False
    Extensions.PerMessage_Deflate.MemLevel = 1
    Extensions.PerMessage_Deflate.ServerMaxWindowBits = 15
    Extensions.PerMessage_Deflate.ServerNoContextTakeOver = False
    FallBack.Flash.Domain = '*'
    FallBack.Flash.Enabled = False
    FallBack.Flash.Ports = '*'
    FallBack.ServerSentEvents.Enabled = False
    FallBack.ServerSentEvents.Retry = 3
    Options.FragmentedMessages = frgOnlyBuffer
    Options.HTMLFiles = True
    Options.JavascriptFiles = True
    Options.QueueText = False
    Options.QueueBinary = False
    Options.ReadTimeOut = 10
    Options.RaiseDisconnectExceptions = True
    Options.ValidateUTF8 = False
    Specifications.Drafts.Hixie76 = True
    Specifications.RFC6455 = True
    NotifyEvents = neAsynchronous
    LogFile.Enabled = False
    Throttle.BitsPerSec = 0
    Throttle.Enabled = False
    WatchDog.Attempts = 0
    WatchDog.Enabled = False
    WatchDog.Interval = 60
    Left = 416
    Top = 144
  end
end
