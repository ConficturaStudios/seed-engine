#ifndef SEEDENGINE_INCLUDE_PROPERTY_H_
#define SEEDENGINE_INCLUDE_PROPERTY_H_

#include <functional>

namespace seedengine {

    /**
     * @brief A Property of type T that can have custom get and set behaviors.
     * @details
     * 
     * @tparam T The type of this property.
     */
    template<typename T>
    class Property final {

    public:

        /** A function pointer for a getter function. */
        typedef std::function<T& (const Property<T>*)> GetterFunc;
        /** A function pointer for a setter function. */
        typedef std::function<T& (const Property<T>*, const T&)> SetterFunc;

        /** A macro to use as the standard lambda for getter functions */
        #define GET(type) [&, this](const Property<type>* ref) -> type&
        /** A macro to use as the standard lambda for setter functions */
        #define SET(type) [&, this](const Property<type>* ref, const type& value) -> type&

        Property()
            : Property(T()) {}
        Property(const T& value)
            : Property(value, &defaultGet, &defaultSet) {}

        Property(const GetterFunc getter, const SetterFunc setter)
            : Property(T(), getter, setter) {}
        
        Property(const T& value, const GetterFunc getter, const SetterFunc setter) {
            this->value = value;
            this->getter_ = getter;
            this->setter_ = setter;
        }

        ~Property() = default;

        Property<T>& operator=(const T& value) {
            setter_(this, value);
            return *this;
        }
        bool operator==(const T& value) const { return getter_(this) == value; }
        bool operator==(const Property<T>& prop) const { return getter_(this) == prop.value; }
        T& operator()() const { return getter_(this); }
        operator T&() const { return getter_(this); }
        T* operator->() const { return &getter_(this); }

    protected:

        /** The value of this property. Only used in deafult getters and setters. */
        mutable T value;

        /** A pointer to the getter function assigned to this property. */
        GetterFunc getter_;
        /** A pointer to the setter function assigned to this property. */
        SetterFunc setter_;

        /**
         * @brief Gets the value stored in this Property.
         * 
         * @param ref A pointer to the Property to access.
         * @return T& A reference to this Property's stored value.
         */
        static T& defaultGet(const Property<T>* ref) { return ref->value; }
        /**
         * @brief Sets the value stored in this Property.
         * 
         * @param ref A pointer to the Property to access.
         * @param value The value to assign.
         * @return T& A reference to this Property's stored value.
         */
        static T& defaultSet(const Property<T>* ref, const T& value) { return ref->value = value; }

    };

    template<typename T>
    class ReadOnlyProperty final {

    public:
        ReadOnlyProperty(const T& value) { this->value = value; }
        virtual ~ReadOnlyProperty() = default;

        /**
         * @brief Gets the value stored in this Property. Read only.
         * 
         * @return const T& A reference to this Property's stored value. Read only.
         */
        virtual const T& get() const { return this->value; }

        const T& operator()() const { return get(); }
        operator T&() const { return get(); }
        const T* operator->() { return &value; }

    protected:
        /** The value of this property. */
        T value;
    };
}

#endif