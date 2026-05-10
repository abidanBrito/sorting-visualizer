#pragma once

#include "../sort_algorithm.hpp"

#include <utility>

class BubbleSort : public SortAlgorithm
{
public:
    auto step(std::vector<float>& elements) -> void override;
    auto reset() -> void override;
    [[nodiscard]] auto get_compared() const -> std::pair<size_t, size_t> override;
    [[nodiscard]] auto get_name() const -> std::string_view override;
    [[nodiscard]] auto is_done() const -> bool override;

private:
    std::pair<size_t, size_t> compared_ { 0, 0 };
    size_t cursor_ { 0 };
    size_t sweep_count_ { 0 };
    bool done_ { false };
};
