#ifndef SEEDENGINE_INCLUDE_PROPERTY_H_
#define SEEDENGINE_INCLUDE_PROPERTY_H_

namespace seedengine {

    // A Property of type T that can have custom get and set behaviors.
    template<typename T>
    class Property {

    public:
        Property() = default;
        Property(const T& value) { this->value = value; }
        virtual ~Property() = default;

        // Gets the value stored in this Property.
        // @returns: A reference to this Property's stored value.
        virtual T& get() const { return this->value; }
        // Sets the value stored in this Property.
        // @returns: A reference to this Property's stored value.
        virtual T& set(const T& value) { return this->value = value; }

        T& operator=(const T& value) const { return set(value); }
        T& operator()() const { return get(); }
        operator T&() const { return get(); }
        T* operator->() { return &value; }

    protected:
        // The value of this property.
        mutable T value;
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