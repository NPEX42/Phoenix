#pragma once

#include <memory>
namespace phnx {
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ...Args>
    Ref<T> MakeRef(Args&& ...args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Scoped = std::shared_ptr<T>;

    template<typename T, typename ...Args>
    Scoped<T> MakeScoped(Args&& ...args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}