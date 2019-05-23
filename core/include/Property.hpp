#ifndef SEEDENGINE_INCLUDE_PROPERTY_H_
#define SEEDENGINE_INCLUDE_PROPERTY_H_

#include <functional>

namespace seedengine {

    // A Property of type T that can have custom get and set behaviors.
    template<typename T>
    class Property final {

    public:

        typedef std::function<T& (const Property<T>*)> GetterFunc;
        typedef std::function<T& (const Property<T>*, const T&)> SetterFunc;

        #define GET(t) [this](const Property<t>* ref) -> t&
        #define SET(t) [this](const Property<t>* ref, const t& value) -> t&

        Property()
            : Property(T()) {}
        Property(const T& value)
            : Property(value, &default_get, &default_set) {}
        
        Property(const GetterFunc getter)
            : Property(T(), getter, &default_set) {}
        Property(const SetterFunc setter)
            : Property(T(), &default_get, setter) {}

        Property(const GetterFunc getter, const SetterFunc setter)
            : Property(T(), getter, setter) {}

        Property(const T& value, const GetterFunc getter)
            : Property(value, getter, &default_set) {}
        Property(const T& value, const SetterFunc setter)
            : Property(value, &default_get, setter) {}
        
        Property(const T& value, const GetterFunc getter, const SetterFunc setter) {
            this->value = value;
            this->getter_ = getter;
            this->setter_ = setter;
        }

        ~Property() = default;

        // Gets the value stored in this Property.
        // @returns: A reference to this Property's stored value.
        T& get() const { return getter_(this); }
        // Sets the value stored in this Property.
        // @returns: A reference to this Property's stored value.
        T& set(const T& value) { return setter_(this, value); }

        Property<T>& operator=(const T& value) {
            set(value);
            return *this;
        }
        bool operator==(const T& value) const { return this->value == value; }
        bool operator==(const Property<T>& prop) const { return this->value == prop.value; }
        T& operator()() const { return get(); }
        operator T&() const { return get(); }
        T* operator->() { return &value; }

    protected:

        // The value of this property.
        mutable T value;

        GetterFunc getter_;
        SetterFunc setter_;

        // Gets the value stored in this Property.
        // @returns: A reference to this Property's stored value.
        static T& default_get(const Property<T>* ref) { return ref->value; }
        // Sets the value stored in this Property.
        // @returns: A reference to this Property's stored value.
        static T& default_set(const Property<T>* ref, const T& value) { return ref->value = value; }

    };

    template<typename T>
    class ReadOnlyProperty {

    public:
        ReadOnlyProperty(const T& value) { this->value = value; }
        virtual ~ReadOnlyProperty() = default;

        // Gets the value stored in this Property. Read only.
        // @returns: A reference to this Property's stored value. Read only.
        virtual const T& get() const { return this->value; }

        const T& operator()() const { return get(); }
        operator T&() const { return get(); }
        const T* operator->() { return &value; }

    protected:
        // The value of this property.
        T value;
    };
}

#endif