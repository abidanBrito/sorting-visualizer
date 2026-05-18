#pragma once

#include "../sort_algorithm.hpp"

#include <stack>

class QuickSort : public SortAlgorithm
{
public:
    auto step(std::vector<float>& elements) -> void override;
    auto reset() -> void override;

    [[nodiscard]] auto compared_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto swapped_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto sorted_indices() const -> std::set<size_t> override;
    [[nodiscard]] auto name() const -> std::string_view override { return "Quick Sort"; }

private:
    struct Range
    {
        size_t start;
        size_t end;
    };

    std::stack<Range> pending_ranges_;
    std::set<size_t> last_compared_;
    std::set<size_t> last_swapped_;
    std::set<size_t> sorted_;
    size_t partition_start_ { 0 };
    size_t partition_end_ { 0 };
    size_t boundary_ { 0 };
    size_t cursor_ { 0 };
    float pivot_ { 0.0f };
    bool started_ { false };
    bool partitioning_ { false };
};
