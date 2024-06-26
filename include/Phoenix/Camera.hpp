#pragma once

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/matrix.hpp"
#include <glm/glm.hpp>

namespace phnx {
    class ICamera {
        public:
            const glm::mat4& ViewMatrix() {return mView;};
            const glm::mat4& ProjectionMatrix() {return mProjection;};

            const glm::mat4 ViewProjection() { return mProjection * mView; }


            void SetPosition(const glm::vec3& pos) {mPosition = pos; RecalculateView();}
            const glm::vec3& Position() const {return mPosition;}
            void SetRotation(const glm::vec3& rot) {mRotation = rot; RecalculateView();}
            const glm::vec3& Rotation() const { return mRotation; }

            void SetNearPlane(float near) {mNear = near; RecalculateProjection();}
            const float NearPlane() const { return mNear; }

            void SetFarPlane(float far) {mFar = far; RecalculateProjection();}
            const float FarPlane() const { return mFar; }

            void SetWidth(float width) {mWidth = width; RecalculateProjection();}
            const float Width() const { return mWidth; }

            void SetHeight(float height) {mHeight = height; RecalculateProjection();}
            const float Height() const { return mHeight; }

        public:
            virtual void RecalculateView() {
                glm::mat4 translation = glm::translate(mPosition);
                glm::mat4 rotation = glm::mat4(1);
                rotation = glm::rotate(rotation, mRotation.x, {1, 0, 0});
                rotation = glm::rotate(rotation, mRotation.y, {0, 1, 0});
                rotation = glm::rotate(rotation, mRotation.z, {0, 0, 1});

                mView = glm::inverse((translation * rotation));

            }
            virtual void RecalculateProjection() = 0;

        protected:
            glm::mat4 mView = glm::mat4(1), mProjection = glm::mat4(1);
            glm::vec3 mPosition, mRotation;
            float mNear = 0.1f, mFar = 1000.0f, mWidth = 1080, mHeight = 720;
    };


    class PerspectiveCamera : public ICamera {
    public:
        virtual void RecalculateProjection() override {
            mProjection = glm::perspective(mFOV, mWidth / mHeight , mNear, mFar);
        }

    private:
        float mFOV = 75.0f;

    };
}