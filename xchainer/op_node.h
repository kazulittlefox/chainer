#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <gsl/gsl>

#include "xchainer/array_node.h"

namespace xchainer {

class OpNode {
public:
    OpNode() = default;
    OpNode(std::string name) : name_(name), rank_(0), next_nodes_(), backward_functions_() {}
    OpNode(std::string name, int64_t rank, std::vector<std::shared_ptr<ArrayNode>> next_nodes,
           std::vector<std::function<Array(const Array&)>> backward_functions)
        : name_(std::move(name)), rank_(rank), next_nodes_(std::move(next_nodes)), backward_functions_(std::move(backward_functions)) {}

    void RegisterNextNode(std::shared_ptr<ArrayNode> next_node) { next_nodes_.push_back(std::move(next_node)); }

    void RegisterBackwardFunction(std::function<Array(const Array&)> backward_function) {
        backward_functions_.push_back(std::move(backward_function));
    }

    std::string name() const { return name_; }

    int64_t rank() const { return rank_; }

    void set_rank(int64_t rank) { rank_ = rank; }

    gsl::span<const std::shared_ptr<ArrayNode>> next_nodes() const { return gsl::make_span(next_nodes_); }

    gsl::span<const std::function<Array(const Array&)>> backward_functions() const { return gsl::make_span(backward_functions_); }

private:
    std::string name_;
    int64_t rank_{0};
    std::vector<std::shared_ptr<ArrayNode>> next_nodes_;
    std::vector<std::function<Array(const Array&)>> backward_functions_;
};

}  // namespace xchainer
