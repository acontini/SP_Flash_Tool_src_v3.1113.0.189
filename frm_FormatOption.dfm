object FormatOption: TFormatOption
  Left = 348
  Top = 145
  BorderStyle = bsDialog
  Caption = ' Format Options'
  ClientHeight = 497
  ClientWidth = 818
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = OnShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 801
    Height = 481
    TabOrder = 0
    object m_Panel_AutoFormat1: TPanel
      Left = 16
      Top = 21
      Width = 177
      Height = 25
      BevelOuter = bvLowered
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      object m_Radio_AutoFormat: TRadioButton
        Left = 8
        Top = 6
        Width = 161
        Height = 17
        Caption = 'Auto Format Flash'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        OnClick = m_Radio_AutoFormatClick
      end
    end
    object m_Panel_ManualFormat1: TPanel
      Left = 16
      Top = 188
      Width = 193
      Height = 25
      BevelOuter = bvLowered
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object m_Radio_ManualFormat: TRadioButton
        Left = 8
        Top = 4
        Width = 177
        Height = 17
        Caption = 'Manual Format'
        TabOrder = 0
        OnClick = m_Radio_ManualFormatClick
      end
    end
    object m_Panel_ManualFormat2: TPanel
      Left = 16
      Top = 212
      Width = 649
      Height = 249
      BevelOuter = bvLowered
      TabOrder = 4
      object Label4: TLabel
        Left = 43
        Top = 17
        Width = 324
        Height = 16
        Caption = 'Specify the begin address and length of the format area.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Pitch = fpFixed
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object Label8: TLabel
        Left = 43
        Top = 104
        Width = 333
        Height = 16
        Caption = 'WARNING! Calibration data is erased if begin address is 0.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Pitch = fpFixed
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object FormatLength: TLabeledEdit
        Left = 176
        Top = 76
        Width = 137
        Height = 21
        EditLabel.Width = 102
        EditLabel.Height = 13
        EditLabel.Caption = 'Format Length (Hex) :'
        LabelPosition = lpLeft
        LabelSpacing = 3
        MaxLength = 18
        TabOrder = 1
      end
      object FormatStartAddr: TLabeledEdit
        Left = 176
        Top = 44
        Width = 137
        Height = 21
        EditLabel.Width = 102
        EditLabel.Height = 13
        EditLabel.Caption = 'Begin Address (Hex) :'
        LabelPosition = lpLeft
        LabelSpacing = 3
        MaxLength = 18
        TabOrder = 0
      end
      object m_Group_EraseFlag: TRadioGroup
        Left = 40
        Top = 128
        Width = 585
        Height = 105
        Caption = ' Erase Flag '
        TabOrder = 2
      end
    end
    object m_Panel_AutoFormat2: TPanel
      Left = 16
      Top = 45
      Width = 649
      Height = 132
      BevelOuter = bvLowered
      TabOrder = 1
      object m_Group_AutoFormatFlag: TRadioGroup
        Left = 39
        Top = 21
        Width = 585
        Height = 84
        Caption = 'Auto Format Flag '
        Items.Strings = (
          'Format whole flash'
          'Format whole flash except Bootloader')
        TabOrder = 0
      end
      object m_group_autoformatflag_partial: TRadioGroup
        Left = 39
        Top = 21
        Width = 585
        Height = 84
        Caption = 'Auto Format Flag'
        Items.Strings = (
          'Format whole flash except Bootloader')
        TabOrder = 1
      end
    end
    object m_FormatValidation: TCheckBox
      Left = 691
      Top = 128
      Width = 73
      Height = 25
      Hint = 'Perform read back check to verify if all the data is 0xFF'
      Caption = 'Validation'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = m_FormatValidationClick
    end
  end
  object btn_FormatCancel: TButton
    Left = 696
    Top = 90
    Width = 89
    Height = 26
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btn_FormatCancelClick
  end
  object btn_FormatOK: TButton
    Left = 696
    Top = 50
    Width = 89
    Height = 26
    Caption = 'OK'
    TabOrder = 1
    OnClick = btn_FormatOKClick
  end
end
