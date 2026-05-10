#pragma once

#include "../sort_algorithm.hpp"

class SelectionSort : public SortAlgorithm
{
public:
    auto step(std::vector<float>& elements) -> void override;
    auto reset() -> void override;

    [[nodiscard]] auto compared_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto swapped_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto sorted_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto name() const -> std::string_view override { return "Selection Sort"; }

private:
    std::set<size_t> last_compared_;
    std::set<size_t> sorted_;
    bool last_was_swap_ { false };
    size_t right_marker_ { 0 };
    size_t last_min_idx_ { 0 };
};
