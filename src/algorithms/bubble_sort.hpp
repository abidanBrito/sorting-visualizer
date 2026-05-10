#pragma once

#include "../sort_algorithm.hpp"

class BubbleSort : public SortAlgorithm
{
public:
    auto step(std::vector<float>& elements) -> void override;
    auto reset() -> void override;

    [[nodiscard]] auto compared_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto swapped_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto name() const -> std::string_view override { return "Bubble Sort"; }

private:
    std::set<size_t> last_compared_;
    bool last_was_swap_ { false };
    size_t sweep_count_ { 0 };
    size_t cursor_ { 0 };
};
