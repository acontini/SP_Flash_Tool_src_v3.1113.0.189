object m_SecuritySetting: Tm_SecuritySetting
  Left = 610
  Top = 183
  Width = 361
  Height = 355
  Caption = 'Security Setting'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PopupMenu = m_SecuritySettingRightClick
  Position = poMainFormCenter
  OnClose = FormClose
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object m_GroupSecuritySetting: TGroupBox
    Left = 8
    Top = 8
    Width = 337
    Height = 305
    TabOrder = 0
  end
  object m_OK: TButton
    Left = 264
    Top = 24
    Width = 65
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = m_OKClick
  end
  object m_Cancel: TButton
    Left = 264
    Top = 56
    Width = 65
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = m_CancelClick
  end
  object m_Lockdown_CheckBox: TCheckBox
    Left = 20
    Top = 6
    Width = 129
    Height = 17
    Caption = 'Lock down all images'
    TabOrder = 3
    OnClick = m_Lockdown_CheckBoxClick
  end
  object m_SecuritySettingRightClick: TPopupMenu
    Left = 280
    Top = 160
    object m_CheckAll: TMenuItem
      Caption = 'Check all'
      OnClick = m_CheckAllClick
    end
    object m_UncheckAll: TMenuItem
      Caption = 'Un-check all'
      OnClick = m_UncheckAllClick
    end
  end
end
