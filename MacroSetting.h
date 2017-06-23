#ifndef MACRO_SETTING_H_
#define MACRO_SETTING_H_

#include "flashtool_api.h"
#include "XMLSerializable.h"

class MacroSetting//:public XML::Serializable
{
   public:
        virtual ~MacroSetting() {}

    protected:
        MacroSetting() {}

    public:
        virtual SharedPtr<Command> CreateCommand(
                            FLASHTOOL_API_HANDLE_T ft_handle) const = 0;

        // Virtual copy constructor
        virtual MacroSetting* Clone() const = 0;

        // For debugging purpose
        virtual void Dump() const = 0;

};

#endif

