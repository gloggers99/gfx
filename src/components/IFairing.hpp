#pragma once

#include <memory>
#include <string>

template<typename T = void>
class IFairing {
protected:
    /** Data shared within the Fairing
     *
     */
    T *fairingData;

public:
    /** Set the shared pointer within the Fairing
     *
     */
    void setFairingData(T *data) {
        this->fairingData = data;
    }

    /** Get the shared pointer within the Fairing
     *
     */
    T *getFairingData() {
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