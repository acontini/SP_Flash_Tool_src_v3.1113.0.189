object Form_About: TForm_About
  Left = 283
  Top = 103
  BorderStyle = bsDialog
  Caption = 'About Smart Phone Flash Tool'
  ClientHeight = 566
  ClientWidth = 473
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 30
    Width = 40
    Height = 13
    Caption = 'DA v2.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 50
    Width = 85
    Height = 13
    Caption = 'DA BUILD_DATE'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 457
    Height = 513
    TabOrder = 0
    object VersionInfo: TLabel
      Left = 24
      Top = 24
      Width = 132
      Height = 29
      Caption = 'Version 3.1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object tool_BuildInfo: TLabel
      Left = 24
      Top = 64
      Width = 80
      Height = 13
      Caption = 'Build 2002.12.31'
    end
    object copyrightLabel: TLabel
      Left = 25
      Top = 489
      Width = 170
      Height = 13
      Caption = 'Copyright 2001-2011 MediaTek Inc.'
    end
    object tool_Comment: TLabel
      Left = 24
      Top = 88
      Width = 70
      Height = 13
      Caption = 'Comment: N/A'
    end
    object GroupBox2: TGroupBox
      Left = 24
      Top = 112
      Width = 409
      Height = 369
      Caption = 'DA and DLL Info'
      TabOrder = 0
      object brom_dll_build_date: TLabel
        Left = 24
        Top = 147
        Width = 109
        Height = 13
        Caption = 'brom_dll BUILD_DATE'
      end
      object brom_dll_release_type: TLabel
        Left = 24
        Top = 127
        Width = 125
        Height = 13
        Caption = 'brom_dll RELEASE_TYPE'
      end
      object brom_dll_version: TLabel
        Left = 24
        Top = 107
        Width = 67
        Height = 13
        Caption = 'brom.dll v2.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object da_build_date: TLabel
        Left = 24
        Top = 50
        Width = 85
        Height = 13
        Caption = 'DA BUILD_DATE'
      end
      object da_version: TLabel
        Left = 24
        Top = 30
        Width = 40
        Height = 13
        Caption = 'DA v2.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object meta_dll_build_date: TLabel
        Left = 24
        Top = 267
        Width = 109
        Height = 13
        Caption = 'meta_dll BUILD_DATE'
      end
      object meta_dll_release_type: TLabel
        Left = 24
        Top = 247
        Width = 125
        Height = 13
        Caption = 'meta_dll RELEASE_TYPE'
      end
      object meta_dll_version: TLabel
        Left = 24
        Top = 227
        Width = 104
        Height = 13
        Caption = 'META_DLL.dll v2.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object eboot_dll_version: TLabel
        Left = 24
        Top = 167
        Width = 112
        Height = 13
        Caption = 'EBOOT_DLL.dll v2.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object eboot_dll_release_type: TLabel
        Left = 24
        Top = 187
        Width = 125
        Height = 13
        Caption = 'meta_dll RELEASE_TYPE'
      end
      object eboot_dll_build_date: TLabel
        Left = 24
        Top = 207
        Width = 109
        Height = 13
        Caption = 'meta_dll BUILD_DATE'
      end
      object sp_meta_dll_version: TLabel
        Left = 24
        Top = 290
        Width = 124
        Height = 13
        Caption = 'SP META_DLL.dll v2.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object sp_meta_dll_release_type: TLabel
        Left = 24
        Top = 310
        Width = 125
        Height = 13
        Caption = 'meta_dll RELEASE_TYPE'
      end
      object sp_meta_dll_build_date: TLabel
        Left = 24
        Top = 330
        Width = 109
        Height = 13
        Caption = 'meta_dll BUILD_DATE'
      end
      object nand_util_version: TLabel
        Left = 24
        Top = 70
        Width = 72
        Height = 13
        Caption = 'NandUtil v2.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object nand_util_build_date: TLabel
        Left = 24
        Top = 88
        Width = 111
        Height = 13
        Caption = 'NandUtil BUILD_DATE'
      end
    end
  end
  object about_OK_Btn: TButton
    Left = 390
    Top = 530
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = about_OK_BtnClick
  end
  object check_update_btn: TButton
    Left = 8
    Top = 530
    Width = 120
    Height = 25
    Caption = 'Check for Updates'
    TabOrder = 2
    OnClick = check_update_btnClick
  end
end
