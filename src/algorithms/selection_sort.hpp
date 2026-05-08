#pragma once

#include "../sort_algorithm.hpp"

class SelectionSort : public SortAlgorithm
{
public:
    auto step(std::vector<float>& elements) -> void override;
    auto reset() -> void override;
    [[nodiscard]] auto get_compared() const -> std::pair<size_t, size_t> override;
    [[nodiscard]] auto get_name() const -> std::string_view override;
    [[nodiscard]] auto is_done() const -> bool override;

private:
    std::pair<size_t, size_t> compared_;
    size_t right_marker_ { 0 };
    bool done_ { false };
};
