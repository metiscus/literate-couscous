#pragma once

#include <cassert>
#include <cstdint>
#include <staticjson/staticjson.hpp>

#include "body.h"
#include "component.h"
#include "damagetype.h"

class WearableComponent 
    : public Component<WearableComponent>
{
    LimbType limb_;
    std::map<Damage::Type, Damage> protection_;

    friend struct staticjson::Converter<WearableComponent>;

public:
    WearableComponent(LimbType limb = LimbType::Invalid)
        : Component(ComponentType::Wearable, "Wearable Component")
        , limb_(limb)
    {
        ;
    }

    inline void set_limb(LimbType limb)
    {
        limb_ = limb;
    }

    std::unique_ptr<WearableComponent> clone() const;
};


namespace staticjson
{
template <>
struct Converter<WearableComponent>
{
    typedef std::vector<std::string> shadow_type; 
    // This typedef is a must. The shadow type is a C++ type 
    // that can be directly converted to and from JSON values.

    static std::unique_ptr<ErrorBase> from_shadow(const shadow_type& shadow, WearableComponent& value)
    {
        assert(shadow.size() > 0);
        from_json_string(shadow[0].c_str(), &value.limb_, nullptr);
        for(uint32_t i = 1; i<shadow.size(); ++i)
        {
            Damage dmg;
            from_json_string(shadow[i].c_str(), &dmg, nullptr);
            value.protection_[dmg.type] = dmg;
        }
        return nullptr;
    }

    static void to_shadow(const WearableComponent& value, shadow_type& shadow)
    {
        shadow.push_back(to_json_string(value.limb_));
        for(const auto& obj : value.protection_)
        {
            shadow.push_back(to_json_string(obj.second));
        }
    }
};
}