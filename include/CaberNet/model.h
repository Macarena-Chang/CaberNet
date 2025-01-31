#pragma once

#include <iostream>
#include <variant>

#include "tensor.h"
#include "optimizers.h"

namespace net {

template<class Derived>
class Model {
    using optimizer_variant = std::variant<
        optimizer::SGD
    >;

    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_t>;

    Tensor<float> operator()(Tensor<float> input) {
        return static_cast<Derived*>(this)->forward(input);
    }

    void configure_optimizer(optimizer_variant instance) {
        optimizer_ = std::visit([](auto&& argument) { return &argument; }, instance);
        static_cast<Derived*>(this)->set_optimizer(optimizer_);
    }

    protected:
    net::base::Optimizer* optimizer() const {
        return optimizer_;
    }

    private:
    net::base::Optimizer* optimizer_ = nullptr;
};

} // namespace net
