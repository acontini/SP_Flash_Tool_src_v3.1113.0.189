object frm_encription: Tfrm_encription
  Left = 390
  Top = 337
  Width = 295
  Height = 208
  Caption = 'Encription'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lb_Encription: TLabel
    Left = 32
    Top = 32
    Width = 144
    Height = 16
    Caption = 'Please enter  password:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object ed_Encription: TEdit
    Left = 32
    Top = 64
    Width = 225
    Height = 21
    TabOrder = 0
    OnKeyDown = ed_EncriptionKeyDown
  end
  object btn_encription_ok: TButton
    Left = 48
    Top = 120
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = btn_encription_okClick
  end
  object btn_encription_cancel: TButton
    Left = 152
    Top = 120
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btn_encription_cancelClick
  end
end
