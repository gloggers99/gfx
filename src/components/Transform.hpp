#pragma once

#include "IFairing.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm/glm.hpp"
#include "glm/glm/ext.hpp"
#include "glm/glm/gtx/matrix_decompose.hpp"
#include "../Shader.hpp"

namespace GFX {

typedef struct {
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
} MatrixComponents;

class Transform : public IFairing {
private:
    glm::mat4 transform;

public:
    /** Get the underlying transform matrix
     * @return The transform matrix as a glm::mat4
     */
    glm::mat4 getTransform();

    /** Decompose the underlying transform matrix
     * @return Each matrix component in a MatrixComponents struct
     */
    MatrixComponents decompose();

    /** Compose a new matrix from a set of MatrixComponents
     * @param components Components to build from
     */
    void compose(MatrixComponents components);

    /** Get the underlying translation
     * @return The translation as a glm::vec3
     */
    glm::vec3 getTranslation();

    /** Get the underlying scale
     * @return The scale as a glm::vec3
     */
    glm::vec3 getScale();

    /** Get the underlying rotation
     * @return The rotation as a quaternion
     */
    glm::quat getRotation();

    /** Apply a translation to the underlying transform matrix
     * @param translation The translation to apply
     */
    void translate(glm::vec3 translation);

    /** Apply a scale to the underlying transform matrix
     * @param scale The scale to apply
     */
    void scale(glm::vec3 scale);

    /** Apply a rotation to the underlying transform matrix
     * @param angle The angle of the rotation to apply
     * @param axis The axis to perform the rotation about
     */
    void rotate(float angle, glm::vec3 axis);

    /** Set the translation of the underlying transform matrix
     * @param translation The translation to set
     */
    void setTranslation(glm::vec3 translation);

    /** Set the scale of the underlying transform matrix
     * @param scale The scale to set
     */
    void setScale(glm::vec3 scale);

    /** Set the rotation of the underlying transform matrix
     * @param rotation The rotation to set
     */
    void setRotation(glm::quat rotation);

    /** Reset the transform matrix to glm::mat4(1.0f)
     *
     */
    void reset();

    void apply() override;
    void unapply() override;

    Transform();
    ~Transform() override;
};

} // namespace GFX
