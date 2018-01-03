#pragma once

#include <optional>
#include <memory>
#include <staticjson/staticjson.hpp>
#include <staticjson/optional_support.hpp>

template <typename ComponentType>
class HasComponent
{
protected:
    std::optional<std::unique_ptr<ComponentType>> component_;

public:
    HasComponent() = default;
    HasComponent(std::unique_ptr<ComponentType> component)
    {
        component_ = std::move(component);
    }

    inline bool has_value() const
    {
        return component_.has_value();
    }

    ComponentType* value()
    {
        if(component_.has_value())
            return component_.value().get();
        else
            return nullptr;
    }

    const ComponentType* value() const
    {
        if(component_.has_value())
            return component_.value().get();
        else
            return nullptr;
    }

    void set_value(std::unique_ptr<ComponentType> component)
    {
        component_ = std::move(component);
    }

    HasComponent<ComponentType> clone() const
    {
        if(component_.has_value())
        {

            return HasComponent<ComponentType>(component_.value()->clone());
        }
        else
        {
            return HasComponent<ComponentType>(nullptr);
        }
    }

    void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("component", &component_, staticjson::Flags::Optional);
    }
};