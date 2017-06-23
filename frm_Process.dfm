object frm_Processing: Tfrm_Processing
  Left = 420
  Top = 608
  Width = 561
  Height = 133
  BorderIcons = []
  Caption = 'Processing...'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object tipLabel: TLabel
    Left = 14
    Top = 14
    Width = 331
    Height = 16
    Caption = 'Clear-up is processing. Please wait for a while...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object masterPanel: TPanel
    Left = 135
    Top = 45
    Width = 300
    Height = 36
    BevelOuter = bvLowered
    BevelWidth = 5
    TabOrder = 0
    object red1Shape: TShape
      Left = 5
      Top = 2
      Width = 96
      Height = 30
      Brush.Color = clRed
    end
    object red2Shape: TShape
      Left = 101
      Top = 2
      Width = 96
      Height = 30
      Brush.Color = clSilver
    end
    object red3Shape: TShape
      Left = 197
      Top = 2
      Width = 96
      Height = 30
      Brush.Color = clSilver
    end
  end
  object processTimer: TTimer
    OnTimer = processTimerTimer
    Left = 499
    Top = 8
  end
end
