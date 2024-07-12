#pragma once

#include <string>
#include <typeinfo>

namespace GFX {

class FairingDataMissingException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Fairing data is missing.";
    }
};

class FairingDataInvalidException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Fairing data is invalid.";
    }
};

class IFairing {
protected:
    /** Data shared within the Fairing
     *
     */
    void *fairingData = nullptr;

public:
    /** Wrapper with safety features to retrieve and validate the fairing data
     *
     * @note It should be noted that the data returned can still be invalid or mismatched, this isn't the safest implementation but it works for now.
     * @note This function will throw a FairingDataMissingException if the data is missing and a FairingDataInvalidException if the data is invalid.
     *
     * @tparam T The type of the data to retrieve
     * @return The data within the Fairing static_casted to the type T
     */
    template<typename T>
    T *validateData() {
        if (this->fairingData == nullptr)
            throw FairingDataMissingException();

        T *data = static_cast<T *>(this->fairingData);

        if (data == nullptr)
            throw FairingDataInvalidException();

        return static_cast<T*>(data);
    }

    /** Set the void pointer within the Fairing
     *
     */
    template<typename T>
    void setFairingData(T *data) {
        if (data == nullptr)
            throw FairingDataInvalidException();

        this->fairingData = static_cast<void*>(data);
    }

    /** Get the void pointer within the Fairing
     *
     */
    void *getFairingData() {
        return this->fairingData;
    }

    /** Apply's the fairing's data in its own manner
     *
     * @param data Optional data to send to the Fairing during application
     */
    virtual void apply() = 0;

    /** Unapply's the fairing's data in its own manner
     *
     * @param data Optional data to send to the Fairing during application
     */
    virtual void unapply() = 0;

    virtual ~IFairing() = default;
};

} // namespace GFX
