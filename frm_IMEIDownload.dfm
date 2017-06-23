object Form_IMEI_setting: TForm_IMEI_setting
  Left = 412
  Top = 182
  Width = 612
  Height = 433
  Caption = 'IMEI check and update'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 48
    Top = 16
    Width = 102
    Height = 13
    Caption = 'NVRAM database file'
  end
  object Label8: TLabel
    Left = 440
    Top = 376
    Width = 50
    Height = 13
    Caption = 'Checksum'
  end
  object m_edtNVRAMDatabaseFile: TEdit
    Left = 40
    Top = 40
    Width = 353
    Height = 21
    TabOrder = 0
  end
  object btnOpenNVRAMDatabase: TButton
    Left = 424
    Top = 40
    Width = 129
    Height = 25
    Caption = 'Open modem database'
    TabOrder = 1
    OnClick = btnOpenNVRAMDatabaseClick
  end
  object gbSIM1: TGroupBox
    Left = 40
    Top = 88
    Width = 441
    Height = 129
    Caption = ' SIM 1 '
    TabOrder = 2
    object Label2: TLabel
      Left = 208
      Top = 24
      Width = 22
      Height = 13
      Caption = 'IMEI'
    end
    object Label3: TLabel
      Left = 208
      Top = 72
      Width = 22
      Height = 13
      Caption = 'IMEI'
    end
    object Label4: TLabel
      Left = 368
      Top = 72
      Width = 50
      Height = 13
      Caption = 'Checksum'
    end
    object cbIMEI1InitialCheck: TCheckBox
      Left = 16
      Top = 40
      Width = 113
      Height = 17
      Caption = 'IMEI initial check'
      TabOrder = 0
    end
    object m_edtInitialIMEI1: TEdit
      Left = 144
      Top = 40
      Width = 193
      Height = 21
      TabOrder = 1
    end
    object cbIMEI1Update: TCheckBox
      Left = 16
      Top = 88
      Width = 97
      Height = 17
      Caption = 'IMEI update'
      TabOrder = 2
    end
    object m_edtIMEI1: TEdit
      Left = 144
      Top = 88
      Width = 193
      Height = 21
      MaxLength = 15
      TabOrder = 3
    end
    object m_edtChecksum1: TEdit
      Left = 368
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 4
    end
  end
  object gbSIM2: TGroupBox
    Left = 40
    Top = 232
    Width = 441
    Height = 129
    Caption = ' SIM 2 '
    TabOrder = 3
    object Label5: TLabel
      Left = 208
      Top = 24
      Width = 22
      Height = 13
      Caption = 'IMEI'
    end
    object Label6: TLabel
      Left = 208
      Top = 72
      Width = 22
      Height = 13
      Caption = 'IMEI'
    end
    object Label7: TLabel
      Left = 368
      Top = 72
      Width = 50
      Height = 13
      Caption = 'Checksum'
    end
    object cbIMEI2InitialCheck: TCheckBox
      Left = 16
      Top = 40
      Width = 105
      Height = 17
      Caption = 'IMEI initial check'
      TabOrder = 0
    end
    object m_edtInitialIMEI2: TEdit
      Left = 144
      Top = 40
      Width = 193
      Height = 21
      TabOrder = 1
    end
    object cbIMEI2Update: TCheckBox
      Left = 16
      Top = 88
      Width = 97
      Height = 17
      Caption = 'IMEI update'
      TabOrder = 2
    end
    object m_edtIMEI2: TEdit
      Left = 144
      Top = 88
      Width = 193
      Height = 21
      MaxLength = 15
      TabOrder = 3
    end
    object m_edtChecksum2: TEdit
      Left = 368
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 4
    end
  end
  object btnOK: TButton
    Left = 504
    Top = 128
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 4
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 504
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 5
    OnClick = btnCancelClick
  end
  object cbChecksum: TCheckBox
    Left = 384
    Top = 376
    Width = 49
    Height = 17
    Caption = 'Check'
    Checked = True
    State = cbChecked
    TabOrder = 6
  end
  object OpenNVRAMdatabaseFileDialog: TOpenDialog
    Filter = 'All File (*.*)|*.*'
    Title = 'Open NVRAM database file'
    Left = 144
    Top = 368
  end
end
