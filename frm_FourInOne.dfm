object Form_FourInOne: TForm_FourInOne
  Left = 385
  Top = 136
  Width = 639
  Height = 704
  Caption = 'Write IMEI/BT/WiFi'
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
  object Label3: TLabel
    Left = 304
    Top = 223
    Width = 22
    Height = 13
    Caption = 'IMEI'
  end
  object Label8: TLabel
    Left = 24
    Top = 592
    Width = 585
    Height = 16
    Caption = 
      'Please click "Download" button in main form to excute the operat' +
      'ions after Download.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 40
    Top = 18
    Width = 561
    Height = 169
    Caption = 'NVRAM Database File'
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 28
      Width = 84
      Height = 13
      Caption = 'Modem Database'
    end
    object Label2: TLabel
      Left = 24
      Top = 100
      Width = 63
      Height = 13
      Caption = 'AP Database'
    end
    object m_edtModemDatabaseFile: TEdit
      Left = 24
      Top = 52
      Width = 353
      Height = 21
      TabOrder = 0
    end
    object btnModemDatabase: TButton
      Left = 408
      Top = 48
      Width = 129
      Height = 25
      Caption = 'Modem Database'
      TabOrder = 1
      OnClick = btnModemDatabaseClick
    end
    object m_edtAPDatabaseFile: TEdit
      Left = 24
      Top = 124
      Width = 353
      Height = 21
      TabOrder = 2
    end
    object btnAPDatabase: TButton
      Left = 408
      Top = 120
      Width = 129
      Height = 25
      Caption = 'AP Database'
      TabOrder = 3
      OnClick = btnAPDatabaseClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 40
    Top = 207
    Width = 553
    Height = 137
    Caption = 'IMEI'
    TabOrder = 1
    object Label4: TLabel
      Left = 248
      Top = 16
      Width = 62
      Height = 13
      Caption = 'IMEI Number'
    end
    object Label5: TLabel
      Left = 248
      Top = 72
      Width = 62
      Height = 13
      Caption = 'IMEI Number'
    end
    object cbIMEI1: TCheckBox
      Left = 32
      Top = 40
      Width = 97
      Height = 17
      Caption = 'Write SIM1 IMEI'
      TabOrder = 0
    end
    object cbIMEI2: TCheckBox
      Left = 32
      Top = 96
      Width = 97
      Height = 17
      Caption = 'Write SIM2 IMEI'
      TabOrder = 1
    end
    object m_edtIMEI1_Number: TEdit
      Left = 192
      Top = 36
      Width = 273
      Height = 21
      MaxLength = 15
      TabOrder = 2
    end
    object m_edtIMEI2_Number: TEdit
      Left = 192
      Top = 92
      Width = 273
      Height = 21
      MaxLength = 15
      TabOrder = 3
    end
  end
  object GroupBox3: TGroupBox
    Left = 40
    Top = 360
    Width = 553
    Height = 97
    Caption = 'BT'
    TabOrder = 2
    object Label7: TLabel
      Left = 248
      Top = 16
      Width = 55
      Height = 13
      Caption = 'BT Address'
    end
    object cbBTAddr: TCheckBox
      Left = 32
      Top = 36
      Width = 121
      Height = 17
      Caption = 'Write BT Address'
      TabOrder = 0
    end
    object m_edtBT_Address: TEdit
      Left = 191
      Top = 36
      Width = 276
      Height = 21
      MaxLength = 12
      TabOrder = 1
    end
  end
  object GroupBox4: TGroupBox
    Left = 40
    Top = 474
    Width = 553
    Height = 97
    Caption = 'WiFi'
    TabOrder = 3
    object Label6: TLabel
      Left = 248
      Top = 16
      Width = 62
      Height = 13
      Caption = 'WiFi Address'
    end
    object cbWIFIAddr: TCheckBox
      Left = 32
      Top = 40
      Width = 121
      Height = 17
      Caption = 'Write WiFi Address'
      TabOrder = 0
    end
    object m_edtWiFi_Address: TEdit
      Left = 191
      Top = 38
      Width = 273
      Height = 21
      MaxLength = 12
      TabOrder = 1
    end
  end
  object btnOK: TButton
    Left = 200
    Top = 625
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 4
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 328
    Top = 625
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 5
    OnClick = btnCancelClick
  end
  object OpenModemDialog: TOpenDialog
    Filter = 'All File (*.*)|*.*'
    Left = 456
    Top = 617
  end
  object OpenAPDialog: TOpenDialog
    Filter = 'All File (*.*)|*.*'
    Left = 520
    Top = 617
  end
end
